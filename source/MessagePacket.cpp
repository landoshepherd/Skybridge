//
// Created by Lando Shepherd on 5/27/26.
//

#include "include/MessagePacket.h"

// External
#include <proton/message.hpp>
#include <rapidjson/document.h>
#include <iostream>
#include <chrono>
#include <iomanip>

// Local

static std::map<MessageType, std::function<IMessagePayload*(const std::string&)>> deserializeDispatch;

// TODO: Need to add error handling to this
std::time_t stringToTime_t(const std::string& timeStr) {
  std::tm timeObj{0}; // Need to init like this
  std::istringstream ss(timeStr);
  ss >> std::get_time(&timeObj, "%YYYY-%MM-%DDT%HH:%mm:%ss");
  return mktime(&timeObj);
}

std::string time_tToString(const std::time_t& time_t) {

}

MessagePacket::MessagePacket(const std::string& source,
                             const std::string& destination,
                             const uuids::uuid& id,
                             const std::time_t& timestamp,
                             MessageType messageType,
                             std::unique_ptr<IMessagePayload> messagePayload):
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

void MessagePacket::setTimestamp(const std::time_t& timestamp) {
  m_timestamp = timestamp;
}

const std::time_t& MessagePacket::getTimestamp() {
  return m_timestamp;
}

void MessagePacket::setMessageType(MessageType type) {
  m_messageType = type;
}

MessageType MessagePacket::getMessageType() {
  return m_messageType;
}

MessagePacket MessagePacket::deserialize(const std::string& dataStr) {
  rapidjson::Document doc;
  doc.Parse(dataStr.c_str());

  if (doc.HasParseError()) {
    std::cerr << "ERROR: Failed to parse message" << std::endl;
  }

  const auto source = doc["messagePacket"]["source"].GetString();
  const auto destination = doc["messagePacket"]["destination"].GetString();
  const auto id = uuids::uuid::from_string(doc["messagePacket"]["uuid"].GetString()).value();
  const auto timestamp = stringToTime_t(doc["messagePacket"]["timestamp"].GetString());
  const auto messageType = static_cast<MessageType>(doc["messagePacket"]["messageType"].GetInt());

  const auto payloadStr = doc["messagePacket"]["data"].GetString();
  const std::unique_ptr<IMessagePayload> payload{deserializeDispatch[messageType](payloadStr)};

  return {source, destination, id, timestamp, messageType, std::move(payload)};
}