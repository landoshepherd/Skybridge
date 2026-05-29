//
// Created by Lando Shepherd on 5/28/26.
//

#ifndef SKYBRIDGE_IMESSAGEPAYLOAD_H
#define SKYBRIDGE_IMESSAGEPAYLOAD_H

#include <string>

class IMessagePayload {
public:
  virtual std::string serialize() = 0;

  // Move constructor
  IMessagePayload(IMessagePayload&&) = default;

  // Copy assignment
  IMessagePayload& operator=(IMessagePayload&) = delete;

  // Move assignment operator
  IMessagePayload& operator=(IMessagePayload&&) = default;

  // Copy constructor
  IMessagePayload(IMessagePayload&) = delete;

  // Destructor
  virtual ~IMessagePayload() = default;
private:
};
#endif //SKYBRIDGE_IMESSAGEPAYLOAD_H