#include "simple_bus.hpp"
#include <cstdint>

uint8_t SimpleBus::Read(uint16_t addr)
{
  return m_memory[addr];
}

void SimpleBus::Write(uint16_t addr, uint8_t data)
{
  constexpr int DIV{ 0xFF04 };

  if (addr == DIV) // Explcitily writing to DIV register reset's it to zero
  {
    m_memory[DIV] = 0;
  }
  else
  {
    m_memory[addr] = data;
  }
}

uint8_t& SimpleBus::Address(uint16_t addr)
{
  return m_memory[addr];
}

void SimpleBus::Reset()
{
  m_memory.fill(0);
}

void SimpleBus::RequestInterrupt(uint8_t id)
{
  uint8_t IF = Address(0xFF0F);
  IF |= (1U << id);
}
