#include "executor.hpp"
#include "bus.hpp"
#include "common.hpp"
#include <cstdint>
#include <format>

void Executor::DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus)
{
  switch (opcode)
  {
    case 0x00: Nop(state); break;
    case 0x01: Load_RR_NN(state.BC.reg, state, bus); break;
    case 0x02: Load_BC_A(state, bus); break;
    case 0x06: Load_R_N(state.BC.high, state, bus); break;
    case 0x0E: Load_R_N(state.BC.low, state, bus); break;
    case 0x08: Load_NN_SP(state, bus); break;
    case 0x09: Add_HL_RR(state.BC.reg, state); break;
    case 0x0A: Load_A_BC(state, bus); break;
    case 0x11: Load_RR_NN(state.DE.reg, state, bus); break;
    case 0x12: Load_DE_A(state, bus); break;
    case 0x16: Load_R_N(state.DE.high, state, bus); break;
    case 0x19: Add_HL_RR(state.DE.reg, state); break;
    case 0x1E: Load_R_N(state.DE.low, state, bus); break;
    case 0x1A: Load_A_DE(state, bus); break;
    case 0x21: Load_RR_NN(state.HL.reg, state, bus); break;
    case 0x22: Load_HL_A_Pos(state, bus); break;
    case 0x26: Load_R_N(state.HL.high, state, bus); break;
    case 0x29: Add_HL_RR(state.HL.reg, state); break;
    case 0x2E: Load_R_N(state.HL.low, state, bus); break;
    case 0x2A: Load_A_HL_Pos(state, bus); break;
    case 0x31: Load_RR_NN(state.SP.reg, state, bus); break;
    case 0x32: Load_HL_A_Neg(state, bus); break;
    case 0x36: Load_HL_N(state, bus); break;
    case 0x3E: Load_R_N(state.AF.high, state, bus); break;
    case 0x39: Add_HL_RR(state.SP.reg, state); break;
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
    case 0x80: Add_R(state.BC.high, state); break;
    case 0x81: Add_R(state.BC.low, state); break;
    case 0x82: Add_R(state.DE.high, state); break;
    case 0x83: Add_R(state.DE.low, state); break;
    case 0x84: Add_R(state.HL.high, state); break;
    case 0x85: Add_R(state.HL.low, state); break;
    case 0x86: Add_HL(state, bus); break;
    case 0x87: Add_R(state.AF.high, state); break;
    case 0x88: Adc_R(state.BC.high, state); break;
    case 0x89: Adc_R(state.BC.low, state); break;
    case 0x8A: Adc_R(state.DE.high, state); break;
    case 0x8B: Adc_R(state.DE.low, state); break;
    case 0x8C: Adc_R(state.HL.high, state); break;
    case 0x8D: Adc_R(state.HL.low, state); break;
    case 0x8E: Adc_HL(state, bus); break;
    case 0x8F: Adc_R(state.AF.high, state); break;
    case 0x90: Sub_R(state.BC.high, state); break;
    case 0x91: Sub_R(state.BC.low, state); break;
    case 0x92: Sub_R(state.DE.high, state); break;
    case 0x93: Sub_R(state.DE.low, state); break;
    case 0x94: Sub_R(state.HL.high, state); break;
    case 0x95: Sub_R(state.HL.low, state); break;
    case 0x96: Sub_HL(state, bus); break;
    case 0x97: Sub_R(state.AF.high, state); break;
    case 0x98: Sbc_R(state.BC.high, state); break;
    case 0x99: Sbc_R(state.BC.low, state); break;
    case 0x9A: Sbc_R(state.DE.high, state); break;
    case 0x9B: Sbc_R(state.DE.low, state); break;
    case 0x9C: Sbc_R(state.HL.high, state); break;
    case 0x9D: Sbc_R(state.HL.low, state); break;
    case 0x9E: Sbc_HL(state, bus); break;
    case 0x9F: Sbc_R(state.AF.high, state); break;
    case 0xA0: And_R(state.BC.high, state); break;
    case 0xA1: And_R(state.BC.low, state); break;
    case 0xA2: And_R(state.DE.high, state); break;
    case 0xA3: And_R(state.DE.low, state); break;
    case 0xA4: And_R(state.HL.high, state); break;
    case 0xA5: And_R(state.HL.low, state); break;
    case 0xA6: And_HL(state, bus); break;
    case 0xA7: And_R(state.AF.high, state); break;
    case 0xA8: Xor_R(state.BC.high, state); break;
    case 0xA9: Xor_R(state.BC.low, state); break;
    case 0xAA: Xor_R(state.DE.high, state); break;
    case 0xAB: Xor_R(state.DE.low, state); break;
    case 0xAC: Xor_R(state.HL.high, state); break;
    case 0xAD: Xor_R(state.HL.low, state); break;
    case 0xAE: Xor_HL(state, bus); break;
    case 0xAF: Xor_R(state.AF.high, state); break;
    case 0xB0: Or_R(state.BC.high, state); break;
    case 0xB1: Or_R(state.BC.low, state); break;
    case 0xB2: Or_R(state.DE.high, state); break;
    case 0xB3: Or_R(state.DE.low, state); break;
    case 0xB4: Or_R(state.HL.high, state); break;
    case 0xB5: Or_R(state.HL.low, state); break;
    case 0xB6: Or_HL(state, bus); break;
    case 0xB7: Or_R(state.AF.high, state); break;
    case 0xB8: Cp_R(state.BC.high, state); break;
    case 0xB9: Cp_R(state.BC.low, state); break;
    case 0xBA: Cp_R(state.DE.high, state); break;
    case 0xBB: Cp_R(state.DE.low, state); break;
    case 0xBC: Cp_R(state.HL.high, state); break;
    case 0xBD: Cp_R(state.HL.low, state); break;
    case 0xBE: Cp_HL(state, bus); break;
    case 0xBF: Cp_R(state.AF.high, state); break;
    case 0xC6: Add_N(state, bus); break;
    case 0xCE: Adc_N(state, bus); break;
    case 0xD6: Sub_N(state, bus); break;
    case 0xDE: Sbc_N(state, bus); break;
    case 0xE0: Load_N_A(state, bus); break;
    case 0xE2: Load_C_A(state, bus); break;
    case 0xE6: And_N(state, bus); break;
    case 0xE8: Add_SP_E(state, bus); break;
    case 0xEE: Xor_N(state, bus); break;
    case 0xEA: Load_NN_A(state, bus); break;
    case 0xF0: Load_A_N(state, bus); break;
    case 0xF2: Load_A_C(state, bus); break;
    case 0xFA: Load_A_NN(state, bus); break;
    case 0xF6: Or_N(state, bus); break;
    case 0xF8: Load_HL_SP_E(state, bus); break;
    case 0xFE: Cp_N(state, bus); break;
    case 0xF9: Load_SP_HL(state, bus); break;
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

// Special
void Executor::Nop(CpuState &state)
{
  state.t_cycles += 4;
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

// Arithmetic
void Executor::Add_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high ^ reg ^ res) & 0x10) != 0);
  SetCY(state, ((state.AF.high ^ reg ^ res) & 0x100) != 0);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Add_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  Add_R(u8, state);
  state.t_cycles += 4;
}

