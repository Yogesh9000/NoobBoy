#include "executor.hpp"
#include "bus.hpp"
#include "common.hpp"
#include <cstdint>
#include <format>

int Executor::DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus)
{
  switch (opcode)
  {
    case 0x00: return Nop(); break;
    case 0x01: return Load_RR_NN(state.BC.reg, state, bus); break;
    case 0x02: return Load_BC_A(state, bus); break;
    case 0x03: return Inc_RR(state.BC.reg); break;
    case 0x04: return Inc_R(state.BC.high, state); break;
    case 0x05: return Dec_R(state.BC.high, state); break;
    case 0x06: return Load_R_N(state.BC.high, state, bus); break;
    case 0x07: return Rlca(state); break;
    case 0x08: return Load_NN_SP(state, bus); break;
    case 0x09: return Add_HL_RR(state.BC.reg, state); break;
    case 0x0A: return Load_A_BC(state, bus); break;
    case 0x0B: return Dec_RR(state.BC.reg); break;
    case 0x0C: return Inc_R(state.BC.low, state); break;
    case 0x0D: return Dec_R(state.BC.low, state); break;
    case 0x0E: return Load_R_N(state.BC.low, state, bus); break;
    case 0x0F: return Rrca(state); break;
    case 0x10: return Stop(); break;
    case 0x11: return Load_RR_NN(state.DE.reg, state, bus); break;
    case 0x12: return Load_DE_A(state, bus); break;
    case 0x13: return Inc_RR(state.DE.reg); break;
    case 0x14: return Inc_R(state.DE.high, state); break;
    case 0x15: return Dec_R(state.DE.high, state); break;
    case 0x16: return Load_R_N(state.DE.high, state, bus); break;
    case 0x17: return Rla(state); break;
    case 0x18: return Jr_E(state, bus); break;
    case 0x19: return Add_HL_RR(state.DE.reg, state); break;
    case 0x1A: return Load_A_DE(state, bus); break;
    case 0x1B: return Dec_RR(state.DE.reg); break;
    case 0x1C: return Inc_R(state.DE.low, state); break;
    case 0x1D: return Dec_R(state.DE.low, state); break;
    case 0x1E: return Load_R_N(state.DE.low, state, bus); break;
    case 0x1F: return Rra(state); break;
    case 0x20: return Jr_CC_E((state.AF.low & (1U << 7U)) == 0, state, bus) ;break;
    case 0x21: return Load_RR_NN(state.HL.reg, state, bus); break;
    case 0x22: return Load_HL_A_Pos(state, bus); break;
    case 0x23: return Inc_RR(state.HL.reg); break;
    case 0x24: return Inc_R(state.HL.high, state); break;
    case 0x25: return Dec_R(state.HL.high, state); break;
    case 0x26: return Load_R_N(state.HL.high, state, bus); break;
    case 0x27: return Daa(state); break;
    case 0x28: return Jr_CC_E((state.AF.low & (1U << 7U)) != 0, state, bus) ;break;
    case 0x29: return Add_HL_RR(state.HL.reg, state); break;
    case 0x2A: return Load_A_HL_Pos(state, bus); break;
    case 0x2B: return Dec_RR(state.HL.reg); break;
    case 0x2C: return Inc_R(state.HL.low, state); break;
    case 0x2D: return Dec_R(state.HL.low, state); break;
    case 0x2E: return Load_R_N(state.HL.low, state, bus); break;
    case 0x2F: return Cpl(state); break;
    case 0x30: return Jr_CC_E((state.AF.low & (1U << 4U)) == 0, state, bus) ;break;
    case 0x31: return Load_RR_NN(state.SP.reg, state, bus); break;
    case 0x32: return Load_HL_A_Neg(state, bus); break;
    case 0x33: return Inc_RR(state.SP.reg); break;
    case 0x34: return Inc_HL(state, bus); break;
    case 0x35: return Dec_HL(state, bus); break;
    case 0x36: return Load_HL_N(state, bus); break;
    case 0x37: return Scf(state); break;
    case 0x38: return Jr_CC_E((state.AF.low & (1U << 4U)) != 0, state, bus) ;break;
    case 0x39: return Add_HL_RR(state.SP.reg, state); break;
    case 0x3A: return Load_A_HL_Neg(state, bus); break;
    case 0x3B: return Dec_RR(state.SP.reg); break;
    case 0x3C: return Inc_R(state.AF.high, state); break;
    case 0x3D: return Dec_R(state.AF.high, state); break;
    case 0x3E: return Load_R_N(state.AF.high, state, bus); break;
    case 0x3F: return Ccf(state); break;
    case 0x40: return Load_R_R(state.BC.high, state.BC.high); break;
    case 0x41: return Load_R_R(state.BC.high, state.BC.low); break;
    case 0x42: return Load_R_R(state.BC.high, state.DE.high); break;
    case 0x43: return Load_R_R(state.BC.high, state.DE.low); break;
    case 0x44: return Load_R_R(state.BC.high, state.HL.high); break;
    case 0x45: return Load_R_R(state.BC.high, state.HL.low); break;
    case 0x46: return Load_R_HL(state.BC.high, state, bus); break;
    case 0x47: return Load_R_R(state.BC.high, state.AF.high); break;
    case 0x48: return Load_R_R(state.BC.low, state.BC.high); break;
    case 0x49: return Load_R_R(state.BC.low, state.BC.low); break;
    case 0x4A: return Load_R_R(state.BC.low, state.DE.high); break;
    case 0x4B: return Load_R_R(state.BC.low, state.DE.low); break;
    case 0x4C: return Load_R_R(state.BC.low, state.HL.high); break;
    case 0x4D: return Load_R_R(state.BC.low, state.HL.low); break;
    case 0x4E: return Load_R_HL(state.BC.low, state, bus); break;
    case 0x4F: return Load_R_R(state.BC.low, state.AF.high); break;
    case 0x50: return Load_R_R(state.DE.high, state.BC.high); break;
    case 0x51: return Load_R_R(state.DE.high, state.BC.low); break;
    case 0x52: return Load_R_R(state.DE.high, state.DE.high); break;
    case 0x53: return Load_R_R(state.DE.high, state.DE.low); break;
    case 0x54: return Load_R_R(state.DE.high, state.HL.high); break;
    case 0x55: return Load_R_R(state.DE.high, state.HL.low); break;
    case 0x56: return Load_R_HL(state.DE.high, state, bus); break;
    case 0x57: return Load_R_R(state.DE.high, state.AF.high); break;
    case 0x58: return Load_R_R(state.DE.low, state.BC.high); break;
    case 0x59: return Load_R_R(state.DE.low, state.BC.low); break;
    case 0x5A: return Load_R_R(state.DE.low, state.DE.high); break;
    case 0x5B: return Load_R_R(state.DE.low, state.DE.low); break;
    case 0x5C: return Load_R_R(state.DE.low, state.HL.high); break;
    case 0x5D: return Load_R_R(state.DE.low, state.HL.low); break;
    case 0x5E: return Load_R_HL(state.DE.low, state, bus); break;
    case 0x5F: return Load_R_R(state.DE.low, state.AF.high); break;
    case 0x60: return Load_R_R(state.HL.high, state.BC.high); break;
    case 0x61: return Load_R_R(state.HL.high, state.BC.low); break;
    case 0x62: return Load_R_R(state.HL.high, state.DE.high); break;
    case 0x63: return Load_R_R(state.HL.high, state.DE.low); break;
    case 0x64: return Load_R_R(state.HL.high, state.HL.high); break;
    case 0x65: return Load_R_R(state.HL.high, state.HL.low); break;
    case 0x66: return Load_R_HL(state.HL.high, state, bus); break;
    case 0x67: return Load_R_R(state.HL.high, state.AF.high); break;
    case 0x68: return Load_R_R(state.HL.low, state.BC.high); break;
    case 0x69: return Load_R_R(state.HL.low, state.BC.low); break;
    case 0x6A: return Load_R_R(state.HL.low, state.DE.high); break;
    case 0x6B: return Load_R_R(state.HL.low, state.DE.low); break;
    case 0x6C: return Load_R_R(state.HL.low, state.HL.high); break;
    case 0x6D: return Load_R_R(state.HL.low, state.HL.low); break;
    case 0x6E: return Load_R_HL(state.HL.low, state, bus); break;
    case 0x6F: return Load_R_R(state.HL.low, state.AF.high); break;
    case 0x70: return Load_HL_R(state.BC.high, state, bus); break;
    case 0x71: return Load_HL_R(state.BC.low, state, bus); break;
    case 0x72: return Load_HL_R(state.DE.high, state, bus); break;
    case 0x73: return Load_HL_R(state.DE.low, state, bus); break;
    case 0x74: return Load_HL_R(state.HL.high, state, bus); break;
    case 0x75: return Load_HL_R(state.HL.low, state, bus); break;
    case 0x76: return Halt(state); break;
    case 0x77: return Load_HL_R(state.AF.high, state, bus); break;
    case 0x78: return Load_R_R(state.AF.high, state.BC.high); break;
    case 0x79: return Load_R_R(state.AF.high, state.BC.low); break;
    case 0x7A: return Load_R_R(state.AF.high, state.DE.high); break;
    case 0x7B: return Load_R_R(state.AF.high, state.DE.low); break;
    case 0x7C: return Load_R_R(state.AF.high, state.HL.high); break;
    case 0x7D: return Load_R_R(state.AF.high, state.HL.low); break;
    case 0x7E: return Load_R_HL(state.AF.high, state, bus); break;
    case 0x7F: return Load_R_R(state.AF.high, state.AF.high); break;
    case 0x80: return Add_R(state.BC.high, state); break;
    case 0x81: return Add_R(state.BC.low, state); break;
    case 0x82: return Add_R(state.DE.high, state); break;
    case 0x83: return Add_R(state.DE.low, state); break;
    case 0x84: return Add_R(state.HL.high, state); break;
    case 0x85: return Add_R(state.HL.low, state); break;
    case 0x86: return Add_HL(state, bus); break;
    case 0x87: return Add_R(state.AF.high, state); break;
    case 0x88: return Adc_R(state.BC.high, state); break;
    case 0x89: return Adc_R(state.BC.low, state); break;
    case 0x8A: return Adc_R(state.DE.high, state); break;
    case 0x8B: return Adc_R(state.DE.low, state); break;
    case 0x8C: return Adc_R(state.HL.high, state); break;
    case 0x8D: return Adc_R(state.HL.low, state); break;
    case 0x8E: return Adc_HL(state, bus); break;
    case 0x8F: return Adc_R(state.AF.high, state); break;
    case 0x90: return Sub_R(state.BC.high, state); break;
    case 0x91: return Sub_R(state.BC.low, state); break;
    case 0x92: return Sub_R(state.DE.high, state); break;
    case 0x93: return Sub_R(state.DE.low, state); break;
    case 0x94: return Sub_R(state.HL.high, state); break;
    case 0x95: return Sub_R(state.HL.low, state); break;
    case 0x96: return Sub_HL(state, bus); break;
    case 0x97: return Sub_R(state.AF.high, state); break;
    case 0x98: return Sbc_R(state.BC.high, state); break;
    case 0x99: return Sbc_R(state.BC.low, state); break;
    case 0x9A: return Sbc_R(state.DE.high, state); break;
    case 0x9B: return Sbc_R(state.DE.low, state); break;
    case 0x9C: return Sbc_R(state.HL.high, state); break;
    case 0x9D: return Sbc_R(state.HL.low, state); break;
    case 0x9E: return Sbc_HL(state, bus); break;
    case 0x9F: return Sbc_R(state.AF.high, state); break;
    case 0xA0: return And_R(state.BC.high, state); break;
    case 0xA1: return And_R(state.BC.low, state); break;
    case 0xA2: return And_R(state.DE.high, state); break;
    case 0xA3: return And_R(state.DE.low, state); break;
    case 0xA4: return And_R(state.HL.high, state); break;
    case 0xA5: return And_R(state.HL.low, state); break;
    case 0xA6: return And_HL(state, bus); break;
    case 0xA7: return And_R(state.AF.high, state); break;
    case 0xA8: return Xor_R(state.BC.high, state); break;
    case 0xA9: return Xor_R(state.BC.low, state); break;
    case 0xAA: return Xor_R(state.DE.high, state); break;
    case 0xAB: return Xor_R(state.DE.low, state); break;
    case 0xAC: return Xor_R(state.HL.high, state); break;
    case 0xAD: return Xor_R(state.HL.low, state); break;
    case 0xAE: return Xor_HL(state, bus); break;
    case 0xAF: return Xor_R(state.AF.high, state); break;
    case 0xB0: return Or_R(state.BC.high, state); break;
    case 0xB1: return Or_R(state.BC.low, state); break;
    case 0xB2: return Or_R(state.DE.high, state); break;
    case 0xB3: return Or_R(state.DE.low, state); break;
    case 0xB4: return Or_R(state.HL.high, state); break;
    case 0xB5: return Or_R(state.HL.low, state); break;
    case 0xB6: return Or_HL(state, bus); break;
    case 0xB7: return Or_R(state.AF.high, state); break;
    case 0xB8: return Cp_R(state.BC.high, state); break;
    case 0xB9: return Cp_R(state.BC.low, state); break;
    case 0xBA: return Cp_R(state.DE.high, state); break;
    case 0xBB: return Cp_R(state.DE.low, state); break;
    case 0xBC: return Cp_R(state.HL.high, state); break;
    case 0xBD: return Cp_R(state.HL.low, state); break;
    case 0xBE: return Cp_HL(state, bus); break;
    case 0xBF: return Cp_R(state.AF.high, state); break;
    case 0xC0: return Ret_CC((state.AF.low & (1U << 7U)) == 0, state, bus); break;
    case 0xC1: return Pop(state.BC, state, bus); break;
    case 0xC2: return Jp_CC_NN((state.AF.low & (1U << 7U)) == 0, state, bus); break;
    case 0xC3: return Jp_NN(state, bus); break;
    case 0xC4: return Call_CC_NN((state.AF.low & (1U << 7U)) == 0, state, bus); break;
    case 0xC5: return Push(state.BC, state, bus); break;
    case 0xC6: return Add_N(state, bus); break;
    case 0xC7: return Rst(0x00, state, bus); break;
    case 0xC8: return Ret_CC((state.AF.low & (1U << 7U)) != 0, state, bus); break;
    case 0xC9: return Ret(state, bus); break;
    case 0xCA: return Jp_CC_NN((state.AF.low & (1U << 7U)) != 0, state, bus); break;
    case 0xCB: return DecodeAndExecuteCB(bus.Read(state.PC.reg++), state, bus); break; // cb prefixed instructions
    case 0xCC: return Call_CC_NN((state.AF.low & (1U << 7U)) != 0, state, bus); break;
    case 0xCD: return Call_NN(state, bus); break;
    case 0xCE: return Adc_N(state, bus); break;
    case 0xCF: return Rst(0x08, state, bus); break;
    case 0xD0: return Ret_CC((state.AF.low & (1U << 4U)) == 0, state, bus); break;
    case 0xD1: return Pop(state.DE, state, bus); break;
    case 0xD2: return Jp_CC_NN((state.AF.low & (1U << 4U)) == 0, state, bus); break;
    case 0xD4: return Call_CC_NN((state.AF.low & (1U << 4U)) == 0, state, bus); break;
    case 0xD5: return Push(state.DE, state, bus); break;
    case 0xD6: return Sub_N(state, bus); break;
    case 0xD7: return Rst(0x10, state, bus); break;
    case 0xD8: return Ret_CC((state.AF.low & (1U << 4U)) != 0, state, bus); break;
    case 0xD9: return RetI(state, bus); break;
    case 0xDA: return Jp_CC_NN((state.AF.low & (1U << 4U)) != 0, state, bus); break;
    case 0xDC: return Call_CC_NN((state.AF.low & (1U << 4U)) != 0, state, bus); break;
    case 0xDE: return Sbc_N(state, bus); break;
    case 0xDF: return Rst(0x18, state, bus); break;
    case 0xE0: return Load_N_A(state, bus); break;
    case 0xE1: return Pop(state.HL, state, bus); break;
    case 0xE2: return Load_C_A(state, bus); break;
    case 0xE5: return Push(state.HL, state, bus); break;
    case 0xE6: return And_N(state, bus); break;
    case 0xE7: return Rst(0x20, state, bus); break;
    case 0xE8: return Add_SP_E(state, bus); break;
    case 0xE9: return Jp_HL(state); break;
    case 0xEA: return Load_NN_A(state, bus); break;
    case 0xEE: return Xor_N(state, bus); break;
    case 0xEF: return Rst(0x28, state, bus); break;
    case 0xF0: return Load_A_N(state, bus); break;
    case 0xF1: {
      int cycles = Pop(state.AF, state, bus);
      state.AF.low &= 0xF0U; // clear unused lower nibble
      return cycles;
    } break;
    case 0xF2: return Load_A_C(state, bus); break;
    case 0xF3: return Di(state); break;
    case 0xF5: return Push(state.AF, state, bus); break;
    case 0xF6: return Or_N(state, bus); break;
    case 0xF7: return Rst(0x30, state, bus); break;
    case 0xF8: return Load_HL_SP_E(state, bus); break;
    case 0xF9: return Load_SP_HL(state); break;
    case 0xFA: return Load_A_NN(state, bus); break;
    case 0xFB: return Ei(state); break;
    case 0xFE: return Cp_N(state, bus); break;
    case 0xFF: return Rst(0x38, state, bus); break;
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

// TODO: remove unused variable from methods
// NOLINTBEGIN(readability-convert-member-functions-to-static)

// Special
int Executor::Nop()
{
  return 4;
}

int Executor::Stop()
{
  // TODO:
  return 4;
}

int Executor::Halt(CpuState &state)
{
  state.IsHalted = true;
  return 4;
}

int Executor::Di(CpuState &state)
{
  state.ime = false;
  return 4;
}

int Executor::Ei(CpuState &state)
{
  state.ie_delay = 2; // NOTE: Cpu must kepp reducing this delay befor each instruction, until it reaches zero
                      //       Once delay reaches 0, set ime flag
  return 4;
}

// Load

int Executor::Load_R_R(uint8_t &dest, uint8_t src)
{
  dest = src;
  return 4;
}

int Executor::Load_R_N(uint8_t &dest, CpuState &state, Bus &bus)
{
  dest = bus.Read(state.PC.reg);
  ++state.PC.reg;
  return 8;
}

int Executor::Load_RR_NN(uint16_t& dest, CpuState &state, Bus &bus)
{
  auto lsb = bus.Read(state.PC.reg++);
  auto msb = bus.Read(state.PC.reg++);
  dest = ToU16(msb, lsb);
  return 12;
}

int Executor::Load_R_HL(uint8_t &dest, CpuState &state, Bus &bus)
{
  dest = bus.Read(state.HL.reg);
  return 8;
}

int Executor::Load_HL_R(uint8_t &src, CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, src);
  return 8;
}

int Executor::Load_HL_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  bus.Write(state.HL.reg, u8);
  return 12;
}

