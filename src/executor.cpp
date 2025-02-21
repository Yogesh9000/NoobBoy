#include "executor.hpp"
#include "bus.hpp"
#include "common.hpp"
#include <cstdint>
#include <format>

void Executor::DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus)
{
  switch (opcode)
  {
    case 0x01: Load_RR_NN(state.BC.reg, state, bus); break;
    case 0x02: Load_BC_A(state, bus); break;
    case 0x06: Load_R_N(state.BC.high, state, bus); break;
    case 0x0E: Load_R_N(state.BC.low, state, bus); break;
    case 0x08: Load_NN_SP(state, bus); break;
    case 0x0A: Load_A_BC(state, bus); break;
    case 0x11: Load_RR_NN(state.DE.reg, state, bus); break;
    case 0x12: Load_DE_A(state, bus); break;
    case 0x16: Load_R_N(state.DE.high, state, bus); break;
    case 0x1E: Load_R_N(state.DE.low, state, bus); break;
    case 0x1A: Load_A_DE(state, bus); break;
    case 0x21: Load_RR_NN(state.HL.reg, state, bus); break;
    case 0x22: Load_HL_A_Pos(state, bus); break;
    case 0x26: Load_R_N(state.HL.high, state, bus); break;
    case 0x2E: Load_R_N(state.HL.low, state, bus); break;
    case 0x2A: Load_A_HL_Pos(state, bus); break;
    case 0x31: Load_RR_NN(state.SP.reg, state, bus); break;
    case 0x32: Load_HL_A_Neg(state, bus); break;
    case 0x36: Load_HL_N(state, bus); break;
    case 0x3E: Load_R_N(state.AF.high, state, bus); break;
    case 0x3A: Load_A_HL_Neg(state, bus); break;
    case 0x40: Load_R_R(state.BC.high, state.BC.high, state); break;
    case 0x41: Load_R_R(state.BC.high, state.BC.low, state); break;
    case 0x42: Load_R_R(state.BC.high, state.DE.high, state); break;
    case 0x43: Load_R_R(state.BC.high, state.DE.low, state); break;
    case 0x44: Load_R_R(state.BC.high, state.HL.high, state); break;
    case 0x45: Load_R_R(state.BC.high, state.HL.low, state); break;
    case 0x46: Load_R_HL(state.BC.high, state, bus); break;
    case 0x47: Load_R_R(state.BC.high, state.AF.high, state); break;
    case 0x48: Load_R_R(state.BC.low, state.BC.high, state); break;
    case 0x49: Load_R_R(state.BC.low, state.BC.low, state); break;
    case 0x4A: Load_R_R(state.BC.low, state.DE.high, state); break;
    case 0x4B: Load_R_R(state.BC.low, state.DE.low, state); break;
    case 0x4C: Load_R_R(state.BC.low, state.HL.high, state); break;
    case 0x4D: Load_R_R(state.BC.low, state.HL.low, state); break;
    case 0x4E: Load_R_HL(state.BC.low, state, bus); break;
    case 0x4F: Load_R_R(state.BC.low, state.AF.high, state); break;
    case 0x50: Load_R_R(state.DE.high, state.BC.high, state); break;
    case 0x51: Load_R_R(state.DE.high, state.BC.low, state); break;
    case 0x52: Load_R_R(state.DE.high, state.DE.high, state); break;
    case 0x53: Load_R_R(state.DE.high, state.DE.low, state); break;
    case 0x54: Load_R_R(state.DE.high, state.HL.high, state); break;
    case 0x55: Load_R_R(state.DE.high, state.HL.low, state); break;
    case 0x56: Load_R_HL(state.DE.high, state, bus); break;
    case 0x57: Load_R_R(state.DE.high, state.AF.high, state); break;
    case 0x58: Load_R_R(state.DE.low, state.BC.high, state); break;
    case 0x59: Load_R_R(state.DE.low, state.BC.low, state); break;
    case 0x5A: Load_R_R(state.DE.low, state.DE.high, state); break;
    case 0x5B: Load_R_R(state.DE.low, state.DE.low, state); break;
    case 0x5C: Load_R_R(state.DE.low, state.HL.high, state); break;
    case 0x5D: Load_R_R(state.DE.low, state.HL.low, state); break;
    case 0x5E: Load_R_HL(state.DE.low, state, bus); break;
    case 0x5F: Load_R_R(state.DE.low, state.AF.high, state); break;
    case 0x60: Load_R_R(state.HL.high, state.BC.high, state); break;
    case 0x61: Load_R_R(state.HL.high, state.BC.low, state); break;
    case 0x62: Load_R_R(state.HL.high, state.DE.high, state); break;
    case 0x63: Load_R_R(state.HL.high, state.DE.low, state); break;
    case 0x64: Load_R_R(state.HL.high, state.HL.high, state); break;
    case 0x65: Load_R_R(state.HL.high, state.HL.low, state); break;
    case 0x66: Load_R_HL(state.HL.high, state, bus); break;
    case 0x67: Load_R_R(state.HL.high, state.AF.high, state); break;
    case 0x68: Load_R_R(state.HL.low, state.BC.high, state); break;
    case 0x69: Load_R_R(state.HL.low, state.BC.low, state); break;
    case 0x6A: Load_R_R(state.HL.low, state.DE.high, state); break;
    case 0x6B: Load_R_R(state.HL.low, state.DE.low, state); break;
    case 0x6C: Load_R_R(state.HL.low, state.HL.high, state); break;
    case 0x6D: Load_R_R(state.HL.low, state.HL.low, state); break;
    case 0x6E: Load_R_HL(state.HL.low, state, bus); break;
    case 0x6F: Load_R_R(state.HL.low, state.AF.high, state); break;
    case 0x70: Load_HL_R(state.BC.high, state, bus); break;
    case 0x71: Load_HL_R(state.BC.low, state, bus); break;
    case 0x72: Load_HL_R(state.DE.high, state, bus); break;
    case 0x73: Load_HL_R(state.DE.low, state, bus); break;
    case 0x74: Load_HL_R(state.HL.high, state, bus); break;
    case 0x75: Load_HL_R(state.HL.low, state, bus); break;
    case 0x77: Load_HL_R(state.AF.high, state, bus); break;
    case 0x78: Load_R_R(state.AF.high, state.BC.high, state); break;
    case 0x79: Load_R_R(state.AF.high, state.BC.low, state); break;
    case 0x7A: Load_R_R(state.AF.high, state.DE.high, state); break;
    case 0x7B: Load_R_R(state.AF.high, state.DE.low, state); break;
    case 0x7C: Load_R_R(state.AF.high, state.HL.high, state); break;
    case 0x7D: Load_R_R(state.AF.high, state.HL.low, state); break;
    case 0x7E: Load_R_HL(state.AF.high, state, bus); break;
    case 0x7F: Load_R_R(state.AF.high, state.AF.high, state); break;
    case 0xE0: Load_N_A(state, bus); break;
    case 0xE2: Load_C_A(state, bus); break;
    case 0xEA: Load_NN_A(state, bus); break;
    case 0xF0: Load_A_N(state, bus); break;
    case 0xF2: Load_A_C(state, bus); break;
    case 0xFA: Load_A_NN(state, bus); break;
    case 0xf8: Load_HL_SP_E(state, bus); break;
    case 0xf9: Load_SP_HL(state, bus); break;
    default:
      throw NotImplemented(std::format("{}Unable to execute instruction {}{:#04x}{}", RED, BOLDRED, opcode, RESET));
  }
}

