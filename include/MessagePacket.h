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
#include "rapidjson/document.h"

//TODO: Storing the message types here for now. Will move to another place later.
//TODO: Write an issue to convert these types to strings.
enum class MessageType {
  HEARTBEAT = 0,
  VEHICLE_TELEMETRY
};

class MessagePacket {
public:
  void setSource(const std::string& source);
  const std::string& getSource() const;

  void setDestination(const std::string& destination);
  const std::string& getDestination() const;

  void setId(const uuids::uuid& id);
  const uuids::uuid& getId() const;

  void setTimestamp(const std::time_t& timestamp);
  const std::time_t& getTimestamp() const;

  void setMessageType(MessageType type);
  MessageType getMessageType() const;

  const std::shared_ptr<const IMessagePayload> getPayload() const;

  static MessagePacket deserialize(const std::string& dataStr);

  static void registerDeserializer(MessageType msgType, const std::function<IMessagePayload*(const rapidjson::Value&)>& deserializer);

public:
  // Constructor
  MessagePacket(const std::string& source,
                const std::string& destination,
                const uuids::uuid& id,
                const std::time_t& timestamp,
                MessageType messageType,
                std::shared_ptr<IMessagePayload> messagePayload);

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
  std::string m_source; // TODO: Will source and destination be service names or UUIDs of services?
  std::string m_destination;
  uuids::uuid m_id;
  std::time_t m_timestamp; // YYYY-MM-DDTHH:mm:ss
  MessageType m_messageType;
  std::shared_ptr<IMessagePayload> m_payload;

  // TODO: Add serialization callback table here
};
#endif //SKYBRIDGE_MESSAGEPACKET_H