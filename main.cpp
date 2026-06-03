#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "include/interfaces/ITelemetryDisplay.h"
#include "include/TerminalDisplay.h"
#include "include/ThreadSafeQueue.h"
#include "include/AmqClient.h"
#include "rapidjson/document.h"
#include "include/VehicleTelemetryPayload.h"

std::string data = R"(
  {
    "messagePacket":{
      "source": "me",
      "destination": "you",
      "uuid": "d47e32b8-936a-4b21-b1e8-724f11d293c6",
      "timestamp": "1999-12-31T11:59:59",
      "messageType": 1,
      "payload":{
        "gpsStatus": 3,
        "latitude": 32.7555,
        "longitude": -97.3308,
        "altitude": 152.4,
        "groundSpeed": 12.5,
        "rateOfClimb": 1.2,
        "batteryVoltage": 11.4
      }
    }
  }
)";

void receiveMessages(AmqClient& client) {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  proton::message msg = client.receive();

  const auto body = proton::get<std::string>(msg.body());

  try {
    MessagePacket packet = MessagePacket::deserialize(to_string(msg.body()));
    ThreadSafeQueue::getInstance().push(packet);
  }
  catch (std::exception& ex) {
    std::cout << "Error Processing received message. Message tossed. Recovering..." << std::endl;
  }
}

void displayData(AmqClient& client) {
  TerminalDisplay terminal;

  while (true) {
    MessagePacket newMessage;
    ThreadSafeQueue::getInstance().waitAndPop(newMessage);

    terminal.updateDisplay(newMessage);
  }
}

int main(int argc, char *argv[]) {
  // Connect to the amq server
  // TODO: Make this configurable via a configuration file
  AmqClient client("localhost:5672", "admin", "admin");
  proton::container container(client);
  std::thread container_thread([&]() {container.run();});

  // Wait a second to allow for the connection to be made before moving on
  // TODO: Is there a way we can wait for a specific condition instead
  std::this_thread::sleep_for(std::chrono::seconds(1));

  // Start processor
  std::thread dataDisplayThread([&]() {
    displayData(client);
  });

  // Start receiver
  std::thread receiverThread([&]() {
    receiveMessages(client);
  });

  // Send a message
  proton::message msg(data);
  msg.creation_time(proton::timestamp::now());

  // TODO: The send invocation should not be here. It should be deleted and called
  //  only when we send commands or heartbeats from the client
  client.send(msg);

  receiverThread.join();
  dataDisplayThread.join();
  container_thread.join();

  return 0;
}