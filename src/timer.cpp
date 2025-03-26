#include "timer.hpp"
#include "bus.hpp"
#include <stdexcept>

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
    auto& div = m_bus.Address(0xFF04);
    ++div;
  }
}

void Timer::UpdateTimers(int cycles)
{
  UpdateDividerRegister(cycles);

  auto& tima = m_bus.Address(0xFF05);
  auto& tma = m_bus.Address(0xFF06);

  // the clock must be enabled to update the clock 
  if (IsClockEnabled())
  {
    m_timerCounter += cycles; 

    // enough cpu clock cycles have happened to update the timer
    if (m_timerCounter >= GetClockFreq())
    {
      if (tima >= 255)
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


int Timer::GetClockFreq()
{
  constexpr uint16_t TAC {0xFF07U};
  auto freq =  m_bus.Read(TAC) & 0x03U;
  switch (freq)
  {
    case 0: return  1024;break;
    case 1: return 16;break;
    case 2: return 64;break;
    case 3: return 256;break;
    default: throw std::runtime_error("Unknown Timer Freq"); break;
  }
}

bool Timer::IsClockEnabled()
{
  constexpr uint16_t TAC {0xFF07U};
  return (m_bus.Read(TAC) & (1U << 2U)) != 0;
}
