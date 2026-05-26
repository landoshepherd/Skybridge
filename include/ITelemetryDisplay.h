//
// Created by Lando Shepherd on 5/25/26.
//

#ifndef SKYBRIDGE_ITELEMETRYDISPLAY_H
#define SKYBRIDGE_ITELEMETRYDISPLAY_H

#include <string>

struct TelemetryData {
  double altitude;
  std::string gpsStatus;
  double batteryVoltage;
};

class ITelemetryDisplay {
public:
  virtual void updateDisplay(const TelemetryData& data) = 0;
  virtual ~ITelemetryDisplay() = default;

private:
};

#endif //SKYBRIDGE_ITELEMETRYDISPLAY_H