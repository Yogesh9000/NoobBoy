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
    case 0x03: Inc_RR(state.BC.reg, state); break;
    case 0x04: Inc_R(state.BC.high, state); break;
    case 0x05: Dec_R(state.BC.high, state); break;
    case 0x06: Load_R_N(state.BC.high, state, bus); break;
    case 0x07: Rlca(state); break;
    case 0x08: Load_NN_SP(state, bus); break;
    case 0x09: Add_HL_RR(state.BC.reg, state); break;
    case 0x0A: Load_A_BC(state, bus); break;
    case 0x0B: Dec_RR(state.BC.reg, state); break;
    case 0x0C: Inc_R(state.BC.low, state); break;
    case 0x0D: Dec_R(state.BC.low, state); break;
    case 0x0E: Load_R_N(state.BC.low, state, bus); break;
    case 0x0F: Rrca(state); break;
    case 0x10: Stop(state); break;
    case 0x11: Load_RR_NN(state.DE.reg, state, bus); break;
    case 0x12: Load_DE_A(state, bus); break;
    case 0x13: Inc_RR(state.DE.reg, state); break;
    case 0x14: Inc_R(state.DE.high, state); break;
    case 0x15: Dec_R(state.DE.high, state); break;
    case 0x16: Load_R_N(state.DE.high, state, bus); break;
    case 0x17: Rla(state); break;
    case 0x18: Jr_E(state, bus); break;
    case 0x19: Add_HL_RR(state.DE.reg, state); break;
    case 0x1A: Load_A_DE(state, bus); break;
    case 0x1B: Dec_RR(state.DE.reg, state); break;
    case 0x1C: Inc_R(state.DE.low, state); break;
    case 0x1D: Dec_R(state.DE.low, state); break;
    case 0x1E: Load_R_N(state.DE.low, state, bus); break;
    case 0x1F: Rra(state); break;
    case 0x20: Jr_CC_E((state.AF.low & (1U << 7U)) == 0, state, bus) ;break;
    case 0x21: Load_RR_NN(state.HL.reg, state, bus); break;
    case 0x22: Load_HL_A_Pos(state, bus); break;
    case 0x23: Inc_RR(state.HL.reg, state); break;
    case 0x24: Inc_R(state.HL.high, state); break;
    case 0x25: Dec_R(state.HL.high, state); break;
    case 0x26: Load_R_N(state.HL.high, state, bus); break;
    case 0x27: Daa(state); break;
    case 0x28: Jr_CC_E((state.AF.low & (1U << 7U)) != 0, state, bus) ;break;
    case 0x29: Add_HL_RR(state.HL.reg, state); break;
    case 0x2A: Load_A_HL_Pos(state, bus); break;
    case 0x2B: Dec_RR(state.HL.reg, state); break;
    case 0x2C: Inc_R(state.HL.low, state); break;
    case 0x2D: Dec_R(state.HL.low, state); break;
    case 0x2E: Load_R_N(state.HL.low, state, bus); break;
    case 0x2F: Cpl(state); break;
    case 0x30: Jr_CC_E((state.AF.low & (1U << 4U)) == 0, state, bus) ;break;
    case 0x31: Load_RR_NN(state.SP.reg, state, bus); break;
    case 0x32: Load_HL_A_Neg(state, bus); break;
    case 0x33: Inc_RR(state.SP.reg, state); break;
    case 0x34: Inc_HL(state, bus); break;
    case 0x35: Dec_HL(state, bus); break;
    case 0x36: Load_HL_N(state, bus); break;
    case 0x37: Scf(state); break;
    case 0x38: Jr_CC_E((state.AF.low & (1U << 4U)) != 0, state, bus) ;break;
    case 0x39: Add_HL_RR(state.SP.reg, state); break;
    case 0x3A: Load_A_HL_Neg(state, bus); break;
    case 0x3B: Dec_RR(state.SP.reg, state); break;
    case 0x3C: Inc_R(state.AF.high, state); break;
    case 0x3D: Dec_R(state.AF.high, state); break;
    case 0x3E: Load_R_N(state.AF.high, state, bus); break;
    case 0x3F: Ccf(state); break;
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
    case 0x76: Halt(state); break;
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
    case 0xC0: Ret_CC((state.AF.low & (1U << 7U)) == 0, state, bus); break;
    case 0xC1: Pop(state.BC, state, bus); break;
    case 0xC2: Jp_CC_NN((state.AF.low & (1U << 7U)) == 0, state, bus); break;
    case 0xC3: Jp_NN(state, bus); break;
    case 0xC4: Call_CC_NN((state.AF.low & (1U << 7U)) == 0, state, bus); break;
    case 0xC5: Push(state.BC, state, bus); break;
    case 0xC6: Add_N(state, bus); break;
    case 0xC7: Rst(0x00, state, bus); break;
    case 0xC8: Ret_CC((state.AF.low & (1U << 7U)) != 0, state, bus); break;
    case 0xC9: Ret(state, bus); break;
    case 0xCA: Jp_CC_NN((state.AF.low & (1U << 7U)) != 0, state, bus); break;
    case 0xCB: DecodeAndExecuteCB(bus.Read(state.PC.reg++), state, bus); break; // cb prefixed instructions
    case 0xCC: Call_CC_NN((state.AF.low & (1U << 7U)) != 0, state, bus); break;
    case 0xCD: Call_NN(state, bus); break;
    case 0xCE: Adc_N(state, bus); break;
    case 0xCF: Rst(0x08, state, bus); break;
    case 0xD0: Ret_CC((state.AF.low & (1U << 4U)) == 0, state, bus); break;
    case 0xD1: Pop(state.DE, state, bus); break;
    case 0xD2: Jp_CC_NN((state.AF.low & (1U << 4U)) == 0, state, bus); break;
    case 0xD4: Call_CC_NN((state.AF.low & (1U << 4U)) == 0, state, bus); break;
    case 0xD5: Push(state.DE, state, bus); break;
    case 0xD6: Sub_N(state, bus); break;
    case 0xD7: Rst(0x10, state, bus); break;
    case 0xD8: Ret_CC((state.AF.low & (1U << 4U)) != 0, state, bus); break;
    case 0xD9: RetI(state, bus); break;
    case 0xDA: Jp_CC_NN((state.AF.low & (1U << 4U)) != 0, state, bus); break;
    case 0xDC: Call_CC_NN((state.AF.low & (1U << 4U)) != 0, state, bus); break;
    case 0xDE: Sbc_N(state, bus); break;
    case 0xDF: Rst(0x18, state, bus); break;
    case 0xE0: Load_N_A(state, bus); break;
    case 0xE1: Pop(state.HL, state, bus); break;
    case 0xE2: Load_C_A(state, bus); break;
    case 0xE5: Push(state.HL, state, bus); break;
    case 0xE6: And_N(state, bus); break;
    case 0xE7: Rst(0x20, state, bus); break;
    case 0xE8: Add_SP_E(state, bus); break;
    case 0xE9: Jp_HL(state); break;
    case 0xEA: Load_NN_A(state, bus); break;
    case 0xEE: Xor_N(state, bus); break;
    case 0xEF: Rst(0x28, state, bus); break;
    case 0xF0: Load_A_N(state, bus); break;
    case 0xF1: {
      Pop(state.AF, state, bus);
      state.AF.low &= 0xF0U; // clear unused lower nibble
    } break;
    case 0xF2: Load_A_C(state, bus); break;
    case 0xF3: Di(state); break;
    case 0xF5: Push(state.AF, state, bus); break;
    case 0xF6: Or_N(state, bus); break;
    case 0xF7: Rst(0x30, state, bus); break;
    case 0xF8: Load_HL_SP_E(state, bus); break;
    case 0xF9: Load_SP_HL(state, bus); break;
    case 0xFA: Load_A_NN(state, bus); break;
    case 0xFB: Ei(state); break;
    case 0xFE: Cp_N(state, bus); break;
    case 0xFF: Rst(0x38, state, bus); break;
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

