#pragma once

#include "bus.hpp"
class Timer
{
public:
  explicit Timer(Bus &bus);
  void Tick(int cycles);

private:
  void UpdateDividerRegister(int cycles);
  void UpdateTimers(int cycles);
  int GetClockFreq();
  bool IsClockEnabled();

  Bus &m_bus;

  int m_timerCounter{0};
  int m_dividerCounter{0};
};
