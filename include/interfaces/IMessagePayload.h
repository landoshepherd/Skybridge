//
// Created by Lando Shepherd on 5/28/26.
//

#ifndef SKYBRIDGE_IMESSAGEPAYLOAD_H
#define SKYBRIDGE_IMESSAGEPAYLOAD_H

#include <string>

class IMessagePayload {
public:
  virtual std::string serialize() = 0;

  // Allow default construction for derived classes
  IMessagePayload() = default;

  // Destructor
  virtual ~IMessagePayload() = default;

  // Delete copy constructor and assignment to prevent object slicing
  IMessagePayload(const IMessagePayload&) = delete;
  IMessagePayload& operator=(const IMessagePayload&) = delete;

  // Delete move constructor and assignment to prevent object slicing
  IMessagePayload(IMessagePayload&&) = delete;
  IMessagePayload& operator=(IMessagePayload&&) = delete;
private:

};
#endif //SKYBRIDGE_IMESSAGEPAYLOAD_H