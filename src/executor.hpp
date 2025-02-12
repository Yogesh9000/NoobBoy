#pragma once

#include "bus.hpp"
#include "common.hpp"
#include <cstdint>

class Executor
{
public:
  template<uint8_t Opcode> void Execute(CpuState &state, Bus &bus)
  {
    throw NotImplemented(std::format("{}Unable to execute instruction {}{:#04x}{}\n", RED, BOLDRED, Opcode, RESET));
  }

private:
  // Helper functions
  static uint16_t ToU16(uint8_t msb, uint8_t lsb);
  static void SetZ(CpuState &state, bool value);
  static void SetN(CpuState &state, bool value);
  static void SetH(CpuState &state, bool value);
  static void SetCY(CpuState &state, bool value);
};
