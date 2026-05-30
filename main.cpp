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

/*void processData(const std::shared_ptr<ITelemetryDisplay>& terminalDisplay) {
  ThreadSafeQueue& queue = ThreadSafeQueue::getInstance();

  while (true) {
    TelemetryData newData;

    // Waits for data to appear in the queue
    queue.waitAndPop(newData);
    std::cout << "Main thread: Processing..." << std::endl;
    terminalDisplay->updateDisplay(newData);
  }
}

void receiveData() {
  ThreadSafeQueue& queue = ThreadSafeQueue::getInstance();
  while (true) {
    std::cout << "Data Receiver: LISTENING" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Data Receiver: DATA RECEIVED!" << std::endl;

    VehicleTelemetryMessage data {
      .gpsStatus = GPSStatus::OPERATIONAL,
      .latitude = 27.849293,
      .longitude = -82.114077,
      .altitude = 345.2,
      .groundSpeed = 10,
      .rateOfClimb = 3,
      .batteryVoltage = 3.7,
    };

    queue.push(data);
  }
}*/

std::string data = R"(
  {
    "messagePacket":{
      "source": "me",
      "destination": "you",
      "uuid": "d47e32b8-936a-4b21-b1e8-724f11d293c6",
      "timestamp": "1999-12-31T11:59:59",
      "messageType": 1,
      "data":{
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

int main(int argc, char *argv[]) {
  // Connect to the amqp router
  AmqClient client("localhost:5672", "admin", "admin");
  proton::container container(client);
  std::thread container_thread([&]() {container.run();});

  // Allow for the connection to be made before moving on
  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::thread sender([&]() {
    // TODO: Wrap telemetry data into Message packet then serialize it
    proton::message msg(data);
    msg.creation_time(proton::timestamp::now());
    client.send(msg);
  });

  std::thread receiver([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    proton::message msg = client.receive();

    // TODO: Deserialize msg.data into VehicleTelemetryMessage here
    const auto body = proton::get<std::string>(msg.body());

    try {
      const MessagePacket packet = MessagePacket::deserialize(to_string(msg.body()));
      /*
      TODO: Move this activity to it's own thread. This thread is only for
        receiving messages and putting them on the queue.
      */
      TerminalDisplay display;
      display.updateDisplay(packet);
    }
    catch (std::exception& ex) {
      std::cout << "Error Processing received message. Message tossed. Recovering..." << std::endl;
    }



  });

  receiver.join();
  sender.join();
  container_thread.join();

  /*const std::shared_ptr<ITelemetryDisplay> terminalDisplay = std::make_shared<TerminalDisplay>();
  ThreadSafeQueue& queue = ThreadSafeQueue::getInstance();

  // Start new thread that mimics receiving data
  std::thread dataReceiverThread(receiveData);

  // Start data processor thread
  std::thread dataProcessorThread(processData, terminalDisplay);

  if (dataReceiverThread.joinable()) {
    dataReceiverThread.join();
  }

  if (dataProcessorThread.joinable()) {
    dataProcessorThread.join();
  }*/

  return 0;
}