void Executor::Stop(CpuState &state)
{
  // TODO:
  state.t_cycles += 4;
}

void Executor::Halt(CpuState &state)
{
  state.IsHalted = true;
  state.t_cycles += 4;
}

void Executor::Di(CpuState &state)
{
  state.ime = false;
  state.t_cycles += 4;
}

void Executor::Ei(CpuState &state)
{
  state.ie_delay = 2; // NOTE: Cpu must kepp reducing this delay befor each instruction, until it reaches zero
                      //       Once delay reaches 0, set ime flag
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

void Executor::Pop(Register &reg, CpuState &state, Bus &bus)
{
  reg.low = bus.Read(state.SP.reg++);
  reg.high = bus.Read(state.SP.reg++);
  state.t_cycles += 12;
}

void Executor::Push(Register &reg, CpuState &state, Bus &bus)
{
  bus.Write(--state.SP.reg, reg.high);
  bus.Write(--state.SP.reg, reg.low);
  state.t_cycles += 16;
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

void Executor::Inc_R(uint8_t &src, CpuState &state)
{
  uint16_t res = src + 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((src & 0x0FU) + 1) > 0x0FU);

  src = (res & 0xFFU);
  state.t_cycles += 4;
}

void Executor::Inc_RR(uint16_t &src, CpuState &state)
{
  src = src + 1;
  state.t_cycles += 8;
}

void Executor::Inc_HL(CpuState &state, Bus &bus)
{
  uint8_t data = bus.Read(state.HL.reg);
  uint16_t res = data + 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((data & 0x0FU) + 1U) > 0x0F);

  bus.Write(state.HL.reg, (res & 0xFFU));
  state.t_cycles += 12;
}

