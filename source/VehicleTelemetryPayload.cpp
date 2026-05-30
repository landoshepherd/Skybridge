//
// Created by Lando Shepherd on 5/27/26.
//

#include "include/VehicleTelemetryPayload.h"

#include "simdjson.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "include/MessagePacket.h"
#include "rapidjson/document.h"

struct DeserializerRegister {
  void doRegistration(const std::function<IMessagePayload*(const std::string&)>& deserializer) {
    MessagePacket::registerDeserializer(MessageType::VEHICLE_TELEMETRY, deserializer);
  }

  DeserializerRegister(const std::function<IMessagePayload*(const std::string&)>& deserializer) {
      doRegistration(deserializer);
  }
};

static DeserializerRegister reg(VehicleTelemetryPayload::deserialize);

VehicleTelemetryPayload::VehicleTelemetryPayload(GPSStatus status,
                                                 const double& latitude,
                                                 const double& longitude,
                                                 const double& altitude,
                                                 const double& groundSpeed,
                                                 const double& rateOfClimb,
                                                 const double& batteryVoltage):
m_gpsStatus(status),
m_latitude(latitude),
m_longitude(longitude),
m_altitude(altitude),
m_groundSpeed(groundSpeed),
m_rateOfClimb(rateOfClimb),
m_batteryVoltage(batteryVoltage)
{

}

std::string VehicleTelemetryPayload::serialize() {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.Key("data");
  writer.StartObject();
  writer.Key("gpsStatus");
  writer.Int(static_cast<int>(m_gpsStatus)); // TODO: Convert the gpsstatus enums to strings

  writer.Key("latitude");
  writer.Double(m_latitude);

  writer.Key("longitude");
  writer.Double(m_longitude);

  writer.Key("altitude");
  writer.Double(m_altitude);

  writer.Key("groundSpeed");
  writer.Double(m_groundSpeed);

  writer.Key("rateOfClime");
  writer.Double(m_rateOfClimb);

  writer.Key("batteryVoltage");
  writer.Double(m_batteryVoltage);

  writer.EndObject();

  return buffer.GetString();
}

IMessagePayload* VehicleTelemetryPayload::deserialize(const std::string& payloadStr) {
  rapidjson::Document doc;
  doc.Parse(payloadStr.c_str());

  if (doc.HasParseError()) {
    std::cerr << "ERROR: Failed to parse message" << std::endl;
  }

  auto gpsStatus = static_cast<GPSStatus>(doc["messagePacket"]["data"]["gpsStatus"].GetInt());
  double latitude = doc["messagePacket"]["data"]["latitude"].GetDouble();
  double longitude = doc["messagePacket"]["data"]["longitude"].GetDouble();
  double altitude = doc["messagePacket"]["data"]["altitude"].GetDouble();
  double groundSpeed = doc["messagePacket"]["data"]["groundSpeed"].GetDouble();
  double rateOfClimb = doc["messagePacket"]["data"]["rateOfClimb"].GetDouble();
  double batteryVoltage = doc["messagePacket"]["data"]["batteryVoltage"].GetDouble();

  IMessagePayload* payload = new VehicleTelemetryPayload(gpsStatus, latitude, longitude, altitude, groundSpeed, rateOfClimb, batteryVoltage);

  return payload;
}

void VehicleTelemetryPayload::updateGPSStatus(GPSStatus status) {
  m_gpsStatus = status;
}

GPSStatus VehicleTelemetryPayload::getGPSStatus() const {
  return m_gpsStatus;
}

void VehicleTelemetryPayload::updateLatitude(double latitude) {
  m_latitude = latitude;
}

double VehicleTelemetryPayload::getLatitude() const {
  return m_latitude;
}

void VehicleTelemetryPayload::updateLongitude(double longitude) {
  m_longitude = longitude;
}

double VehicleTelemetryPayload::getLongitude() const {
  return m_longitude;
}

void VehicleTelemetryPayload::updateAltitude(double altitude) {
  m_altitude = altitude;
}

double VehicleTelemetryPayload::getAltitude() const {
  return m_altitude;
}

void VehicleTelemetryPayload::updateGroundSpeed(double groundSpeed) {
  m_groundSpeed = groundSpeed;
}

double VehicleTelemetryPayload::getGroundSpeed() const {
  return m_groundSpeed;
}

void VehicleTelemetryPayload::updateRateOfClimb(double rateOfClimb) {
  m_rateOfClimb = rateOfClimb;
}

double VehicleTelemetryPayload::getRateOfClimb() const {
  return m_rateOfClimb;
}

void VehicleTelemetryPayload::updateBatteryVoltage(double batteryVoltage) {
  m_batteryVoltage = batteryVoltage;
}

double VehicleTelemetryPayload::getBatteryVoltage() const {
  return m_batteryVoltage;
}