// Helper functions
uint16_t Executor::ToU16(uint8_t msb, uint8_t lsb)
{
  return static_cast<uint16_t>(msb << 8U) | lsb;
}

void Executor::SetZ(CpuState &state, bool value)
{
  state.AF.low = (state.AF.low & ~(1U << 7U)) | static_cast<uint8_t>(value << 7U);
}

void Executor::SetN(CpuState &state, bool value)
{
  state.AF.low = (state.AF.low & ~(1U << 6U)) | static_cast<uint8_t>(value << 6U);
}

void Executor::SetH(CpuState &state, bool value)
{
  state.AF.low = (state.AF.low & ~(1U << 5U)) | static_cast<uint8_t>(value << 5U);
}

void Executor::SetCY(CpuState &state, bool value)
{
  state.AF.low = (state.AF.low & ~(1U << 4U)) | static_cast<uint8_t>(value << 4U);
}


// Load

void Executor::Load_R_R(uint8_t &dest, uint8_t src, CpuState &state)
{
  dest = src;
  state.t_cycles += 4;
}

void Executor::Load_R_N(uint8_t &dest, CpuState &state, Bus &bus)
{
  dest = bus.Read(state.PC.reg);
  ++state.PC.reg;
  state.t_cycles += 8;
}

void Executor::Load_RR_NN(uint16_t& dest, CpuState &state, Bus &bus)
{
  auto lsb = bus.Read(state.PC.reg++);
  auto msb = bus.Read(state.PC.reg++);
  dest = ToU16(msb, lsb);
  state.t_cycles += 12;
}