int Executor::Load_A_BC(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.BC.reg);
  return 8;
}

int Executor::Load_BC_A(CpuState &state, Bus &bus)
{
  bus.Write(state.BC.reg, state.AF.high);
  return 8;
}

int Executor::Load_A_DE(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.DE.reg);
  return 8;
}

int Executor::Load_DE_A(CpuState &state, Bus &bus)
{
  bus.Write(state.DE.reg, state.AF.high);
  return 8;
}

int Executor::Load_HL_A_Neg(CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, state.AF.high);
  state.HL.reg = state.HL.reg - 1;
  return 8;
}

int Executor::Load_A_HL_Neg(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.HL.reg);
  state.HL.reg = state.HL.reg - 1;
  return 8;
}

int Executor::Load_A_HL_Pos(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.HL.reg);
  state.HL.reg = state.HL.reg + 1;
  return 8;
}

int Executor::Load_HL_A_Pos(CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, state.AF.high);
  state.HL.reg = state.HL.reg + 1;
  return 8;
}

int Executor::Load_NN_SP(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  uint16_t nn = ToU16(msb, lsb);
  bus.Write(nn, state.SP.low);
  ++nn;
  bus.Write(nn, state.SP.high);
  return 20;
}

int Executor::Load_NN_A(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  bus.Write(ToU16(msb, lsb), state.AF.high);
  return 16;
}