void Executor::Dec_R(uint8_t &src, CpuState &state)
{
  uint8_t res = src - 1;

  SetZ(state, res == 0);
  SetN(state, true);
  SetH(state, ((src & 0xFU) - 1) > 0xFU);

  src = res;
  state.t_cycles += 4;
}

void Executor::Dec_RR(uint16_t &src, CpuState &state)
{
  src = src - 1;
  state.t_cycles += 8;
}

void Executor::Dec_HL(CpuState &state, Bus &bus)
{
  uint8_t data = bus.Read(state.HL.reg);
  uint16_t res = data - 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((data & 0x0FU) - 1U) > 0x0F);

  bus.Write(state.HL.reg, (res & 0xFFU));
  state.t_cycles += 12;
}

void Executor::Ccf(CpuState &state)
{
  SetN(state, false);
  SetH(state, false);

  state.AF.low = state.AF.low ^ (1U << 4U);
  state.t_cycles += 4;
}

void Executor::Scf(CpuState &state)
{
  SetN(state, false);
  SetH(state, false);
  SetCY(state, true);
  state.t_cycles += 4;
}

// DAA (https://forums.nesdev.org/viewtopic.php?p=196282&sid=a1cdd6adc0b01ea3d77f61aee9527449#p196282)
void Executor::Daa(CpuState &state)
{
  if (!(state.AF.low & (1U << 6U)))
  {
    if ((state.AF.low & (1U << 4U)) || state.AF.high > 0x99)
    {
      state.AF.high += 0x60;
      state.AF.low = (state.AF.low & ~(1U << 4U) | (1U << 4U));
    }
    if ((state.AF.low & (1U << 5U)) || (state.AF.high & 0x0FU) > 0x09)
    {
      state.AF.high += 0x06;
    }
  }
  else
  {
    if (state.AF.low & (1U << 4U))
    {
      state.AF.high -= 0x60;
    }
    if (state.AF.low & (1U << 5U))
    {
      state.AF.high -= 0x06;
    }
  }

  SetZ(state, state.AF.high == 0);
  SetH(state, false);

  state.t_cycles += 4;
}

void Executor::Cpl(CpuState &state)
{
  SetN(state, true);
  SetH(state, true);

  state.AF.high = ~state.AF.high;
  state.t_cycles += 4;
}

// Control Flow
void Executor::Jp_NN(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  state.PC.reg = ToU16(msb, lsb);
  state.t_cycles += 16;
}

void Executor::Jp_HL(CpuState &state)
{
  state.PC.reg = state.HL.reg;
  state.t_cycles += 4;
}

void Executor::Jp_CC_NN(bool jmp, CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  if (jmp)
  {
    state.PC.reg = ToU16(msb, lsb);
    state.t_cycles += 16;
  }
  else
  {
    state.t_cycles += 12;
  }
}

void Executor::Jr_E(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  state.PC.reg = state.PC.reg + i8;
  state.t_cycles += 12;
}

void Executor::Jr_CC_E(bool jmp, CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  if (jmp)
  {
    state.PC.reg = state.PC.reg + i8;
    state.t_cycles += 12;
  }
  else
  {
    state.t_cycles += 8;
  }
}

void Executor::Call_NN(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  bus.Write(--state.SP.reg, state.PC.high);
  bus.Write(--state.SP.reg, state.PC.low);
  state.PC.reg = ToU16(msb, lsb);
  state.t_cycles += 24;
}

void Executor::Call_CC_NN(bool call, CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  if (call)
  {
    bus.Write(--state.SP.reg, state.PC.high);
    bus.Write(--state.SP.reg, state.PC.low);
    state.PC.reg = ToU16(msb, lsb);
    state.t_cycles += 24;
  }
  else
  {
    state.t_cycles += 12;
  }
}

