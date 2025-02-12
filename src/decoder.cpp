#include "decoder.hpp"
#include <format>


void Decoder::DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus, Executor &executor)
{
  switch (opcode)
  {
    case 0x00: executor.Execute<0x00>(state, bus); break;
    case 0x01: executor.Execute<0x01>(state, bus); break;
    case 0x02: executor.Execute<0x02>(state, bus); break;
    case 0x03: executor.Execute<0x03>(state, bus); break;
    case 0x04: executor.Execute<0x04>(state, bus); break;
    case 0x05: executor.Execute<0x05>(state, bus); break;
    case 0x06: executor.Execute<0x06>(state, bus); break;
    case 0x07: executor.Execute<0x07>(state, bus); break;
    case 0x08: executor.Execute<0x08>(state, bus); break;
    case 0x09: executor.Execute<0x09>(state, bus); break;
    case 0x0A: executor.Execute<0x0A>(state, bus); break;
    case 0x0B: executor.Execute<0x0B>(state, bus); break;
    case 0x0C: executor.Execute<0x0C>(state, bus); break;
    case 0x0D: executor.Execute<0x0D>(state, bus); break;
    case 0x0E: executor.Execute<0x0E>(state, bus); break;
    case 0x0F: executor.Execute<0x0F>(state, bus); break;
    default:
      throw NotImplemented(std::format("{}Unable to decode instruction {}{:#04x}{}\n", RED, BOLDRED, opcode, RESET));
  }
}
