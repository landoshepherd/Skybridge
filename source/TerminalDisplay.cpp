//
// Created by Lando Shepherd on 5/25/26.
//

#include "include/TerminalDisplay.h"

#include <iostream>
#include <iomanip>

void TerminalDisplay::updateDisplay(const MessagePacket &data) {

  std::cout << "SOURCE: " << data.getSource() << "\n";
  std::cout << "DESTINATION: " << data.getDestination() << "\n";
  std::cout << "ID: " << data.getId() << "\n";
  std::cout << "TIMESTAMP: " << data.getTimestamp() << std::endl;
  std::cout << "*****************************************" << std::endl;
}



