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



static std::map<MessageType, std::function<IMessagePayload*(const std::string&)>> getDispatchTable() {
  static std::map<MessageType, std::function<IMessagePayload*(const std::string&)>> dispatchTable{};
  return dispatchTable;
}

void MessagePacket::registerDeserializer(MessageType msgType,
  const std::function<IMessagePayload*(const std::string&)>& deserializer) {
  getDispatchTable().insert(std::make_pair(msgType, deserializer));
}

// TODO: Need to add error handling to this
std::time_t stringToTime_t(const std::string& timeStr) {
  std::tm timeObj{0}; // Need to init like this
  std::istringstream ss(timeStr);
  ss >> std::get_time(&timeObj, "%YYYY-%MM-%DDT%HH:%mm:%ss");
  return mktime(&timeObj);
}

MessagePacket MessagePacket::deserialize(const std::string& dataStr) {
  rapidjson::Document doc;
  doc.Parse(dataStr.c_str());

  if (doc.HasParseError()) {
    std::cerr << "ERROR: Failed to parse message" << std::endl;
  }

  if (!doc.HasMember("messagePacket") || !doc["messagePacket"].IsObject()) {
    std::string errorMessage = "ERROR: Malformed packet. Missing: `messagePacket`";
    std::cerr << errorMessage << std::endl;

    throw std::runtime_error(errorMessage);
  }

  rapidjson::Value& msgPacketRoot = doc["messagePacket"];

  if (!msgPacketRoot.HasMember("source")) {
    std::string errorMessage = "ERROR: Malformed packet. Missing: 'source`";
    std::cerr << errorMessage << std::endl;

    throw std::runtime_error(errorMessage);
  }
  const auto source = doc["messagePacket"]["source"].GetString();

  if (!msgPacketRoot.HasMember("destination")) {
    std::string errorMessage = "ERROR: Malformed packet. Missing: 'destination`";
    std::cerr << errorMessage << std::endl;

    throw std::runtime_error(errorMessage);
  }
  const auto destination = doc["messagePacket"]["destination"].GetString();

  if (!msgPacketRoot.HasMember("source")) {
    std::string errorMessage = "ERROR: Malformed packet. Missing: 'uuid`";
    std::cerr << errorMessage << std::endl;

    throw std::runtime_error(errorMessage);
  }
  const auto id = uuids::uuid::from_string(doc["messagePacket"]["uuid"].GetString()).value();

  if (!msgPacketRoot.HasMember("timestamp")) {
    std::string errorMessage = "ERROR: Malformed packet. Missing: 'timestamp`";
    std::cerr << errorMessage << std::endl;

    throw std::runtime_error(errorMessage);
  }
  const auto timestamp = stringToTime_t(doc["messagePacket"]["timestamp"].GetString());

  if (!msgPacketRoot.HasMember("messageType")) {
    std::string errorMessage = "ERROR: Malformed packet. Missing: 'messagetype`";
    std::cerr << errorMessage << std::endl;

    throw std::runtime_error(errorMessage);
  }
  const auto messageType = static_cast<MessageType>(doc["messagePacket"]["messageType"].GetInt());

  //const std::string payloadStr = doc["messagePacket"]["data"].GetString();

  // Call deserialize method for specific message type
  //const std::shared_ptr<IMessagePayload> payload{getDispatchTable()[messageType](payloadStr)};

  return {source, destination, id, timestamp, messageType, nullptr};
}

MessagePacket::MessagePacket(const std::string& source,
                             const std::string& destination,
                             const uuids::uuid& id,
                             const std::time_t& timestamp,
                             MessageType messageType,
                             std::shared_ptr<IMessagePayload> messagePayload):
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

const std::string& MessagePacket::getSource() const {
  return m_source;
}

void MessagePacket::setDestination(const std::string& destination) {
  m_destination = destination;
}

const std::string& MessagePacket::getDestination() const {
  return m_destination;
}

void MessagePacket::setId(const uuids::uuid& id) {
  m_id = id;
}

const uuids::uuid& MessagePacket::getId() const {
  return m_id;
}

void MessagePacket::setTimestamp(const std::time_t& timestamp) {
  m_timestamp = timestamp;
}

const std::time_t& MessagePacket::getTimestamp() const {
  return m_timestamp;
}

void MessagePacket::setMessageType(MessageType type) {
  m_messageType = type;
}

MessageType MessagePacket::getMessageType() const {
  return m_messageType;
}

const std::shared_ptr<const IMessagePayload> MessagePacket::getPayload() const {
  return m_payload;
}
