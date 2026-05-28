//
// Created by Lando Shepherd on 5/25/26.
//

#ifndef SKYBRIDGE_ITELEMETRYDISPLAY_H
#define SKYBRIDGE_ITELEMETRYDISPLAY_H

#include <string>
#include "../MessagePacket.h"


class ITelemetryDisplay {
public:
  virtual void updateDisplay(const MessagePacket& data) = 0;
  virtual ~ITelemetryDisplay() = default;

private:
};

#endif //SKYBRIDGE_ITELEMETRYDISPLAY_H