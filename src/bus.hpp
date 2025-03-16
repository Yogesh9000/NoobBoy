#pragma once

#include <cstdint>

class Bus
{
public:
  virtual ~Bus() = default;
  // Read 1 byte of data from given address
  virtual uint8_t Read(uint16_t addr) = 0;

  // write 1 byte of data at given location
  virtual void Write(uint16_t addr, uint8_t data) = 0;

  // Get's a reference to given memory location
  virtual uint8_t& Address(uint16_t addr) = 0;

  // reset all memory location to zero
  virtual void Reset() = 0;

  // request a interrupt to cpu
  virtual void RequestInterrupt(uint8_t id) = 0;
};
