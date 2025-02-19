#pragma once

#include "bus.hpp"
#include "common.hpp"
#include <cstdint>

class Executor
{
public:
  void DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus);
};
