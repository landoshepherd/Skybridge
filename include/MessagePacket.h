//
// Created by Lando Shepherd on 5/27/26.
//

#ifndef SKYBRIDGE_MESSAGEPACKET_H
#define SKYBRIDGE_MESSAGEPACKET_H

#include <string>
#include <memory>
#include <chrono>
#include <map>
#include "uuid.h"
#include "interfaces/IMessagePayload.h"

//TODO: Storing the message types here for now. Will move to another place later.
enum class MessageType {
  HEARTBEAT = 0,
  VEHICLE_TELEMETRY
};

class MessagePacket {
public:
  void setSource(const std::string& source);
  const std::string& getSource();

  void setDestination(const std::string& destination);
  const std::string& getDestination();

  void setId(const uuids::uuid& id);
  const uuids::uuid& getId();

  void setTimestamp(const std::time_t& timestamp);
  const std::time_t& getTimestamp();

  void setMessageType(MessageType type);
  MessageType getMessageType();

  static MessagePacket deserialize(const std::string& dataStr);

public:
  // Constructor
  MessagePacket(const std::string& source,
                const std::string& destination,
                const uuids::uuid& id,
                const std::time_t& timestamp,
                MessageType messageType,
                std::unique_ptr<IMessagePayload> messagePayload = nullptr);

  // Move constructor
  MessagePacket(MessagePacket&&) = default;

  // Copy assignment
  MessagePacket& operator=(MessagePacket&) = delete;

  // Move assignment operator
  MessagePacket& operator=(MessagePacket&&) = default;

  // Copy constructor
  MessagePacket(MessagePacket&) = delete;

  // Destructor
  ~MessagePacket() = default;

private:
  std::string m_source;
  std::string m_destination;
  uuids::uuid m_id;
  std::time_t m_timestamp; // YYYY-MM-DDTHH:mm:ss
  MessageType m_messageType;
  std::unique_ptr<IMessagePayload> m_payload;

  // TODO: Add serialization callback table here
};
#endif //SKYBRIDGE_MESSAGEPACKET_H