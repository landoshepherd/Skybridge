//
// Created by Lando Shepherd on 5/27/26.
//

#ifndef SKYBRIDGE_VEHICLETELEMETRYPAYLOAD_H
#define SKYBRIDGE_VEHICLETELEMETRYPAYLOAD_H

#include <string>

#include "interfaces/IMessagePayload.h"


enum class GPSStatus {
  OPERATIONAL,
  DOWN
};

struct VehicleTelemetryData {

};

class VehicleTelemetryPayload : public IMessagePlayload {
public:
  VehicleTelemetryPayload(GPSStatus status, const double& latitude, const double& longitude,
                          const double& altitude, const double& groundSpeed,
                          const double& rateOfClimb, const double& batteryVoltage);
  ~VehicleTelemetryPayload() override = default;

  std::string serialize() override;

  // Getters and Setters for individual telemetry fields
  void setGpsStatus(GPSStatus status);
  GPSStatus getGpsStatus() const;

  void setLatitude(double latitude);
  double getLatitude() const;

  void setLongitude(double longitude);
  double getLongitude() const;

  void setAltitude(double altitude);
  double getAltitude() const;

  void setGroundSpeed(double groundSpeed);
  double getGroundSpeed() const;

  void setRateOfClimb(double rateOfClimb);
  double getRateOfClimb() const;

  void setBatteryVoltage(double batteryVoltage);
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