int Executor::Load_A_NN(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  state.AF.high = bus.Read(ToU16(msb, lsb));
  return 16;
}

int Executor::Load_N_A(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  bus.Write(0xFF00 + u8, state.AF.high);
  return 12;
}

int Executor::Load_A_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  state.AF.high = bus.Read(0xFF00 + u8);
  return 12;
}

int Executor::Load_C_A(CpuState &state, Bus &bus)
{
  bus.Write(0xFF00 + state.BC.low, state.AF.high);
  return 8;
}

int Executor::Load_A_C(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(0xFF00 + state.BC.low);
  return 8;
}

int Executor::Load_SP_HL(CpuState &state)
{
  state.SP.reg = state.HL.reg;
  return 8;
}

int Executor::Load_HL_SP_E(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  uint16_t res = state.SP.reg + i8;
  SetZ(state, false);
  SetN(state, false);
  SetH(state, ((state.SP.reg ^ i8 ^ res) & 0x10) != 0);
  SetCY(state, ((state.SP.reg ^ i8 ^ res) & 0x100) != 0);

  state.HL.reg = res;
  return 12;
}

int Executor::Pop(Register &reg, CpuState &state, Bus &bus)
{
  reg.low = bus.Read(state.SP.reg++);
  reg.high = bus.Read(state.SP.reg++);
  return 12;
}

