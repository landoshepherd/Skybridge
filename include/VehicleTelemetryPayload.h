//
// Created by Lando Shepherd on 5/27/26.
//

#ifndef SKYBRIDGE_VEHICLETELEMETRYPAYLOAD_H
#define SKYBRIDGE_VEHICLETELEMETRYPAYLOAD_H

#include <string>

#include "interfaces/IMessagePayload.h"
#include "rapidjson/document.h"


enum class GPSStatus {
  OPERATIONAL,
  DOWN
};

class VehicleTelemetryPayload : public IMessagePayload {
public:
  VehicleTelemetryPayload(GPSStatus status, const double& latitude, const double& longitude,
                          const double& altitude, const double& groundSpeed,
                          const double& rateOfClimb, const double& batteryVoltage);

  ~VehicleTelemetryPayload() override = default;

  std::string serialize() override;

  static IMessagePayload* deserialize(const rapidjson::Value& payloadStr);

  // Getters and Setters for individual telemetry fields
  void updateGPSStatus(GPSStatus status);
  GPSStatus getGPSStatus() const;

  void updateLatitude(double latitude);
  double getLatitude() const;

  void updateLongitude(double longitude);
  double getLongitude() const;

  void updateAltitude(double altitude);
  double getAltitude() const;

  void updateGroundSpeed(double groundSpeed);
  double getGroundSpeed() const;

  void updateRateOfClimb(double rateOfClimb);
  double getRateOfClimb() const;

  void updateBatteryVoltage(double batteryVoltage);
  double getBatteryVoltage() const;

private:
  GPSStatus   m_gpsStatus;
  double      m_latitude;
  double      m_longitude;
  double      m_altitude;
  double      m_groundSpeed;
  double      m_rateOfClimb;
  double      m_batteryVoltage;
};
#endif //SKYBRIDGE_VEHICLETELEMETRYPAYLOAD_H