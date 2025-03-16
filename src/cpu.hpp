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

private:
  void HandleInterrupts();

  // helper methods
  void SetInitialState();

  // internal state of cpu
  CpuState m_state{};
  Bus &m_bus;
  Executor  m_executor{};
};
