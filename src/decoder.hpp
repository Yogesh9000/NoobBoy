#pragma once

#include "bus.hpp"
#include "common.hpp"
#include "executor.hpp"
#include <cstdint>

class Decoder
{
public:
  void DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus, Executor &executor);
};
