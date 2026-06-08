//
// Created by Lando Shepherd on 5/26/26.
//

#ifndef SKYBRIDGE_AMQCLIENT_H
#define SKYBRIDGE_AMQCLIENT_H

#include <proton/connection.hpp>
#include <proton/connection_options.hpp>
#include <proton/container.hpp>
#include <proton/message.hpp>
#include <proton/messaging_handler.hpp>
#include <proton/receiver.hpp>
#include <proton/sender.hpp>
#include <proton/work_queue.hpp>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

/**
 * @class AmqClient
 * @brief A client class for managing AMQP connections, sending, and receiving messages.
 * 
 * AmqClient wraps Apache Qpid Proton's messaging handler to provide a simplified,
 * thread-safe, and asynchronous interface for interacting with an AMQP broker.
 * It manages connection lifecycle, credentials, and message routing.
 */
class AmqClient : public proton::messaging_handler {

public:
  /**
   * @brief Constructs an AmqClient instance.
   * 
   * @param address The AMQP broker address to connect to (e.g., host:port or URL).
   */
  AmqClient(const std::string& address, const std::string& username, const std::string& password);

  /**
   * @brief Asynchronously sends an AMQP message.
   * 
   * Dispatches the message send operation to the Proton work queue of the sender.
   * 
   * @param msg The proton::message to be transmitted.
   * @note Does not override proton::messaging_handler. Can be redefined with a custom message type if needed.
   */
  void send(const proton::message& msg); //Does not override. May redfine with own message type

  /**
   * @brief Blocks until a message is received, then returns it.
   * 
   * This is a thread-safe, blocking call that waits for a message to arrive
   * in the internal queue, extracts it using move semantics, and returns it.
   * 
   * @return The received proton::message.
   */
  proton::message receive(); //Does not override

  /**
   * @brief Closes the AMQP connection.
   * 
   * Asynchronously schedules the connection close event on the Proton work queue.
   */
  void close();

private:
  /**
   * @brief Retrieves the proton::work_queue associated with the active sender.
   * 
   * This is a thread-safe call that blocks the caller if the sender is not yet open.
   * Once the sender is ready and the work queue is established, it returns the pointer.
   * 
   * @return A pointer to the active proton::work_queue.
   */
  proton::work_queue* workQueue();

  /**
   * @brief Callback invoked when the Proton container starts.
   * 
   * Configures connection options (such as authentication credentials) and
   * initiates the connection to the AMQP broker.
   * 
   * @param container The proton::container that has started.
   */
  void on_container_start(proton::container& container) override;

  /**
   * @brief Callback invoked when the AMQP connection is successfully opened.
   * 
   * Opens the default sender and receiver links on the configured AMQP address.
   * 
   * @param connection The opened proton::connection.
   */
  void on_connection_open(proton::connection& connection) override;

  /**
   * @brief Callback invoked when the AMQP sender link is successfully opened.
   * 
   * Caches the sender reference and its associated work queue, and signals that
   * the sender is ready for message transmission.
   * 
   * @param sender The opened proton::sender.
   */
  void on_sender_open(proton::sender& sender) override;

  /**
   * @brief Callback invoked when a new AMQP message is received.
   * 
   * Thread-safely pushes the incoming message onto the internal message queue
   * and notifies any threads waiting in receive().
   * 
   * @param delivery The delivery details associated with the message.
   * @param message The incoming proton::message object.
   */
  void on_message(proton::delivery& delivery, proton::message& message) override;

  /**
   * @brief Callback invoked when an unexpected protocol or transport error occurs.
   * 
   * Prints the error condition details to standard error and terminates the application.
   * 
   * @param error The details of the error condition.
   */
  void on_error(const proton::error_condition& error) override;

private:
  const std::string m_amqAddress;
  const std::string m_username;
  const std::string m_password;
  proton::sender m_sender;
  std::mutex m_mutex;
  proton::work_queue *m_workQueue;
  std::condition_variable m_senderReady;
  std::queue<proton::message> m_messages;
  std::condition_variable m_messagesReady;
  proton::connection_options m_connectionOpts;
};
#endif //SKYBRIDGE_AMQCLIENT_H