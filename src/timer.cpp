#include "timer.hpp"
#include "bus.hpp"

Timer::Timer(Bus &bus) : m_bus(bus)
{
}

void Timer::Tick(int cycles)
{
  UpdateTimers(cycles);
}


void Timer::UpdateDividerRegister(int cycles)
{
  m_dividerCounter += cycles;
  if (m_dividerCounter > 255)
  {
    m_dividerCounter = 0;
    auto div = m_bus.Address(0xFF04);
    ++div;
  }
}

void Timer::UpdateTimers(int cycles)
{
  UpdateDividerRegister(cycles);

  auto tima = m_bus.Address(0xFF05);
  auto tma = m_bus.Address(0xFF06);

  // Update the frequency at which TIMA is incremented
  if (m_timerFreq != GetClockFreq())
  {
    SetClockFreq();
  }

  // the clock must be enabled to update the clock 
  if (IsClockEnabled())
  {
    m_timerCounter -= cycles; 

    // enough cpu clock cycles have happened to update the timer
    if (m_timerCounter <= 0)
    {
      SetClockFreq();
      if (tima == 255)
      {
        tima = tma;
        m_bus.RequestInterrupt(2);
      }
      else
      {
        ++tima;
      }
    }
  }
}


uint8_t Timer::GetClockFreq()
{
  constexpr uint16_t TAC {0xFF07U};
  return m_bus.Read(TAC) & 0x03U;
}

void Timer::SetClockFreq()
{
  auto freq = GetClockFreq();
  switch (freq)
  {
    case 0: m_timerCounter = 1024;break;
    case 1: m_timerCounter = 16;break;
    case 2: m_timerCounter = 64;break;
    case 3: m_timerCounter = 256;break;
    default: /* Unreachable */ break;
  }
}

bool Timer::IsClockEnabled()
{
  constexpr uint16_t TAC {0xFF07U};
  return (m_bus.Read(TAC) & (1U << 2U)) != 0;
}
