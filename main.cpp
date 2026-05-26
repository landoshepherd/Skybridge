#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "include/ITelemetryDisplay.h"
#include "include/TerminalDisplay.h"
#include "include/ThreadSafeQueue.h"

void processData() {

}

void prepareData(ThreadSafeQueue& queue) {

}

int main(int argc, char *argv[]) {
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

    const std::shared_ptr<ITelemetryDisplay> terminalDisplay = std::make_shared<TerminalDisplay>();
    ThreadSafeQueue& queue = ThreadSafeQueue::getInstance();

    queue.push(data);

    std::cout << "Queue Count: " << queue.count() << std::endl;

    TelemetryData& front = queue.front();
    terminalDisplay->updateDisplay(front);
    queue.waitAndPop();

    std::cout << "Queue Count: " << queue.count() << std::endl;

    if (queue.empty()) {
      std::cout << "Queue is empty" << std::endl;
    }


    return 0;
}