int Executor::Push(Register &reg, CpuState &state, Bus &bus)
{
  bus.Write(--state.SP.reg, reg.high);
  bus.Write(--state.SP.reg, reg.low);
  return 16;
}

// Arithmetic
int Executor::Add_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high ^ reg ^ res) & 0x10) != 0);
  SetCY(state, ((state.AF.high ^ reg ^ res) & 0x100) != 0);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::Add_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  int cycles = Add_R(u8, state);
  cycles += 4;
  return cycles;
}

int Executor::Add_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  int cycles = Add_R(u8, state);
  cycles += 4;
  return cycles;
}

int Executor::Add_HL_RR(uint16_t src, CpuState &state)
{
  uint32_t res = static_cast<uint32_t>(state.HL.reg) + static_cast<uint32_t>(src);

  SetN(state, false);
  SetH(state, ((state.HL.reg & 0xFFFU) + (src & 0xFFFU)) > 0xFFFU);
  SetCY(state, res >= 0xFFFFU);

  state.HL.reg = res & 0xFFFFU;
  return 8;
}

int Executor::Add_SP_E(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  uint16_t res = state.SP.reg + i8;

  SetZ(state, false);
  SetN(state, false);
  SetH(state, ((state.SP.reg ^ i8 ^ res) & 0x10) != 0); // Half-carry detection
  SetCY(state, ((state.SP.reg ^ i8 ^ res) & 0x100) != 0);

  state.SP.reg = res;
  return 16;
}

int Executor::Adc_R(uint8_t reg, CpuState &state)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(reg) + c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high & 0xFU) + (reg & 0xFU) + c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::Adc_HL(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(u8) + c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high & 0xFU) + (u8 & 0xFU) + c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Adc_N(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) + static_cast<uint16_t>(u8) + c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.AF.high & 0xFU) + (u8 & 0xFU) + c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Sub_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (reg & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::Sub_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Sub_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Sbc_R(uint8_t reg, CpuState &state)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(reg) - c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (reg & 0xFU) - c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::Sbc_HL(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8) - c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU) - c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Sbc_N(CpuState &state, Bus &bus)
{
  auto c = static_cast<uint16_t>((state.AF.low & (1U << 4U)) >> 4U);
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8) - c;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU) - c) > 0xFU);
  SetCY(state, res > 0xFFU);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::And_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) & static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, true);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::And_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) & static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, true);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::And_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint8_t res = state.AF.high & u8;
  SetZ(state, res == 0);
  SetN(state, false);
  SetH(state, true);
  SetCY(state, false);

  state.AF.high = res;
  return 8;
}

int Executor::Xor_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) ^ static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::Xor_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) ^ static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Xor_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint8_t res = state.AF.high ^ u8;
  SetZ(state, res == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = res;
  return 8;
}

int Executor::Or_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) | static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 4;
}

int Executor::Or_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) | static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Or_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) | static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  state.AF.high = (res & 0xFFU);
  return 8;
}

int Executor::Cp_R(uint8_t reg, CpuState &state)
{
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(reg);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (reg & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  return 4;
}

int Executor::Cp_HL(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.HL.reg);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  return 8;
}

int Executor::Cp_N(CpuState &state, Bus &bus)
{
  uint8_t u8 = bus.Read(state.PC.reg++);
  uint16_t res = static_cast<uint16_t>(state.AF.high) - static_cast<uint16_t>(u8);

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((state.AF.high & 0xFU) - (u8 & 0xFU)) > 0xFU);
  SetCY(state, res > 0xFFU);

  return 8;
}

int Executor::Inc_R(uint8_t &src, CpuState &state)
{
  uint16_t res = src + 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((src & 0x0FU) + 1) > 0x0FU);

  src = (res & 0xFFU);
  return 4;
}

int Executor::Inc_RR(uint16_t &src)
{
  src = src + 1;
  return 8;
}

