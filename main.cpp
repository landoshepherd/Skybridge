#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "include/ITelemetryDisplay.h"
#include "include/TerminalDisplay.h"
#include "include/ThreadSafeQueue.h"
#include "include/AmqClient.h"

void processData(const std::shared_ptr<ITelemetryDisplay>& terminalDisplay) {
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

    TelemetryData data {
      .gpsStatus = GPSStatus::OPERATIONAL,
      .latitude = 27.849293,
      .longitude = -82.114077,
      .altitude = 345.2,
      .groundSpeed = 10,
      .rateOfClimb = 3,
      .batteryVoltage = 3.7,
      .time = "12:59"
    };

    queue.push(data);
  }
}

int main(int argc, char *argv[]) {
  AmqClient client("localhost:5672", "admin", "admin");
  proton::container container(client);
  std::thread container_thread([&]() {container.run();});

  // Allow for the connection to be made before moving on
  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::thread sender([&]() {
    proton::message msg("Lando sent this");
    msg.creation_time(proton::timestamp::now());
    client.send(msg);
  });

  std::thread receiver([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    auto msg = client.receive();
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