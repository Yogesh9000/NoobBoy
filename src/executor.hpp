#pragma once

#include "bus.hpp"
#include "common.hpp"
#include <cstdint>

class Executor
{
public:
  int DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus);

private:
  int DecodeAndExecuteCB(uint8_t opcode, CpuState &state, Bus &bus);

  // Special
  int Nop(CpuState &state);
  int Stop(CpuState &state);
  int Halt(CpuState &state);
  int Di(CpuState &state);
  int Ei(CpuState &state);

  // Load
  int Load_R_R(uint8_t &dest, uint8_t src, CpuState &state);
  int Load_R_N(uint8_t &dest, CpuState &state, Bus &bus);
  int Load_RR_NN(uint16_t& dest, CpuState &state, Bus &bus);
  int Load_R_HL(uint8_t &dest, CpuState &state, Bus &bus);
  int Load_HL_R(uint8_t &src, CpuState &state, Bus &bus);
  int Load_HL_N(CpuState &state, Bus &bus);
  int Load_A_BC(CpuState &state, Bus &bus);
  int Load_A_DE(CpuState &state, Bus &bus);
  int Load_BC_A(CpuState &state, Bus &bus);
  int Load_DE_A(CpuState &state, Bus &bus);
  int Load_A_NN(CpuState &state, Bus &bus);
  int Load_NN_A(CpuState &state, Bus &bus);
  int Load_HL_A_Neg(CpuState &state, Bus &bus);
  int Load_HL_A_Pos(CpuState &state, Bus &bus);
  int Load_A_HL_Neg(CpuState &state, Bus &bus);
  int Load_A_HL_Pos(CpuState &state, Bus &bus);
  int Load_NN_SP(CpuState &state, Bus &bus);
  int Load_N_A(CpuState &state, Bus &bus);
  int Load_A_N(CpuState &state, Bus &bus);
  int Load_C_A(CpuState &state, Bus &bus);
  int Load_A_C(CpuState &state, Bus &bus);
  int Load_SP_HL(CpuState &state, Bus &bus);
  int Load_HL_SP_E(CpuState &state, Bus &bus);
  int Pop(Register &reg, CpuState &state, Bus &bus);
  int Push(Register &reg, CpuState &state, Bus &bus);

  // Arithmetic
  int Add_R(uint8_t reg, CpuState &state);
  int Add_HL(CpuState &state, Bus &bus);
  int Add_N(CpuState &state, Bus &bus);
  int Add_HL_RR(uint16_t src, CpuState &state);
  int Add_SP_E(CpuState &state, Bus &bus);

  int Adc_R(uint8_t reg, CpuState &state);
  int Adc_HL(CpuState &state, Bus &bus);
  int Adc_N(CpuState &state, Bus &bus);

  int Sub_R(uint8_t reg, CpuState &state);
  int Sub_HL(CpuState &state, Bus &bus);
  int Sub_N(CpuState &state, Bus &bus);

  int Sbc_R(uint8_t reg, CpuState &state);
  int Sbc_HL(CpuState &state, Bus &bus);
  int Sbc_N(CpuState &state, Bus &bus);

  int And_R(uint8_t reg, CpuState &state);
  int And_HL(CpuState &state, Bus &bus);
  int And_N(CpuState &state, Bus &bus);

  int Xor_R(uint8_t reg, CpuState &state);
  int Xor_HL(CpuState &state, Bus &bus);
  int Xor_N(CpuState &state, Bus &bus);
  
  int Or_R(uint8_t reg, CpuState &state);
  int Or_HL(CpuState &state, Bus &bus);
  int Or_N(CpuState &state, Bus &bus);

  int Cp_R(uint8_t reg, CpuState &state);
  int Cp_HL(CpuState &state, Bus &bus);
  int Cp_N(CpuState &state, Bus &bus);

  int Inc_R(uint8_t &src, CpuState &state);
  int Inc_RR(uint16_t &src, CpuState &state);
  int Inc_HL(CpuState &state, Bus &bus);

  int Dec_R(uint8_t &src, CpuState &state);
  int Dec_RR(uint16_t &src, CpuState &state);
  int Dec_HL(CpuState &state, Bus &bus);

  int Ccf(CpuState &state);
  int Scf(CpuState &state);
  int Daa(CpuState &state);
  int Cpl(CpuState &state);

  // Control Flow
  int Jp_NN(CpuState &state, Bus &bus);
  int Jp_HL(CpuState &state);
  int Jp_CC_NN(bool jmp, CpuState &state, Bus &bus);

  int Jr_E(CpuState &state, Bus &bus);
  int Jr_CC_E(bool jmp, CpuState &state, Bus &bus);

  int Call_NN(CpuState &state, Bus &bus);
  int Call_CC_NN(bool call, CpuState &state, Bus &bus);

  int Ret(CpuState &state, Bus &bus);
  int Ret_CC(bool ret, CpuState &state, Bus &bus);
  int RetI(CpuState &state, Bus &bus);
  int Rst(uint8_t addr, CpuState &state, Bus &bus);

  // Rotate-Shift
  int Rlca(CpuState &state);
  int Rla(CpuState &state);
  int Rrca(CpuState &state);
  int Rra(CpuState &state);

  //===============CB Prefixed Instrucitons=======================
  int Rlc(uint8_t &reg, CpuState &state);
  int Rrc(uint8_t &reg, CpuState &state);
  int Rl(uint8_t &reg, CpuState &state);
  int Rr(uint8_t &reg, CpuState &state);
  int Sla(uint8_t &reg, CpuState &state);
  int Sra(uint8_t &reg, CpuState &state);
  int Swap(uint8_t &reg, CpuState &state);
  int Srl(uint8_t &reg, CpuState &state);
  int Bit(uint8_t reg, uint8_t bit, CpuState &state);
  int Res(uint8_t &reg, uint8_t bit, CpuState &state);
  int Set(uint8_t &reg, uint8_t bit, CpuState &state);

  // Helper functions
  static uint16_t ToU16(uint8_t msb, uint8_t lsb);
  static void SetZ(CpuState &state, bool value);
  static void SetN(CpuState &state, bool value);
  static void SetH(CpuState &state, bool value);
  static void SetCY(CpuState &state, bool value);
};
