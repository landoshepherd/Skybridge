//
// Created by Lando Shepherd on 5/26/26.
//

#include "include/AmqClient.h"

AmqClient::AmqClient(const std::string& address, const std::string& username, const std::string& password):
m_amqAddress(address), m_username(username), m_password(password), m_workQueue(nullptr){}

void AmqClient::send(const proton::message& msg) {
  // A work queue is basically a queue of tasks
  // that qpid::proton manages proton objects.
  // This is not our message queue we will use
  // for message processing.
  m_workQueue->add([=](){m_sender.send(msg);});
}

proton::message AmqClient::receive() {
  std::unique_lock<std::mutex> lock(m_mutex);
  while (m_messages.empty()) {
    m_messagesReady.wait(lock);
  }
  auto msg = std::move(m_messages.front());
  m_messages.pop();
  return msg;
}

void AmqClient::close() {
  m_workQueue->add([=]() {
    m_sender.connection().close();
  });
}

proton::work_queue* AmqClient::workQueue() {
  std::unique_lock<std::mutex> lock(m_mutex);
  while (!m_workQueue) {
    m_senderReady.wait(lock);
  }
  return m_workQueue;
}

void AmqClient::on_container_start(proton::container& container) {
  std::cout << "SYSTEM: Establishing connection..." << std::endl;
  proton::connection_options opts;
  opts.user(m_username);
  opts.password(m_password);
  opts.sasl_allow_insecure_mechs(true);
  container.connect(m_amqAddress, opts);
  std::cout << "SYSTEM: Connection established" << std::endl;
}

void AmqClient::on_connection_open(proton::connection& connection) {
  std::cout << "SYSTEM: Setting up sender and receiver..." << std::endl;
  connection.open_sender(m_amqAddress);
  connection.open_receiver(m_amqAddress);
  std::cout << "SYSTEM: Sender and receiver setup completed" << std::endl;
}

void AmqClient::on_sender_open(proton::sender& sender) {
  std::cout << "SYSTEM: Opening sender..." << std::endl;
  std::lock_guard<std::mutex> lock(m_mutex);
  m_sender = sender;
  m_workQueue = &sender.work_queue();
  m_senderReady.notify_all();
  std::cout << "SYSTEM: Sender open" << std::endl;
}

void AmqClient::on_message(proton::delivery& delivery, proton::message& message) {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_messages.push(message);
  m_messagesReady.notify_all();
}

void AmqClient::on_error(const proton::error_condition& error) {
  std::cerr << "unexpected error: " << error << std::endl;
  exit(1);
}