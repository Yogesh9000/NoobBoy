#pragma once

#include <array>
#include <cstdint>
#include "bus.hpp"

constexpr int MEMORY_SIZE = 0xFFFF;

class DummyBus : public Bus
{
public:
  ~DummyBus() override = default;
  // Read 1 byte of data from given address
  uint8_t Read(uint16_t addr) override;

  // write 1 byte of data at given location
  void Write(uint16_t addr, uint8_t data) override;

  uint8_t& Address(uint16_t addr) override;

  // reset all memory location to zero
  void Reset() override;

  // request a interrupt to cpu
  void RequestInterrupt(uint8_t id) override;

private:
  std::array<uint8_t, MEMORY_SIZE> m_memory;
};