void Executor::Load_R_HL(uint8_t &dest, CpuState &state, Bus &bus)
{
  dest = bus.Read(state.HL.reg);
  state.t_cycles += 8;
}

void Executor::Load_HL_R(uint8_t &src, CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, src);
  state.t_cycles += 8;
}

void Executor::Load_HL_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  bus.Write(state.HL.reg, u8);
  state.t_cycles += 12;
}

void Executor::Load_A_BC(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.BC.reg);
  state.t_cycles += 8;
}

void Executor::Load_BC_A(CpuState &state, Bus &bus)
{
  bus.Write(state.BC.reg, state.AF.high);
  state.t_cycles += 8;
}

void Executor::Load_A_DE(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.DE.reg);
  state.t_cycles += 8;
}

void Executor::Load_DE_A(CpuState &state, Bus &bus)
{
  bus.Write(state.DE.reg, state.AF.high);
  state.t_cycles += 8;
}

void Executor::Load_HL_A_Neg(CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, state.AF.high);
  state.HL.reg = state.HL.reg - 1;
  state.t_cycles += 8;
}

void Executor::Load_A_HL_Neg(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.HL.reg);
  state.HL.reg = state.HL.reg - 1;
  state.t_cycles += 8;
}

void Executor::Load_A_HL_Pos(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.HL.reg);
  state.HL.reg = state.HL.reg + 1;
  state.t_cycles += 8;
}

void Executor::Load_HL_A_Pos(CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, state.AF.high);
  state.HL.reg = state.HL.reg + 1;
  state.t_cycles += 8;
}

void Executor::Load_NN_SP(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  uint16_t nn = ToU16(msb, lsb);
  bus.Write(nn, state.SP.low);
  ++nn;
  bus.Write(nn, state.SP.high);
  state.t_cycles += 20;
}

void Executor::Load_NN_A(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  bus.Write(ToU16(msb, lsb), state.AF.high);
  state.t_cycles += 16;
}

void Executor::Load_A_NN(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  state.AF.high = bus.Read(ToU16(msb, lsb));
  state.t_cycles += 16;
}

void Executor::Load_N_A(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  bus.Write(0xFF00 + u8, state.AF.high);
  state.t_cycles += 12;
}

void Executor::Load_A_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  state.AF.high = bus.Read(0xFF00 + u8);
  state.t_cycles += 12;
}

void Executor::Load_C_A(CpuState &state, Bus &bus)
{
  bus.Write(0xFF00 + state.BC.low, state.AF.high);
  state.t_cycles += 8;
}

void Executor::Load_A_C(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(0xFF00 + state.BC.low);
  state.t_cycles += 8;
}

void Executor::Load_SP_HL(CpuState &state, Bus &bus)
{
  state.SP.reg = state.HL.reg;
  state.t_cycles += 8;
}

void Executor::Load_HL_SP_E(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  uint16_t res = state.SP.reg + i8;
  SetZ(state, false);
  SetN(state, false);
  SetH(state, ((state.SP.reg ^ i8 ^ res) & 0x10) != 0);
  SetCY(state, ((state.SP.reg ^ i8 ^ res) & 0x100) != 0);

  state.HL.reg = res;
  state.t_cycles += 12;
}
