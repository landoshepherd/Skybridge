#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "include/ITelemetryDisplay.h"
#include "include/TerminalDisplay.h"


int main(int argc, char *argv[]) {
    const TelemetryData data {
      .gpsStatus = GPSStatus::OPERATIONAL,
      .latitude = 27.849293,
      .longitude = -82.114077,
      .altitude = 345.2,
      .groundSpeed = 10,
      .rateOfClimb = 3,
      .batteryVoltage = 3.7,
      .time = "12:59"
    };

    const std::shared_ptr<ITelemetryDisplay> display = std::make_shared<TerminalDisplay>();

    for (int i = 0; i < 8; i++){
      display->updateDisplay(data);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}