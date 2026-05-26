//
// Created by Lando Shepherd on 5/26/26.
//

#include "include/ThreadSafeQueue.h"

ThreadSafeQueue &ThreadSafeQueue::getInstance() {
  static ThreadSafeQueue singleton;
  return singleton;
}

void ThreadSafeQueue::push(TelemetryData &data) {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_dataQueue.push(std::move(data));
  m_dataCond.notify_one();
}

void ThreadSafeQueue::waitAndPop() {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_dataCond.wait(lock, [this]{return !m_dataQueue.empty();});
  m_dataQueue.pop();
}

void ThreadSafeQueue::waitAndPop(TelemetryData& data) {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_dataCond.wait(lock, [this]{return !m_dataQueue.empty();});
  data = m_dataQueue.front();
  m_dataQueue.pop();
}

bool ThreadSafeQueue::tryPop() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_dataQueue.empty()) {
    m_dataQueue.pop();
    return true;
  }
  return false;
}

TelemetryData& ThreadSafeQueue::front() {
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_dataQueue.front();
}

bool ThreadSafeQueue::empty() {
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_dataQueue.empty();
}

int ThreadSafeQueue::count() {
  std::lock_guard<std::mutex> lock(m_mutex);
  return static_cast<int>(m_dataQueue.size());
}