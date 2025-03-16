#pragma once

#include "common.hpp"
#include "bus.hpp"
#include "executor.hpp"
#include <cstdint>

class Cpu
{
public:
  explicit Cpu(Bus &bus);

  // Get current cpu state
  [[nodiscard]] CpuState GetState() const;

  // Set current cpu state
  void SetState(const CpuState &state);

  // Reset Cpu state to initial state
  void ResetState();

  int Tick();

  void RequestInterrupt(uint8_t id);

private:
  void HandleInterrupts();
  void UpdateTimers();
  void UpdateDividerRegister();

  // helper methods
  void SetInitialState();
  uint8_t GetClockFreq();
  void SetClockFreq();
  bool IsClockEnabled();

  // internal state of cpu
  CpuState m_state{};
  Bus &m_bus;
  Executor  m_executor{};

  uint64_t m_cycles{0}; // cycles taken by last instruction to execute
  int m_timerFreq{0};
  int m_timerCounter{1024};
  int m_dividerCounter{0};
};
