#include "bus.hpp"
#include <cstdint>

uint8_t Bus::Read(uint16_t addr)
{
  return m_memory[addr];
}

void Bus::Write(uint16_t addr, uint8_t data)
{
  m_memory[addr] = data;
}

void Bus::Reset()
{
  m_memory.fill(0);
}