int Executor::Inc_HL(CpuState &state, Bus &bus)
{
  uint8_t data = bus.Read(state.HL.reg);
  uint16_t res = data + 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((data & 0x0FU) + 1U) > 0x0F);

  bus.Write(state.HL.reg, (res & 0xFFU));
  return 12;
}

int Executor::Dec_R(uint8_t &src, CpuState &state)
{
  uint8_t res = src - 1;

  SetZ(state, res == 0);
  SetN(state, true);
  SetH(state, ((src & 0xFU) - 1) > 0xFU);

  src = res;
  return 4;
}

int Executor::Dec_RR(uint16_t &src)
{
  src = src - 1;
  return 8;
}

int Executor::Dec_HL(CpuState &state, Bus &bus)
{
  uint8_t data = bus.Read(state.HL.reg);
  uint16_t res = data - 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, true);
  SetH(state, ((data & 0x0FU) - 1U) > 0x0F);

  bus.Write(state.HL.reg, (res & 0xFFU));
  return 12;
}

int Executor::Ccf(CpuState &state)
{
  SetN(state, false);
  SetH(state, false);

  state.AF.low = state.AF.low ^ (1U << 4U);
  return 4;
}

int Executor::Scf(CpuState &state)
{
  SetN(state, false);
  SetH(state, false);
  SetCY(state, true);
  return 4;
}

// DAA (https://forums.nesdev.org/viewtopic.php?p=196282&sid=a1cdd6adc0b01ea3d77f61aee9527449#p196282)
int Executor::Daa(CpuState &state)
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

  return 4;
}

int Executor::Cpl(CpuState &state)
{
  SetN(state, true);
  SetH(state, true);

  state.AF.high = ~state.AF.high;
  return 4;
}

// Control Flow
int Executor::Jp_NN(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  state.PC.reg = ToU16(msb, lsb);
  return 16;
}

int Executor::Jp_HL(CpuState &state)
{
  state.PC.reg = state.HL.reg;
  return 4;
}

int Executor::Jp_CC_NN(bool jmp, CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  if (jmp)
  {
    state.PC.reg = ToU16(msb, lsb);
    return 16;
  }
  else
  {
    return 12;
  }
}

int Executor::Jr_E(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  state.PC.reg = state.PC.reg + i8;
  return 12;
}

int Executor::Jr_CC_E(bool jmp, CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  if (jmp)
  {
    state.PC.reg = state.PC.reg + i8;
    return 12;
  }
  else
  {
    return 8;
  }
}

int Executor::Call_NN(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  bus.Write(--state.SP.reg, state.PC.high);
  bus.Write(--state.SP.reg, state.PC.low);
  state.PC.reg = ToU16(msb, lsb);
  return 24;
}

int Executor::Call_CC_NN(bool call, CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  if (call)
  {
    bus.Write(--state.SP.reg, state.PC.high);
    bus.Write(--state.SP.reg, state.PC.low);
    state.PC.reg = ToU16(msb, lsb);
    return 24;
  }
  else
  {
    return 12;
  }
}

int Executor::Ret(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.SP.reg++);
  uint8_t msb = bus.Read(state.SP.reg++);
  state.PC.reg = ToU16(msb, lsb);
  return 16;
}

int Executor::Ret_CC(bool ret, CpuState &state, Bus &bus)
{
  if (ret)
  {
    uint8_t lsb = bus.Read(state.SP.reg++);
    uint8_t msb = bus.Read(state.SP.reg++);
    state.PC.reg = ToU16(msb, lsb);
    return 20;
  }
  else
  {
    return 8;
  }
}

int Executor::RetI(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.SP.reg++);
  uint8_t msb = bus.Read(state.SP.reg++);
  state.PC.reg = ToU16(msb, lsb);
  state.ime = 1;
  return 16;
}

int Executor::Rst(uint8_t addr, CpuState &state, Bus &bus)
{
  bus.Write(--state.SP.reg, state.PC.high);
  bus.Write(--state.SP.reg, state.PC.low);
  state.PC.reg = addr;
  return 16;
}

// Rotate-Shift

int Executor::Rlca(CpuState &state)
{
  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, (state.AF.high & (1U << 7U)) >> 7U);

  state.AF.high = state.AF.high << 1U;
  state.AF.high = ((state.AF.high & ~(1U << 0U)) | ((state.AF.low & (1U << 4U)) >> 4U));

  return 4;
}

int Executor::Rla(CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;

  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, (state.AF.high & (1U << 7U)));

  state.AF.high = state.AF.high << 1U;
  state.AF.high = (state.AF.high & ~(1U << 0U)) | oldCY;

  return 4;
}

int Executor::Rrca(CpuState &state)
{
  uint8_t b0 = (state.AF.high & (1U << 0U));

  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, b0);

  state.AF.high = state.AF.high >> 1U;
  state.AF.high = (state.AF.high & ~(1U << 7U)) | static_cast<uint8_t>(b0 << 7U);
  return 4;
}

int Executor::Rra(CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;

  SetZ(state, false);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, (state.AF.high & (1U << 0U)));

  state.AF.high = state.AF.high >> 1U;
  state.AF.high = (state.AF.high & ~(1U << 7U)) | static_cast<uint8_t>(oldCY << 7U);

  return 4;
}

// NOLINTEND(readability-convert-member-functions-to-static)

// CB Prefixed

