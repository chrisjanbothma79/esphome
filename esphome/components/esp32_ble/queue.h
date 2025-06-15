#pragma once

#ifdef USE_ESP32

#include <atomic>
#include <cstddef>

/*
 * BLE events come in from a separate Task (thread) in the ESP32 stack. Rather
 * than using mutex-based locking, this lock-free queue allows the BLE
 * task to enqueue events without blocking. The main loop() then processes
 * these events at a safer time.
 *
 * The queue uses atomic operations to ensure thread safety without locks.
 * This prevents blocking the time-sensitive BLE stack callbacks.
 */

namespace esphome {
namespace esp32_ble {

template<class T, size_t SIZE> class LockFreeQueue {
 public:
  LockFreeQueue() : write_index_(0), read_index_(0), size_(0), dropped_count_(0) {}

  bool push(T *element) {
    if (element == nullptr)
      return false;

    size_t current_size = size_.load(std::memory_order_acquire);
    if (current_size >= SIZE - 1) {
      // Buffer full, track dropped event
      dropped_count_.fetch_add(1, std::memory_order_relaxed);
      return false;
    }

    size_t write_idx = write_index_.load(std::memory_order_relaxed);
    size_t next_write_idx = (write_idx + 1) % SIZE;

    // Store element in buffer
    buffer_[write_idx] = element;
    write_index_.store(next_write_idx, std::memory_order_release);
    size_.fetch_add(1, std::memory_order_release);
    return true;
  }

  T *pop() {
    size_t current_size = size_.load(std::memory_order_acquire);
    if (current_size == 0) {
      return nullptr;
    }

    size_t read_idx = read_index_.load(std::memory_order_relaxed);

    // Get element from buffer
    T *element = buffer_[read_idx];
    read_index_.store((read_idx + 1) % SIZE, std::memory_order_release);
    size_.fetch_sub(1, std::memory_order_release);
    return element;
  }

  size_t size() const { return size_.load(std::memory_order_acquire); }

  size_t get_and_reset_dropped_count() { return dropped_count_.exchange(0, std::memory_order_relaxed); }

  void increment_dropped_count() { dropped_count_.fetch_add(1, std::memory_order_relaxed); }

  bool empty() const { return size_.load(std::memory_order_acquire) == 0; }

 protected:
  T *buffer_[SIZE];
  std::atomic<size_t> write_index_;
  std::atomic<size_t> read_index_;
  std::atomic<size_t> size_;
  std::atomic<size_t> dropped_count_;
};

}  // namespace esp32_ble
}  // namespace esphome

#endif
