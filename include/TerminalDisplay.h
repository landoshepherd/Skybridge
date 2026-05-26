//
// Created by Lando Shepherd on 5/25/26.
//

#ifndef SKYBRIDGE_TERMINALDISPLAY_H
#define SKYBRIDGE_TERMINALDISPLAY_H
#include "ITelemetryDisplay.h"

class TerminalDisplay : public ITelemetryDisplay {
public:
  TerminalDisplay() = default;
  ~TerminalDisplay() override = default;

  void updateDisplay(const TelemetryData &data) override;
private:
};

#endif //SKYBRIDGE_TERMINALDISPLAY_H