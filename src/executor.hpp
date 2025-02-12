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
    if constexpr (Opcode == 0x00)
    {
      state.t_cycles += 4;
    }
    else if constexpr (Opcode == 0x01)
    {
      auto lsb = bus.Read(state.PC.reg++);
      auto msb = bus.Read(state.PC.reg++);
      state.BC.reg = ToU16(msb, lsb);
      state.t_cycles += 12;
    }
    else if constexpr (Opcode == 0x02)
    {
      bus.Write(state.BC.reg, state.AF.high);
      state.t_cycles += 8;
    }
    else if constexpr (Opcode == 0x03)
    {
      ++state.BC.reg;
      state.t_cycles += 8;
    }
    else if constexpr (Opcode == 0x04)
    {
      uint16_t res = state.BC.high + 1;

      SetH(state, (res & (1U << 4U)) != (state.BC.high & (1U << 4U)));
      SetN(state, false);
      SetZ(state, (res & 0xFFU) == 0);

      state.BC.high = (res & 0xFFU);
      state.t_cycles += 4;
    }
    else if constexpr (Opcode == 0x05)
    {
      auto res = state.BC.high - 1;

      SetH(state, (res & (1U << 4U)) != (state.BC.high & (1U << 4U)));
      SetN(state, true);
      SetZ(state, res == 0);

      state.BC.high = res;
      state.t_cycles += 4;
    }
    else if constexpr (Opcode == 0x06)
    {
      state.BC.high = bus.Read(state.PC.reg++);
      state.t_cycles += 8;
    }
    else if constexpr (Opcode == 0x07)
    {
      SetZ(state, false);
      SetN(state, false);
      SetH(state, false);
      SetCY(state, (state.AF.high & (1U << 7U)) >> 7U);

      state.AF.high = state.AF.high << 1U;
      state.AF.high = ((state.AF.high & ~(1U << 0U)) | ((state.AF.low & (1U << 4U)) >> 4U));

      state.t_cycles += 4;
    }
    else
    {
      throw NotImplemented(std::format("{}Unable to execute instruction {}{:#04x}{}\n", RED, BOLDRED, Opcode, RESET));
    }
  }

private:
  uint16_t ToU16(uint8_t msb, uint8_t lsb)
  {
    return static_cast<uint16_t>(msb << 8U) | lsb;
  }

  void SetZ(CpuStateT &state, bool value)
  {
    state.AF.low = (state.AF.low & ~(1U << 7U)) | (static_cast<uint8_t>(value) << 7U);
  }

  void SetN(CpuStateT &state, bool value)
  {
    state.AF.low = (state.AF.low & ~(1U << 6U)) | (static_cast<uint8_t>(value) << 6U);
  }

  void SetH(CpuStateT &state, bool value)
  {
    state.AF.low = (state.AF.low & ~(1U << 5U)) | (static_cast<uint8_t>(value) << 5U);
  }

  void SetCY(CpuStateT &state, bool value)
  {
    state.AF.low = (state.AF.low & ~(1U << 4U)) | (static_cast<uint8_t>(value) << 4U);
  }
};
