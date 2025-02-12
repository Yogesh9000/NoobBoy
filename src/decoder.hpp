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
      case 0x00: executor.template Execute<0x00>(state, bus); break;
      case 0x01: executor.template Execute<0x01>(state, bus); break;
      case 0x02: executor.template Execute<0x02>(state, bus); break;
      case 0x03: executor.template Execute<0x03>(state, bus); break;
      case 0x04: executor.template Execute<0x04>(state, bus); break;
      case 0x05: executor.template Execute<0x05>(state, bus); break;
      case 0x06: executor.template Execute<0x06>(state, bus); break;
      case 0x07: executor.template Execute<0x07>(state, bus); break;
      case 0x08: executor.template Execute<0x08>(state, bus); break;
      case 0x09: executor.template Execute<0x09>(state, bus); break;
      case 0x0A: executor.template Execute<0x0A>(state, bus); break;
      case 0x0B: executor.template Execute<0x0B>(state, bus); break;
      case 0x0C: executor.template Execute<0x0C>(state, bus); break;
      case 0x0D: executor.template Execute<0x0D>(state, bus); break;
      case 0x0E: executor.template Execute<0x0E>(state, bus); break;
      case 0x0F: executor.template Execute<0x0F>(state, bus); break;
      default:
        throw NotImplemented(std::format("{}Unable to decode instruction {}{:#04x}{}\n", RED, BOLDRED, opcode, RESET));
    }
  }
};
