#include "dummy_bus.hpp"
#include <cstdint>

uint8_t DummyBus::Read(uint16_t addr)
{
  return m_memory[addr];
}

void DummyBus::Write(uint16_t addr, uint8_t data)
{
  m_memory[addr] = data;
}

uint8_t& DummyBus::Address(uint16_t addr)
{
  return m_memory[addr];
}

void DummyBus::Reset()
{
  m_memory.fill(0);
}

void DummyBus::RequestInterrupt(uint8_t id)
{
  uint8_t IF = Address(0xFF0F);
  IF |= (1U << id);
}
