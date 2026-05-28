//
// Created by Lando Shepherd on 5/27/26.
//

#ifndef SKYBRIDGE_MESSAGEPACKET_H
#define SKYBRIDGE_MESSAGEPACKET_H

#include <string>
#include <memory>
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

  void setTimestamp(const std::string& timestamp);
  const std::string& getTimestamp();

  void setMessageType(MessageType type);
  MessageType getMessageType();

  // Constructor
  MessagePacket(const std::string& source,
                const std::string& destination,
                const uuids::uuid& id,
                const std::string& timestamp,
                MessageType messageType,
                std::unique_ptr<IMessagePlayload> messagePayload);

  // Destructor
  ~MessagePacket() = default;

private:
  std::string m_source;
  std::string m_destination;
  uuids::uuid m_id;
  std::string m_timestamp;
  MessageType m_messageType;
  std::unique_ptr<IMessagePlayload> m_payload;

  // TODO: Add serialization callback table here
};
#endif //SKYBRIDGE_MESSAGEPACKET_H