#include "simple_bus.hpp"
#include <cstdint>

uint8_t SimpleBus::Read(uint16_t addr)
{
  return m_memory[addr];
}

void SimpleBus::Write(uint16_t addr, uint8_t data)
{
  m_memory[addr] = data;
}

void SimpleBus::Reset()
{
  m_memory.fill(0);
}
