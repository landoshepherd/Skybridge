//
// Created by Lando Shepherd on 5/25/26.
//

#include "include/TerminalDisplay.h"

#include <iostream>
#include <iomanip>

#include "include/VehicleTelemetryPayload.h"

void TerminalDisplay::updateDisplay(const MessagePacket &data) {

  std::cout << "MESSAGE PACKET" << std::endl;
  std::cout << "SOURCE:       " << data.getSource() << "\n";
  std::cout << "DESTINATION:  " << data.getDestination() << "\n";
  std::cout << "ID:           " << data.getId() << "\n";
  std::cout << "TIMESTAMP:    " << data.getTimestamp() << std::endl;

  updateVehicleTelemetryDisplay(data.getPayload());

  std::cout << "*****************************************" << std::endl;
}

void TerminalDisplay::updateVehicleTelemetryDisplay(const std::shared_ptr<const IMessagePayload> payload) {
  std::shared_ptr<const VehicleTelemetryPayload> data =
    std::static_pointer_cast<const VehicleTelemetryPayload>(payload);

  std::cout << "VEHICLE TELEMETRY\n";
  std::cout << "ALTITUDE:         " << data->getAltitude() << "\n";
  std::cout << "LATITUDE:         " << data->getLatitude() << "\n";
  std::cout << "LONGITUDE:        " << data->getLongitude() << "\n";
  std::cout << "GROUND SPEED:     " << data->getGroundSpeed() << "\n";
  std::cout << "RATE OF CLIMB:    " << data->getRateOfClimb() << "\n";
  std::cout << "BATTERY Voltage:  " << data->getBatteryVoltage() << std::endl;
}

