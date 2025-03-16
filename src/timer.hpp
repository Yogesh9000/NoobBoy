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
  uint8_t GetClockFreq();
  void SetClockFreq();
  bool IsClockEnabled();

  Bus &m_bus;

  int m_timerFreq{0};
  int m_timerCounter{1024};
  int m_dividerCounter{0};
};
