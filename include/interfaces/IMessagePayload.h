//
// Created by Lando Shepherd on 5/28/26.
//

#ifndef SKYBRIDGE_IMESSAGEPAYLOAD_H
#define SKYBRIDGE_IMESSAGEPAYLOAD_H

#include <string>

class IMessagePlayload {
public:
  virtual std::string serialize() = 0;
  virtual ~IMessagePlayload() = default;
private:
};
#endif //SKYBRIDGE_IMESSAGEPAYLOAD_H