void Executor::Add_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  Add_R(u8, state);
  state.t_cycles += 4;
}

void Executor::Add_HL_RR(uint16_t src, CpuState &state)
{
  uint32_t res = static_cast<uint32_t>(state.HL.reg) + static_cast<uint32_t>(src);

  SetN(state, false);
  SetH(state, ((state.HL.reg & 0xFFFU) + (src & 0xFFFU)) > 0xFFFU);
  SetCY(state, res >= 0xFFFFU);

  state.HL.reg = res & 0xFFFFU;
  state.t_cycles += 8;
}

void Executor::Add_SP_E(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  uint16_t res = state.SP.reg + i8;

  SetZ(state, false);
  SetN(state, false);
  SetH(state, ((state.SP.reg ^ i8 ^ res) & 0x10) != 0); // Half-carry detection
  SetCY(state, ((state.SP.reg ^ i8 ^ res) & 0x100) != 0);

  state.SP.reg = res;
  state.t_cycles += 16;
}

void Executor::Adc_R(uint8_t reg, CpuState &state)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(reg) + c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high & 0xFU) + (reg & 0xFU) + c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Adc_HL(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(u8) + c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high & 0xFU) + (u8 & 0xFU) + c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Adc_N(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(u8) + c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high & 0xFU) + (u8 & 0xFU) + c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Sub_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (reg & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Sub_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Sub_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Sbc_R(uint8_t reg, CpuState &state)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(reg) - c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (reg & 0xFU) - c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Sbc_HL(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8) - c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU) - c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Sbc_N(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8) - c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU) - c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::And_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) & static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, true);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::And_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) & static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, true);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::And_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint8_t res = state.AF.high & u8;
  SetZ(state, res == 0);
  SetN(state, false);
  SetH(state, true);
  SetCY(state, false);

  state.AF.high = res;
  state.t_cycles += 8;
}

void Executor::Xor_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) ^ static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Xor_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) ^ static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Xor_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint8_t res = state.AF.high ^ u8;
  SetZ(state, res == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = res;
  state.t_cycles += 8;
}

void Executor::Or_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) | static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Or_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) | static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Or_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) | static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  state.t_cycles += 8;
}

void Executor::Cp_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (reg & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.t_cycles += 4;
}

void Executor::Cp_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.t_cycles += 8;
}

void Executor::Cp_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.t_cycles += 8;
}
