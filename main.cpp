#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "include/ITelemetryDisplay.h"
#include "include/TerminalDisplay.h"

int main(int argc, char *argv[]) {
    const TelemetryData data {
      .altitude = 345.27,
      .gpsStatus = "Nominal",
      .batteryVoltage = 3.7
    };

    const std::shared_ptr<ITelemetryDisplay> display = std::make_shared<TerminalDisplay>();

    for (int i = 0; i < 8; i++){
      display->updateDisplay(data);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}