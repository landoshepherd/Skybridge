//
// Created by Lando Shepherd on 5/25/26.
//

#ifndef SKYBRIDGE_TERMINALDISPLAY_H
#define SKYBRIDGE_TERMINALDISPLAY_H
#include "interfaces/ITelemetryDisplay.h"

class TerminalDisplay : public ITelemetryDisplay {
public:
  TerminalDisplay() = default;
  ~TerminalDisplay() override = default;

  void updateDisplay(const MessagePacket &data) override;
  void updateVehicleTelemetryDisplay(const std::shared_ptr<const IMessagePayload> payload);
private:
};

#endif //SKYBRIDGE_TERMINALDISPLAY_H