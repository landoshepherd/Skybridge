//
// Created by Lando Shepherd on 5/27/26.
//

#include "include/MessagePacket.h"

#include <proton/message.hpp>

MessagePacket::MessagePacket(const std::string& source,
                             const std::string& destination,
                             const uuids::uuid& id,
                             const std::string& timestamp,
                             MessageType messageType,
                             std::unique_ptr<IMessagePlayload> messagePayload = nullptr):
  m_source(source),
  m_destination(destination),
  m_id(id),
  m_timestamp(timestamp),
  m_messageType(messageType),
  m_payload(std::move(messagePayload))
{}

void MessagePacket::setSource(const std::string& source) {
  m_source = source;
}

const std::string& MessagePacket::getSource() {
  return m_source;
}

void MessagePacket::setDestination(const std::string& destination) {
  m_destination = destination;
}

const std::string& MessagePacket::getDestination() {
  return m_destination;
}

void MessagePacket::setId(const uuids::uuid& id) {
  m_id = id;
}

const uuids::uuid& MessagePacket::getId() {
  return m_id;
}

void MessagePacket::setTimestamp(const std::string& timestamp) {
  m_timestamp = timestamp;
}

const std::string& MessagePacket::getTimestamp() {
  return m_timestamp;
}

void MessagePacket::setMessageType(MessageType type) {
  m_messageType = type;
}

MessageType MessagePacket::getMessageType() {
  return m_messageType;
}