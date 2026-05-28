//
// Created by Lando Shepherd on 5/26/26.
//

#ifndef SKYBRIDGE_THREADSAFEQUEUE_H
#define SKYBRIDGE_THREADSAFEQUEUE_H
#include <mutex>
#include <queue>
#include <condition_variable>

#include "interfaces/ITelemetryDisplay.h"

class ThreadSafeQueue {
public:
  static ThreadSafeQueue &getInstance();

  // Adds element to queue
  void push(MessagePacket& data);

  // Blocking - Will wait until there is an element to pop from queue
  void waitAndPop();

  void waitAndPop(MessagePacket& data);

  // Non-blocking - will try to pop from queue if element exists
  bool tryPop();

  // Peek at the first element of the queue
  MessagePacket& front();

  // Checks if queue is empty
  bool empty();

  // Gets the number of elements in the queue
  int count();

  ~ThreadSafeQueue() = default;

  // Delete copy constructors
  ThreadSafeQueue(ThreadSafeQueue&) = delete;
  ThreadSafeQueue operator=(ThreadSafeQueue&) = delete;

private:
  std::mutex m_mutex;
  std::queue<MessagePacket> m_dataQueue;
  std::condition_variable m_dataCond;

private:
  // Make constructor private
  ThreadSafeQueue() = default;
};
#endif //SKYBRIDGE_THREADSAFEQUEUE_H