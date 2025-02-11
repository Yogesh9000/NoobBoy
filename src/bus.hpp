#pragma once

#include <array>
#include <cstdint>

constexpr int MEMORY_SIZE = 0xFFFF;

class Bus
{
public:
  // Read 1 byte of data from given address
  uint8_t Read(uint16_t addr);

  // write 1 byte of data at given location
  void Write(uint16_t addr, uint8_t data);

  // reset all memory location to zero
  void Reset();

private:
  std::array<uint8_t, MEMORY_SIZE> m_memory;
};