int Executor::DecodeAndExecuteCB(uint8_t opcode, CpuState &state, Bus &bus)
{
  switch (opcode)
  {
    case 0x00: return Rlc(state.BC.high, state); break;
    case 0x01: return Rlc(state.BC.low, state); break;
    case 0x02: return Rlc(state.DE.high, state); break;
    case 0x03: return Rlc(state.DE.low, state); break;
    case 0x04: return Rlc(state.HL.high, state); break;
    case 0x05: return Rlc(state.HL.low, state); break;
    case 0x06: {
      int cycles = Rlc(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x07: return Rlc(state.AF.high, state); break;
    case 0x08: return Rrc(state.BC.high, state); break;
    case 0x09: return Rrc(state.BC.low, state); break;
    case 0x0A: return Rrc(state.DE.high, state); break;
    case 0x0B: return Rrc(state.DE.low, state); break;
    case 0x0C: return Rrc(state.HL.high, state); break;
    case 0x0D: return Rrc(state.HL.low, state); break;
    case 0x0E: {
      int cycles = Rrc(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x0F: return Rrc(state.AF.high, state); break;
    case 0x10: return Rl(state.BC.high, state); break;
    case 0x11: return Rl(state.BC.low, state); break;
    case 0x12: return Rl(state.DE.high, state); break;
    case 0x13: return Rl(state.DE.low, state); break;
    case 0x14: return Rl(state.HL.high, state); break;
    case 0x15: return Rl(state.HL.low, state); break;
    case 0x16: {
      int cycles = Rl(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x17: return Rl(state.AF.high, state); break;
    case 0x18: return Rr(state.BC.high, state); break;
    case 0x19: return Rr(state.BC.low, state); break;
    case 0x1A: return Rr(state.DE.high, state); break;
    case 0x1B: return Rr(state.DE.low, state); break;
    case 0x1C: return Rr(state.HL.high, state); break;
    case 0x1D: return Rr(state.HL.low, state); break;
    case 0x1E: {
      int cycles = Rr(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x1F: return Rr(state.AF.high, state); break;
    case 0x20: return Sla(state.BC.high, state); break;
    case 0x21: return Sla(state.BC.low, state); break;
    case 0x22: return Sla(state.DE.high, state); break;
    case 0x23: return Sla(state.DE.low, state); break;
    case 0x24: return Sla(state.HL.high, state); break;
    case 0x25: return Sla(state.HL.low, state); break;
    case 0x26: {
      int cycles = Sla(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x27: return Sla(state.AF.high, state); break;
    case 0x28: return Sra(state.BC.high, state); break;
    case 0x29: return Sra(state.BC.low, state); break;
    case 0x2A: return Sra(state.DE.high, state); break;
    case 0x2B: return Sra(state.DE.low, state); break;
    case 0x2C: return Sra(state.HL.high, state); break;
    case 0x2D: return Sra(state.HL.low, state); break;
    case 0x2E: {
      int cycles = Sra(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x2F: return Sra(state.AF.high, state); break;
    case 0x30: return Swap(state.BC.high, state); break;
    case 0x31: return Swap(state.BC.low, state); break;
    case 0x32: return Swap(state.DE.high, state); break;
    case 0x33: return Swap(state.DE.low, state); break;
    case 0x34: return Swap(state.HL.high, state); break;
    case 0x35: return Swap(state.HL.low, state); break;
    case 0x36: {
      int cycles = Swap(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x37: return Swap(state.AF.high, state); break;
    case 0x38: return Srl(state.BC.high, state); break;
    case 0x39: return Srl(state.BC.low, state); break;
    case 0x3A: return Srl(state.DE.high, state); break;
    case 0x3B: return Srl(state.DE.low, state); break;
    case 0x3C: return Srl(state.HL.high, state); break;
    case 0x3D: return Srl(state.HL.low, state); break;
    case 0x3E: {
      int cycles = Srl(bus.Address(state.HL.reg), state);
      cycles += 8;
      return cycles;
    } break;
    case 0x3F: return Srl(state.AF.high, state); break;
    case 0x40: return Bit(state.BC.high, 0, state); break;
    case 0x41: return Bit(state.BC.low,  0, state); break;
    case 0x42: return Bit(state.DE.high, 0, state); break;
    case 0x43: return Bit(state.DE.low,  0, state); break;
    case 0x44: return Bit(state.HL.high, 0, state); break;
    case 0x45: return Bit(state.HL.low,  0, state); break;
    case 0x46: {
      int cycles = Bit(bus.Read(state.HL.reg), 0, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x47: return Bit(state.AF.high, 0, state); break;
    case 0x48: return Bit(state.BC.high, 1, state); break;
    case 0x49: return Bit(state.BC.low,  1, state); break;
    case 0x4A: return Bit(state.DE.high, 1, state); break;
    case 0x4B: return Bit(state.DE.low,  1, state); break;
    case 0x4C: return Bit(state.HL.high, 1, state); break;
    case 0x4D: return Bit(state.HL.low,  1, state); break;
    case 0x4E: {
      int cycles = Bit(bus.Read(state.HL.reg), 1, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x4F: return Bit(state.AF.high, 1, state); break;
    case 0x50: return Bit(state.BC.high, 2, state); break;
    case 0x51: return Bit(state.BC.low,  2, state); break;
    case 0x52: return Bit(state.DE.high, 2, state); break;
    case 0x53: return Bit(state.DE.low,  2, state); break;
    case 0x54: return Bit(state.HL.high, 2, state); break;
    case 0x55: return Bit(state.HL.low,  2, state); break;
    case 0x56: {
      int cycles = Bit(bus.Read(state.HL.reg), 2, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x57: return Bit(state.AF.high, 2, state); break;
    case 0x58: return Bit(state.BC.high, 3, state); break;
    case 0x59: return Bit(state.BC.low,  3, state); break;
    case 0x5A: return Bit(state.DE.high, 3, state); break;
    case 0x5B: return Bit(state.DE.low,  3, state); break;
    case 0x5C: return Bit(state.HL.high, 3, state); break;
    case 0x5D: return Bit(state.HL.low,  3, state); break;
    case 0x5E: {
      int cycles = Bit(bus.Read(state.HL.reg), 3, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x5F: return Bit(state.AF.high, 3, state); break;
    case 0x60: return Bit(state.BC.high, 4, state); break;
    case 0x61: return Bit(state.BC.low,  4, state); break;
    case 0x62: return Bit(state.DE.high, 4, state); break;
    case 0x63: return Bit(state.DE.low,  4, state); break;
    case 0x64: return Bit(state.HL.high, 4, state); break;
    case 0x65: return Bit(state.HL.low,  4, state); break;
    case 0x66: {
      int cycles = Bit(bus.Read(state.HL.reg), 4, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x67: return Bit(state.AF.high, 4, state); break;
    case 0x68: return Bit(state.BC.high, 5, state); break;
    case 0x69: return Bit(state.BC.low,  5, state); break;
    case 0x6A: return Bit(state.DE.high, 5, state); break;
    case 0x6B: return Bit(state.DE.low,  5, state); break;
    case 0x6C: return Bit(state.HL.high, 5, state); break;
    case 0x6D: return Bit(state.HL.low,  5, state); break;
    case 0x6E: {
      int cycles = Bit(bus.Read(state.HL.reg), 5, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x6F: return Bit(state.AF.high, 5, state); break;
    case 0x70: return Bit(state.BC.high, 6, state); break;
    case 0x71: return Bit(state.BC.low,  6, state); break;
    case 0x72: return Bit(state.DE.high, 6, state); break;
    case 0x73: return Bit(state.DE.low,  6, state); break;
    case 0x74: return Bit(state.HL.high, 6, state); break;
    case 0x75: return Bit(state.HL.low,  6, state); break;
    case 0x76: {
      int cycles = Bit(bus.Read(state.HL.reg), 6, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x77: return Bit(state.AF.high, 6, state); break;
    case 0x78: return Bit(state.BC.high, 7, state); break;
    case 0x79: return Bit(state.BC.low,  7, state); break;
    case 0x7A: return Bit(state.DE.high, 7, state); break;
    case 0x7B: return Bit(state.DE.low,  7, state); break;
    case 0x7C: return Bit(state.HL.high, 7, state); break;
    case 0x7D: return Bit(state.HL.low,  7, state); break;
    case 0x7E: {
      int cycles = Bit(bus.Read(state.HL.reg), 7, state);
      cycles += 4;
      return cycles;
    } break;
    case 0x7F: return Bit(state.AF.high, 7, state); break;
    case 0x80: return Res(state.BC.high, 0); break;
    case 0x81: return Res(state.BC.low,  0); break;
    case 0x82: return Res(state.DE.high, 0); break;
    case 0x83: return Res(state.DE.low,  0); break;
    case 0x84: return Res(state.HL.high, 0); break;
    case 0x85: return Res(state.HL.low,  0); break;
    case 0x86: {
      int cycles = Res(bus.Address(state.HL.reg), 0);
      cycles += 8;
      return cycles;
    } break;
    case 0x87: return Res(state.AF.high, 0); break;
    case 0x88: return Res(state.BC.high, 1); break;
    case 0x89: return Res(state.BC.low,  1); break;
    case 0x8A: return Res(state.DE.high, 1); break;
    case 0x8B: return Res(state.DE.low,  1); break;
    case 0x8C: return Res(state.HL.high, 1); break;
    case 0x8D: return Res(state.HL.low,  1); break;
    case 0x8E: {
      int cycles = Res(bus.Address(state.HL.reg), 1);
      cycles += 8;
      return cycles;
    } break;
    case 0x8F: return Res(state.AF.high, 1); break;
    case 0x90: return Res(state.BC.high, 2); break;
    case 0x91: return Res(state.BC.low,  2); break;
    case 0x92: return Res(state.DE.high, 2); break;
    case 0x93: return Res(state.DE.low,  2); break;
    case 0x94: return Res(state.HL.high, 2); break;
    case 0x95: return Res(state.HL.low,  2); break;
    case 0x96: {
      int cycles = Res(bus.Address(state.HL.reg), 2);
      cycles  += 8;
      return cycles;
    } break;
    case 0x97: return Res(state.AF.high, 2); break;
    case 0x98: return Res(state.BC.high, 3); break;
    case 0x99: return Res(state.BC.low,  3); break;
    case 0x9A: return Res(state.DE.high, 3); break;
    case 0x9B: return Res(state.DE.low,  3); break;
    case 0x9C: return Res(state.HL.high, 3); break;
    case 0x9D: return Res(state.HL.low,  3); break;
    case 0x9E: {
      int cycles = Res(bus.Address(state.HL.reg), 3);
      cycles += 8;
      return cycles;
    } break;
    case 0x9F: return Res(state.AF.high, 3); break;
    case 0xA0: return Res(state.BC.high, 4); break;
    case 0xA1: return Res(state.BC.low,  4); break;
    case 0xA2: return Res(state.DE.high, 4); break;
    case 0xA3: return Res(state.DE.low,  4); break;
    case 0xA4: return Res(state.HL.high, 4); break;
    case 0xA5: return Res(state.HL.low,  4); break;
    case 0xA6: {
      int cycles = Res(bus.Address(state.HL.reg), 4);
      cycles += 8;
      return cycles;
    } break;
    case 0xA7: return Res(state.AF.high, 4); break;
    case 0xA8: return Res(state.BC.high, 5); break;
    case 0xA9: return Res(state.BC.low,  5); break;
    case 0xAA: return Res(state.DE.high, 5); break;
    case 0xAB: return Res(state.DE.low,  5); break;
    case 0xAC: return Res(state.HL.high, 5); break;
    case 0xAD: return Res(state.HL.low,  5); break;
    case 0xAE: {
      int cycles = Res(bus.Address(state.HL.reg), 5);
      cycles += 8;
      return cycles;
    } break;
    case 0xAF: return Res(state.AF.high, 5); break;
    case 0xB0: return Res(state.BC.high, 6); break;
    case 0xB1: return Res(state.BC.low,  6); break;
    case 0xB2: return Res(state.DE.high, 6); break;
    case 0xB3: return Res(state.DE.low,  6); break;
    case 0xB4: return Res(state.HL.high, 6); break;
    case 0xB5: return Res(state.HL.low,  6); break;
    case 0xB6: {
      int cycles = Res(bus.Address(state.HL.reg), 6);
      cycles += 8;
      return cycles;
    } break;
    case 0xB7: return Res(state.AF.high, 6); break;
    case 0xB8: return Res(state.BC.high, 7); break;
    case 0xB9: return Res(state.BC.low,  7); break;
    case 0xBA: return Res(state.DE.high, 7); break;
    case 0xBB: return Res(state.DE.low,  7); break;
    case 0xBC: return Res(state.HL.high, 7); break;
    case 0xBD: return Res(state.HL.low,  7); break;
    case 0xBE: {
      int cycles = Res(bus.Address(state.HL.reg), 7);
      cycles += 8;
      return cycles;
    } break;
    case 0xBF: return Res(state.AF.high, 7); break;
    case 0xC0: return Set(state.BC.high, 0); break;
    case 0xC1: return Set(state.BC.low,  0); break;
    case 0xC2: return Set(state.DE.high, 0); break;
    case 0xC3: return Set(state.DE.low,  0); break;
    case 0xC4: return Set(state.HL.high, 0); break;
    case 0xC5: return Set(state.HL.low,  0); break;
    case 0xC6: {
      int cycles = Set(bus.Address(state.HL.reg), 0);
      cycles += 8;
      return cycles;
    } break;
    case 0xC7: return Set(state.AF.high, 0); break;
    case 0xC8: return Set(state.BC.high, 1); break;
    case 0xC9: return Set(state.BC.low,  1); break;
    case 0xCA: return Set(state.DE.high, 1); break;
    case 0xCB: return Set(state.DE.low,  1); break;
    case 0xCC: return Set(state.HL.high, 1); break;
    case 0xCD: return Set(state.HL.low,  1); break;
    case 0xCE: {
      int cycles = Set(bus.Address(state.HL.reg), 1);
      cycles += 8;
      return cycles;
    } break;
    case 0xCF: return Set(state.AF.high, 1); break;
    case 0xD0: return Set(state.BC.high, 2); break;
    case 0xD1: return Set(state.BC.low,  2); break;
    case 0xD2: return Set(state.DE.high, 2); break;
    case 0xD3: return Set(state.DE.low,  2); break;
    case 0xD4: return Set(state.HL.high, 2); break;
    case 0xD5: return Set(state.HL.low,  2); break;
    case 0xD6: {
      int cycles = Set(bus.Address(state.HL.reg), 2);
      cycles += 8;
      return cycles;
    } break;
    case 0xD7: return Set(state.AF.high, 2); break;
    case 0xD8: return Set(state.BC.high, 3); break;
    case 0xD9: return Set(state.BC.low,  3); break;
    case 0xDA: return Set(state.DE.high, 3); break;
    case 0xDB: return Set(state.DE.low,  3); break;
    case 0xDC: return Set(state.HL.high, 3); break;
    case 0xDD: return Set(state.HL.low,  3); break;
    case 0xDE: {
      int cycles = Set(bus.Address(state.HL.reg), 3);
      cycles += 8;
      return cycles;
    } break;
    case 0xDF: return Set(state.AF.high, 3); break;
    case 0xE0: return Set(state.BC.high, 4); break;
    case 0xE1: return Set(state.BC.low,  4); break;
    case 0xE2: return Set(state.DE.high, 4); break;
    case 0xE3: return Set(state.DE.low,  4); break;
    case 0xE4: return Set(state.HL.high, 4); break;
    case 0xE5: return Set(state.HL.low,  4); break;
    case 0xE6: {
      int cycles = Set(bus.Address(state.HL.reg), 4);
      cycles += 8;
      return cycles;
    } break;
    case 0xE7: return Set(state.AF.high, 4); break;
    case 0xE8: return Set(state.BC.high, 5); break;
    case 0xE9: return Set(state.BC.low,  5); break;
    case 0xEA: return Set(state.DE.high, 5); break;
    case 0xEB: return Set(state.DE.low,  5); break;
    case 0xEC: return Set(state.HL.high, 5); break;
    case 0xED: return Set(state.HL.low,  5); break;
    case 0xEE: {
      int cycles = Set(bus.Address(state.HL.reg), 5);
      cycles += 8;
      return cycles;
    } break;
    case 0xEF: return Set(state.AF.high, 5); break;
    case 0xF0: return Set(state.BC.high, 6); break;
    case 0xF1: return Set(state.BC.low,  6); break;
    case 0xF2: return Set(state.DE.high, 6); break;
    case 0xF3: return Set(state.DE.low,  6); break;
    case 0xF4: return Set(state.HL.high, 6); break;
    case 0xF5: return Set(state.HL.low,  6); break;
    case 0xF6: {
      int cycles = Set(bus.Address(state.HL.reg), 6);
      cycles += 8;
      return cycles;
    } break;
    case 0xF7: return Set(state.AF.high, 6); break;
    case 0xF8: return Set(state.BC.high, 7); break;
    case 0xF9: return Set(state.BC.low,  7); break;
    case 0xFA: return Set(state.DE.high, 7); break;
    case 0xFB: return Set(state.DE.low,  7); break;
    case 0xFC: return Set(state.HL.high, 7); break;
    case 0xFD: return Set(state.HL.low,  7); break;
    case 0xFE: {
      int cycles = Set(bus.Address(state.HL.reg), 7);
      cycles += 8;
      return cycles;
    } break;
    case 0xFF: return Set(state.AF.high, 7); break;
    default:
      throw NotImplemented(std::format("{}Unable to execute instruction {}CB {:#04x}{}", RED, BOLDRED, opcode, RESET));
  }

}

// NOLINTBEGIN(readability-convert-member-functions-to-static)
int Executor::Rlc(uint8_t& reg, CpuState &state)
{
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  reg = reg << 1U;
  reg = (reg & ~(1U << 0U)) | (bit7);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit7 == 1U);
  return 8;
}

int Executor::Rrc(uint8_t& reg, CpuState &state)
{
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;
  reg = (reg & ~(1U << 7U)) | (bit0 << 7U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);

  return 8;
}

int Executor::Rl(uint8_t& reg, CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  reg = reg << 1U;
  reg = (reg & ~(1U << 0U)) | (oldCY);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit7 == 1U);
  return 8;
}

int Executor::Rr(uint8_t& reg, CpuState &state)
{
  uint8_t oldCY = (state.AF.low & (1U << 4U)) >> 4U;
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;
  reg = (reg & ~(1U << 7U)) | (oldCY << 7U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);
  return 8;
}

int Executor::Sla(uint8_t& reg, CpuState &state)
{
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  reg = reg << 1U;

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit7 == 1U);
  return 8;
}

int Executor::Sra(uint8_t& reg, CpuState &state)
{
  uint8_t bit7 = (reg & 0x80U) >> 7U;
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;
  reg = (reg & ~(1U << 7U)) | (bit7 << 7U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);

  return 8;
}

int Executor::Srl(uint8_t& reg, CpuState &state)
{
  uint8_t bit0 = (reg & 0x01U);
  reg = reg >> 1U;

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, bit0 == 1U);

  return 8;
}

int Executor::Swap(uint8_t&reg, CpuState &state)
{
  uint8_t lowerNibble = (reg & 0x0FU);
  reg = reg >> 4U;
  reg = (reg & (0x0FU)) | (lowerNibble << 4U);

  SetZ(state, reg == 0);
  SetN(state, false);
  SetH(state, false);
  SetCY(state, false);

  return 8;
}


int Executor::Bit(uint8_t reg, uint8_t bit, CpuState &state)
{ 
  uint8_t bitX = (reg & (1U << bit)) >> bit;
  state.AF.low = (state.AF.low & ~(1U << 7U)) | ((!bitX) << 7U);
  SetN(state, false);
  SetH(state, true);

  return 8;
}

int Executor::Res(uint8_t &reg, uint8_t bit)
{
  reg = (reg & ~(1U << bit));
  return 8;
}

int Executor::Set(uint8_t &reg, uint8_t bit)
{
  reg = (reg & ~(1U << bit)) | (1U << bit);
  return 8;
}

// NOLINTEND(readability-convert-member-functions-to-static)
