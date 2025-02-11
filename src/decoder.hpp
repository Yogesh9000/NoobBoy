#pragma once

#include "common.hpp"
#include <cstdint>
#include <format>
#include <iostream>

template<typename CpuStateT, typename BusT, template<typename, typename> class ExecutorT> class Decoder
{
public:
  void DecodeAndExecute(uint8_t opcode, CpuStateT &state, BusT &bus, ExecutorT<CpuStateT, BusT> &executor)
  {
    switch (opcode)
    {
      default:
        throw NotImplemented(std::format("{}Unable to decode instruction {}{:#04x}{}\n", RED, BOLDRED, opcode, RESET));
    }
  }
};