void Executor::Ret(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.SP.reg++);
  uint8_t msb = bus.Read(state.SP.reg++);
  state.PC.reg = ToU16(msb, lsb);
  state.t_cycles += 16;
}

void Executor::Ret_CC(bool ret, CpuState &state, Bus &bus)
{
  if (ret)
  {
    uint8_t lsb = bus.Read(state.SP.reg++);
    uint8_t msb = bus.Read(state.SP.reg++);
    state.PC.reg = ToU16(msb, lsb);
    state.t_cycles += 20;
  }
  else
  {
    state.t_cycles += 8;
  }
}

void Executor::RetI(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.SP.reg++);
  uint8_t msb = bus.Read(state.SP.reg++);
  state.PC.reg = ToU16(msb, lsb);
  state.ime = 1;
  state.t_cycles += 16;
}

void Executor::Rst(uint8_t addr, CpuState &state, Bus &bus)
{
  bus.Write(--state.SP.reg, state.PC.high);
  bus.Write(--state.SP.reg, state.PC.low);
  state.PC.reg = addr;
  state.t_cycles += 16;
}

// Rotate-Shift

void Executor::Rlca(CpuState &state)
{
  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, (state.AF.high & (1U << 7U)) >> 7U);

  state.AF.high = state.AF.high << 1U;
  state.AF.high = ((state.AF.high & ~(1U << 0U)) | ((state.AF.low & (1U << 4U)) >> 4U));

  state.t_cycles += 4;
}

void Executor::Rla(CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;

  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, (state.AF.high & (1U << 7U)));

  state.AF.high = state.AF.high << 1U;
  state.AF.high = (state.AF.high & ~(1U << 0U)) | oldCY;

  state.t_cycles += 4;
}

void Executor::Rrca(CpuState &state)
{
  uint8_t b0 = (state.AF.high & (1U << 0U));

  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, b0);

  state.AF.high = state.AF.high >> 1U;
  state.AF.high = (state.AF.high & ~(1U << 7U)) | static_cast<uint8_t>(b0 << 7U);
  state.t_cycles += 4;
}

void Executor::Rra(CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;

  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, (state.AF.high & (1U << 0U)));

  state.AF.high = state.AF.high >> 1U;
  state.AF.high = (state.AF.high & ~(1U << 7U)) | static_cast<uint8_t>(oldCY << 7U);

  state.t_cycles += 4;
}

// CB Prefixed

