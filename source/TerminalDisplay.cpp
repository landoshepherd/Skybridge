//
// Created by Lando Shepherd on 5/25/26.
//

#include "include/TerminalDisplay.h"

#include <iostream>

void TerminalDisplay::updateDisplay(const TelemetryData &data) {
  std::cout << "Altitude:        " << data.altitude << std::endl;
  std::cout << "GPS Status:      " << data.gpsStatus << std::endl;
  std::cout << "Battery Voltage: " << data.batteryVoltage << std::endl;
  std::cout << "*****************************************" << std::endl;
}



