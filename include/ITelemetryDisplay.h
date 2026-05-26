//
// Created by Lando Shepherd on 5/25/26.
//

#ifndef SKYBRIDGE_ITELEMETRYDISPLAY_H
#define SKYBRIDGE_ITELEMETRYDISPLAY_H

#include <string>
enum class GPSStatus {
  OPERATIONAL,
  DOWN
};

struct TelemetryData {
  GPSStatus   gpsStatus;
  double      latitude;
  double      longitude;
  double      altitude;
  double      groundSpeed;
  double      rateOfClimb;
  double      batteryVoltage;
  std::string time;
};

class ITelemetryDisplay {
public:
  virtual void updateDisplay(const TelemetryData& data) = 0;
  virtual ~ITelemetryDisplay() = default;

private:
};

#endif //SKYBRIDGE_ITELEMETRYDISPLAY_H