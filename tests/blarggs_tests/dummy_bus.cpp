#include "dummy_bus.hpp"
#include "simple_bus.hpp"
#include <cstdint>
#include <string>

uint8_t DummyBus::Read(uint16_t addr)
{
  if (addr == 0xFF44)
  {
    return 0x90;
  }
  else
  {
    return SimpleBus::Read(addr);
  }
}

void DummyBus::Write(uint16_t addr, uint8_t data)
{
  // Blarggs test rom write result to serial port so we check for that
  if (addr == 0xFF02 && data == 0x81)
  {
    m_message += static_cast<char>(Read(0xFF01));
    SimpleBus::Write(addr, 0);
  }
  else
  {
    SimpleBus::Write(addr, data);
  }
}


[[nodiscard]] bool DummyBus::IsTestPassed() const
{

  return (m_message.find("Passed") != std::string::npos);
}

[[nodiscard]] bool DummyBus::IsTestCompleted() const
{
  return ((m_message.find("Passed") != std::string::npos) || (m_message.find("Failed") != std::string::npos));
}

[[nodiscard]] std::string DummyBus::GetMessage() const
{
  return m_message;
}
