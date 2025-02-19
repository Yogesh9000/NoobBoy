#include "executor.hpp"
#include "bus.hpp"
#include "common.hpp"
#include <format>

void Executor::DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus)
{
  switch (opcode)
  {
    default:
      throw NotImplemented(std::format("{}Unable to execute instruction {}{:#04x}{}", RED, BOLDRED, opcode, RESET));
  }
}
