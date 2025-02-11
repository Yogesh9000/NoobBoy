#pragma once

#include <cstdint>
#include <format>
#include <iostream>
#include "common.hpp"

template<typename CpuStateT, typename BusT> class Executor
{
public:
  template<uint8_t Opcode> void Execute(CpuStateT &state, BusT &bus)
  {
    throw NotImplemented(std::format("{}Unable to execute instruction {}{:#04x}{}\n", RED, BOLDRED, Opcode, RESET));
  }

private:
  uint16_t ToU16(uint8_t msb, uint8_t lsb)
  {
    return static_cast<uint16_t>(msb << 8U) | lsb;
  }
};