void Executor::DecodeAndExecuteCB(uint8_t opcode, CpuState &state, Bus &bus)
{
  switch (opcode)
  {
    case 0x00: Rlc(state.BC.high, state); break;
    case 0x01: Rlc(state.BC.low, state); break;
    case 0x02: Rlc(state.DE.high, state); break;
    case 0x03: Rlc(state.DE.low, state); break;
    case 0x04: Rlc(state.HL.high, state); break;
    case 0x05: Rlc(state.HL.low, state); break;
    case 0x06: {
      Rlc(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x07: Rlc(state.AF.high, state); break;
    case 0x08: Rrc(state.BC.high, state); break;
    case 0x09: Rrc(state.BC.low, state); break;
    case 0x0A: Rrc(state.DE.high, state); break;
    case 0x0B: Rrc(state.DE.low, state); break;
    case 0x0C: Rrc(state.HL.high, state); break;
    case 0x0D: Rrc(state.HL.low, state); break;
    case 0x0E: {
      Rrc(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x0F: Rrc(state.AF.high, state); break;
    case 0x10: Rl(state.BC.high, state); break;
    case 0x11: Rl(state.BC.low, state); break;
    case 0x12: Rl(state.DE.high, state); break;
    case 0x13: Rl(state.DE.low, state); break;
    case 0x14: Rl(state.HL.high, state); break;
    case 0x15: Rl(state.HL.low, state); break;
    case 0x16: {
      Rl(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x17: Rl(state.AF.high, state); break;
    case 0x18: Rr(state.BC.high, state); break;
    case 0x19: Rr(state.BC.low, state); break;
    case 0x1A: Rr(state.DE.high, state); break;
    case 0x1B: Rr(state.DE.low, state); break;
    case 0x1C: Rr(state.HL.high, state); break;
    case 0x1D: Rr(state.HL.low, state); break;
    case 0x1E: {
      Rr(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x1F: Rr(state.AF.high, state); break;
    case 0x20: Sla(state.BC.high, state); break;
    case 0x21: Sla(state.BC.low, state); break;
    case 0x22: Sla(state.DE.high, state); break;
    case 0x23: Sla(state.DE.low, state); break;
    case 0x24: Sla(state.HL.high, state); break;
    case 0x25: Sla(state.HL.low, state); break;
    case 0x26: {
      Sla(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x27: Sla(state.AF.high, state); break;
    case 0x28: Sra(state.BC.high, state); break;
    case 0x29: Sra(state.BC.low, state); break;
    case 0x2A: Sra(state.DE.high, state); break;
    case 0x2B: Sra(state.DE.low, state); break;
    case 0x2C: Sra(state.HL.high, state); break;
    case 0x2D: Sra(state.HL.low, state); break;
    case 0x2E: {
      Sra(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x2F: Sra(state.AF.high, state); break;
    case 0x30: Swap(state.BC.high, state); break;
    case 0x31: Swap(state.BC.low, state); break;
    case 0x32: Swap(state.DE.high, state); break;
    case 0x33: Swap(state.DE.low, state); break;
    case 0x34: Swap(state.HL.high, state); break;
    case 0x35: Swap(state.HL.low, state); break;
    case 0x36: {
      Swap(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x37: Swap(state.AF.high, state); break;
    case 0x38: Srl(state.BC.high, state); break;
    case 0x39: Srl(state.BC.low, state); break;
    case 0x3A: Srl(state.DE.high, state); break;
    case 0x3B: Srl(state.DE.low, state); break;
    case 0x3C: Srl(state.HL.high, state); break;
    case 0x3D: Srl(state.HL.low, state); break;
    case 0x3E: {
      Srl(bus.Address(state.HL.reg), state);
      state.t_cycles += 8;
    } break;
    case 0x3F: Srl(state.AF.high, state); break;
    case 0x40: Bit(state.BC.high, 0, state); break;
    case 0x41: Bit(state.BC.low,  0, state); break;
    case 0x42: Bit(state.DE.high, 0, state); break;
    case 0x43: Bit(state.DE.low,  0, state); break;
    case 0x44: Bit(state.HL.high, 0, state); break;
    case 0x45: Bit(state.HL.low,  0, state); break;
    case 0x46: {
      Bit(bus.Read(state.HL.reg), 0, state);
      state.t_cycles += 4;
    } break;
    case 0x47: Bit(state.AF.high, 0, state); break;
    case 0x48: Bit(state.BC.high, 1, state); break;
    case 0x49: Bit(state.BC.low,  1, state); break;
    case 0x4A: Bit(state.DE.high, 1, state); break;
    case 0x4B: Bit(state.DE.low,  1, state); break;
    case 0x4C: Bit(state.HL.high, 1, state); break;
    case 0x4D: Bit(state.HL.low,  1, state); break;
    case 0x4E: {
      Bit(bus.Read(state.HL.reg), 1, state);
      state.t_cycles += 4;
    } break;
    case 0x4F: Bit(state.AF.high, 1, state); break;
    case 0x50: Bit(state.BC.high, 2, state); break;
    case 0x51: Bit(state.BC.low,  2, state); break;
    case 0x52: Bit(state.DE.high, 2, state); break;
    case 0x53: Bit(state.DE.low,  2, state); break;
    case 0x54: Bit(state.HL.high, 2, state); break;
    case 0x55: Bit(state.HL.low,  2, state); break;
    case 0x56: {
      Bit(bus.Read(state.HL.reg), 2, state);
      state.t_cycles += 4;
    } break;
    case 0x57: Bit(state.AF.high, 2, state); break;
    case 0x58: Bit(state.BC.high, 3, state); break;
    case 0x59: Bit(state.BC.low,  3, state); break;
    case 0x5A: Bit(state.DE.high, 3, state); break;
    case 0x5B: Bit(state.DE.low,  3, state); break;
    case 0x5C: Bit(state.HL.high, 3, state); break;
    case 0x5D: Bit(state.HL.low,  3, state); break;
    case 0x5E: {
      Bit(bus.Read(state.HL.reg), 3, state);
      state.t_cycles += 4;
    } break;
    case 0x5F: Bit(state.AF.high, 3, state); break;
    case 0x60: Bit(state.BC.high, 4, state); break;
    case 0x61: Bit(state.BC.low,  4, state); break;
    case 0x62: Bit(state.DE.high, 4, state); break;
    case 0x63: Bit(state.DE.low,  4, state); break;
    case 0x64: Bit(state.HL.high, 4, state); break;
    case 0x65: Bit(state.HL.low,  4, state); break;
    case 0x66: {
      Bit(bus.Read(state.HL.reg), 4, state);
      state.t_cycles += 4;
    } break;
    case 0x67: Bit(state.AF.high, 4, state); break;
    case 0x68: Bit(state.BC.high, 5, state); break;
    case 0x69: Bit(state.BC.low,  5, state); break;
    case 0x6A: Bit(state.DE.high, 5, state); break;
    case 0x6B: Bit(state.DE.low,  5, state); break;
    case 0x6C: Bit(state.HL.high, 5, state); break;
    case 0x6D: Bit(state.HL.low,  5, state); break;
    case 0x6E: {
      Bit(bus.Read(state.HL.reg), 5, state);
      state.t_cycles += 4;
    } break;
    case 0x6F: Bit(state.AF.high, 5, state); break;
    case 0x70: Bit(state.BC.high, 6, state); break;
    case 0x71: Bit(state.BC.low,  6, state); break;
    case 0x72: Bit(state.DE.high, 6, state); break;
    case 0x73: Bit(state.DE.low,  6, state); break;
    case 0x74: Bit(state.HL.high, 6, state); break;
    case 0x75: Bit(state.HL.low,  6, state); break;
    case 0x76: {
      Bit(bus.Read(state.HL.reg), 6, state);
      state.t_cycles += 4;
    } break;
    case 0x77: Bit(state.AF.high, 6, state); break;
    case 0x78: Bit(state.BC.high, 7, state); break;
    case 0x79: Bit(state.BC.low,  7, state); break;
    case 0x7A: Bit(state.DE.high, 7, state); break;
    case 0x7B: Bit(state.DE.low,  7, state); break;
    case 0x7C: Bit(state.HL.high, 7, state); break;
    case 0x7D: Bit(state.HL.low,  7, state); break;
    case 0x7E: {
      Bit(bus.Read(state.HL.reg), 7, state);
      state.t_cycles += 4;
    } break;
    case 0x7F: Bit(state.AF.high, 7, state); break;
    case 0x80: Res(state.BC.high, 0, state); break;
    case 0x81: Res(state.BC.low,  0, state); break;
    case 0x82: Res(state.DE.high, 0, state); break;
    case 0x83: Res(state.DE.low,  0, state); break;
    case 0x84: Res(state.HL.high, 0, state); break;
    case 0x85: Res(state.HL.low,  0, state); break;
    case 0x86: {
      Res(bus.Address(state.HL.reg), 0, state);
      state.t_cycles += 8;
    } break;
    case 0x87: Res(state.AF.high, 0, state); break;
    case 0x88: Res(state.BC.high, 1, state); break;
    case 0x89: Res(state.BC.low,  1, state); break;
    case 0x8A: Res(state.DE.high, 1, state); break;
    case 0x8B: Res(state.DE.low,  1, state); break;
    case 0x8C: Res(state.HL.high, 1, state); break;
    case 0x8D: Res(state.HL.low,  1, state); break;
    case 0x8E: {
      Res(bus.Address(state.HL.reg), 1, state);
      state.t_cycles += 8;
    } break;
    case 0x8F: Res(state.AF.high, 1, state); break;
    case 0x90: Res(state.BC.high, 2, state); break;
    case 0x91: Res(state.BC.low,  2, state); break;
    case 0x92: Res(state.DE.high, 2, state); break;
    case 0x93: Res(state.DE.low,  2, state); break;
    case 0x94: Res(state.HL.high, 2, state); break;
    case 0x95: Res(state.HL.low,  2, state); break;
    case 0x96: {
      Res(bus.Address(state.HL.reg), 2, state);
      state.t_cycles += 8;
    } break;
    case 0x97: Res(state.AF.high, 2, state); break;
    case 0x98: Res(state.BC.high, 3, state); break;
    case 0x99: Res(state.BC.low,  3, state); break;
    case 0x9A: Res(state.DE.high, 3, state); break;
    case 0x9B: Res(state.DE.low,  3, state); break;
    case 0x9C: Res(state.HL.high, 3, state); break;
    case 0x9D: Res(state.HL.low,  3, state); break;
    case 0x9E: {
      Res(bus.Address(state.HL.reg), 3, state);
      state.t_cycles += 8;
    } break;
    case 0x9F: Res(state.AF.high, 3, state); break;
    case 0xA0: Res(state.BC.high, 4, state); break;
    case 0xA1: Res(state.BC.low,  4, state); break;
    case 0xA2: Res(state.DE.high, 4, state); break;
    case 0xA3: Res(state.DE.low,  4, state); break;
    case 0xA4: Res(state.HL.high, 4, state); break;
    case 0xA5: Res(state.HL.low,  4, state); break;
    case 0xA6: {
      Res(bus.Address(state.HL.reg), 4, state);
      state.t_cycles += 8;
    } break;
    case 0xA7: Res(state.AF.high, 4, state); break;
    case 0xA8: Res(state.BC.high, 5, state); break;
    case 0xA9: Res(state.BC.low,  5, state); break;
    case 0xAA: Res(state.DE.high, 5, state); break;
    case 0xAB: Res(state.DE.low,  5, state); break;
    case 0xAC: Res(state.HL.high, 5, state); break;
    case 0xAD: Res(state.HL.low,  5, state); break;
    case 0xAE: {
      Res(bus.Address(state.HL.reg), 5, state);
      state.t_cycles += 8;
    } break;
    case 0xAF: Res(state.AF.high, 5, state); break;
    case 0xB0: Res(state.BC.high, 6, state); break;
    case 0xB1: Res(state.BC.low,  6, state); break;
    case 0xB2: Res(state.DE.high, 6, state); break;
    case 0xB3: Res(state.DE.low,  6, state); break;
    case 0xB4: Res(state.HL.high, 6, state); break;
    case 0xB5: Res(state.HL.low,  6, state); break;
    case 0xB6: {
      Res(bus.Address(state.HL.reg), 6, state);
      state.t_cycles += 8;
    } break;
    case 0xB7: Res(state.AF.high, 6, state); break;
    case 0xB8: Res(state.BC.high, 7, state); break;
    case 0xB9: Res(state.BC.low,  7, state); break;
    case 0xBA: Res(state.DE.high, 7, state); break;
    case 0xBB: Res(state.DE.low,  7, state); break;
    case 0xBC: Res(state.HL.high, 7, state); break;
    case 0xBD: Res(state.HL.low,  7, state); break;
    case 0xBE: {
      Res(bus.Address(state.HL.reg), 7, state);
      state.t_cycles += 8;
    } break;
    case 0xBF: Res(state.AF.high, 7, state); break;
    case 0xC0: Set(state.BC.high, 0, state); break;
    case 0xC1: Set(state.BC.low,  0, state); break;
    case 0xC2: Set(state.DE.high, 0, state); break;
    case 0xC3: Set(state.DE.low,  0, state); break;
    case 0xC4: Set(state.HL.high, 0, state); break;
    case 0xC5: Set(state.HL.low,  0, state); break;
    case 0xC6: {
      Set(bus.Address(state.HL.reg), 0, state);
      state.t_cycles += 8;
    } break;
    case 0xC7: Set(state.AF.high, 0, state); break;
    case 0xC8: Set(state.BC.high, 1, state); break;
    case 0xC9: Set(state.BC.low,  1, state); break;
    case 0xCA: Set(state.DE.high, 1, state); break;
    case 0xCB: Set(state.DE.low,  1, state); break;
    case 0xCC: Set(state.HL.high, 1, state); break;
    case 0xCD: Set(state.HL.low,  1, state); break;
    case 0xCE: {
      Set(bus.Address(state.HL.reg), 1, state);
      state.t_cycles += 8;
    } break;
    case 0xCF: Set(state.AF.high, 1, state); break;
    case 0xD0: Set(state.BC.high, 2, state); break;
    case 0xD1: Set(state.BC.low,  2, state); break;
    case 0xD2: Set(state.DE.high, 2, state); break;
    case 0xD3: Set(state.DE.low,  2, state); break;
    case 0xD4: Set(state.HL.high, 2, state); break;
    case 0xD5: Set(state.HL.low,  2, state); break;
    case 0xD6: {
      Set(bus.Address(state.HL.reg), 2, state);
      state.t_cycles += 8;
    } break;
    case 0xD7: Set(state.AF.high, 2, state); break;
    case 0xD8: Set(state.BC.high, 3, state); break;
    case 0xD9: Set(state.BC.low,  3, state); break;
    case 0xDA: Set(state.DE.high, 3, state); break;
    case 0xDB: Set(state.DE.low,  3, state); break;
    case 0xDC: Set(state.HL.high, 3, state); break;
    case 0xDD: Set(state.HL.low,  3, state); break;
    case 0xDE: {
      Set(bus.Address(state.HL.reg), 3, state);
      state.t_cycles += 8;
    } break;
    case 0xDF: Set(state.AF.high, 3, state); break;
    case 0xE0: Set(state.BC.high, 4, state); break;
    case 0xE1: Set(state.BC.low,  4, state); break;
    case 0xE2: Set(state.DE.high, 4, state); break;
    case 0xE3: Set(state.DE.low,  4, state); break;
    case 0xE4: Set(state.HL.high, 4, state); break;
    case 0xE5: Set(state.HL.low,  4, state); break;
    case 0xE6: {
      Set(bus.Address(state.HL.reg), 4, state);
      state.t_cycles += 8;
    } break;
    case 0xE7: Set(state.AF.high, 4, state); break;
    case 0xE8: Set(state.BC.high, 5, state); break;
    case 0xE9: Set(state.BC.low,  5, state); break;
    case 0xEA: Set(state.DE.high, 5, state); break;
    case 0xEB: Set(state.DE.low,  5, state); break;
    case 0xEC: Set(state.HL.high, 5, state); break;
    case 0xED: Set(state.HL.low,  5, state); break;
    case 0xEE: {
      Set(bus.Address(state.HL.reg), 5, state);
      state.t_cycles += 8;
    } break;
    case 0xEF: Set(state.AF.high, 5, state); break;
    case 0xF0: Set(state.BC.high, 6, state); break;
    case 0xF1: Set(state.BC.low,  6, state); break;
    case 0xF2: Set(state.DE.high, 6, state); break;
    case 0xF3: Set(state.DE.low,  6, state); break;
    case 0xF4: Set(state.HL.high, 6, state); break;
    case 0xF5: Set(state.HL.low,  6, state); break;
    case 0xF6: {
      Set(bus.Address(state.HL.reg), 6, state);
      state.t_cycles += 8;
    } break;
    case 0xF7: Set(state.AF.high, 6, state); break;
    case 0xF8: Set(state.BC.high, 7, state); break;
    case 0xF9: Set(state.BC.low,  7, state); break;
    case 0xFA: Set(state.DE.high, 7, state); break;
    case 0xFB: Set(state.DE.low,  7, state); break;
    case 0xFC: Set(state.HL.high, 7, state); break;
    case 0xFD: Set(state.HL.low,  7, state); break;
    case 0xFE: {
      Set(bus.Address(state.HL.reg), 7, state);
      state.t_cycles += 8;
    } break;
    case 0xFF: Set(state.AF.high, 7, state); break;
    default:
      throw NotImplemented(std::format("{}Unable to execute instruction {}CB {:#04x}{}", RED, BOLDRED, opcode, RESET));
  }

}

void Executor::Rlc(uint8_t& reg, CpuState &state)
{
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  reg = reg << 1U;
  reg = (reg & ~(1U << 0U)) | (bit7);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit7 == 1U);
  state.t_cycles += 8;
}

void Executor::Rrc(uint8_t& reg, CpuState &state)
{
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;
  reg = (reg & ~(1U << 7U)) | (bit0 << 7U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);

  state.t_cycles += 8;
}

void Executor::Rl(uint8_t& reg, CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  reg = reg << 1U;
  reg = (reg & ~(1U << 0U)) | (oldCY);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit7 == 1U);
  state.t_cycles += 8;
}

void Executor::Rr(uint8_t& reg, CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;
  reg = (reg & ~(1U << 7U)) | (oldCY << 7U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);
  state.t_cycles += 8;
}

void Executor::Sla(uint8_t& reg, CpuState &state)
{
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  reg = reg << 1U;

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit7 == 1U);
  state.t_cycles += 8;
}

void Executor::Sra(uint8_t& reg, CpuState &state)
{
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;
  reg = (reg & ~(1U << 7U)) | (bit7 << 7U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);

  state.t_cycles += 8;
}

void Executor::Srl(uint8_t& reg, CpuState &state)
{
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);

  state.t_cycles += 8;
}

void Executor::Swap(uint8_t&reg, CpuState &state)
{
  uint8_t lowerNibble = (reg & 0x0FU);
  reg = reg >> 4U;
  reg = (reg & (0x0FU)) | (lowerNibble << 4U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.t_cycles += 8;
}


void Executor::Bit(uint8_t reg, uint8_t bit, CpuState &state)
{ 
  uint8_t bitX = (reg & (1U << bit)) >> bit;
  state.AF.low = (state.AF.low & ~(1U << 7U)) | ((!bitX) << 7U);
  SetN(state, false);
  SetH(state, true);

  state.t_cycles += 8;
}

void Executor::Res(uint8_t &reg, uint8_t bit, CpuState &state)
{
  reg = (reg & ~(1U << bit));
  state.t_cycles += 8;
}

void Executor::Set(uint8_t &reg, uint8_t bit, CpuState &state)
{
  reg = (reg & ~(1U << bit)) | (1U << bit);
  state.t_cycles += 8;
}
