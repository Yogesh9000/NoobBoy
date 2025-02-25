#pragma once

#include "bus.hpp"
#include "common.hpp"
#include <cstdint>

class Executor
{
public:
  void DecodeAndExecute(uint8_t opcode, CpuState &state, Bus &bus);

private:

  // Special
  void Nop(CpuState &state);
  void Stop(CpuState &state);
  void Halt(CpuState &state);
  void Di(CpuState &state);
  void Ei(CpuState &state);

  // Load
  void Load_R_R(uint8_t &dest, uint8_t src, CpuState &state);
  void Load_R_N(uint8_t &dest, CpuState &state, Bus &bus);
  void Load_RR_NN(uint16_t& dest, CpuState &state, Bus &bus);
  void Load_R_HL(uint8_t &dest, CpuState &state, Bus &bus);
  void Load_HL_R(uint8_t &src, CpuState &state, Bus &bus);
  void Load_HL_N(CpuState &state, Bus &bus);
  void Load_A_BC(CpuState &state, Bus &bus);
  void Load_A_DE(CpuState &state, Bus &bus);
  void Load_BC_A(CpuState &state, Bus &bus);
  void Load_DE_A(CpuState &state, Bus &bus);
  void Load_A_NN(CpuState &state, Bus &bus);
  void Load_NN_A(CpuState &state, Bus &bus);
  void Load_HL_A_Neg(CpuState &state, Bus &bus);
  void Load_HL_A_Pos(CpuState &state, Bus &bus);
  void Load_A_HL_Neg(CpuState &state, Bus &bus);
  void Load_A_HL_Pos(CpuState &state, Bus &bus);
  void Load_NN_SP(CpuState &state, Bus &bus);
  void Load_N_A(CpuState &state, Bus &bus);
  void Load_A_N(CpuState &state, Bus &bus);
  void Load_C_A(CpuState &state, Bus &bus);
  void Load_A_C(CpuState &state, Bus &bus);
  void Load_SP_HL(CpuState &state, Bus &bus);
  void Load_HL_SP_E(CpuState &state, Bus &bus);
  void Pop(Register &reg, CpuState &state, Bus &bus);
  void Push(Register &reg, CpuState &state, Bus &bus);

  // Arithmetic
  void Add_R(uint8_t reg, CpuState &state);
  void Add_HL(CpuState &state, Bus &bus);
  void Add_N(CpuState &state, Bus &bus);
  void Add_HL_RR(uint16_t src, CpuState &state);
  void Add_SP_E(CpuState &state, Bus &bus);

  void Adc_R(uint8_t reg, CpuState &state);
  void Adc_HL(CpuState &state, Bus &bus);
  void Adc_N(CpuState &state, Bus &bus);

  void Sub_R(uint8_t reg, CpuState &state);
  void Sub_HL(CpuState &state, Bus &bus);
  void Sub_N(CpuState &state, Bus &bus);

  void Sbc_R(uint8_t reg, CpuState &state);
  void Sbc_HL(CpuState &state, Bus &bus);
  void Sbc_N(CpuState &state, Bus &bus);

  void And_R(uint8_t reg, CpuState &state);
  void And_HL(CpuState &state, Bus &bus);
  void And_N(CpuState &state, Bus &bus);

  void Xor_R(uint8_t reg, CpuState &state);
  void Xor_HL(CpuState &state, Bus &bus);
  void Xor_N(CpuState &state, Bus &bus);
  
  void Or_R(uint8_t reg, CpuState &state);
  void Or_HL(CpuState &state, Bus &bus);
  void Or_N(CpuState &state, Bus &bus);

  void Cp_R(uint8_t reg, CpuState &state);
  void Cp_HL(CpuState &state, Bus &bus);
  void Cp_N(CpuState &state, Bus &bus);

  void Inc_R(uint8_t &src, CpuState &state);
  void Inc_RR(uint16_t &src, CpuState &state);
  void Inc_HL(CpuState &state, Bus &bus);

  void Dec_R(uint8_t &src, CpuState &state);
  void Dec_RR(uint16_t &src, CpuState &state);
  void Dec_HL(CpuState &state, Bus &bus);

  void Ccf(CpuState &state);
  void Scf(CpuState &state);
  void Daa(CpuState &state);
  void Cpl(CpuState &state);

  // Control Flow
  void Jp_NN(CpuState &state, Bus &bus);
  void Jp_HL(CpuState &state);
  void Jp_CC_NN(bool jmp, CpuState &state, Bus &bus);

  void Jr_E(CpuState &state, Bus &bus);
  void Jr_CC_E(bool jmp, CpuState &state, Bus &bus);

  void Call_NN(CpuState &state, Bus &bus);
  void Call_CC_NN(bool call, CpuState &state, Bus &bus);

  void Ret(CpuState &state, Bus &bus);
  void Ret_CC(bool ret, CpuState &state, Bus &bus);
  void RetI(CpuState &state, Bus &bus);
  void Rst(uint8_t addr, CpuState &state, Bus &bus);

  // Rotate-Shift
  void Rlca(CpuState &state);
  void Rla(CpuState &state);
  void Rrca(CpuState &state);
  void Rra(CpuState &state);

  // Helper functions
  static uint16_t ToU16(uint8_t msb, uint8_t lsb);
  static void SetZ(CpuState &state, bool value);
  static void SetN(CpuState &state, bool value);
  static void SetH(CpuState &state, bool value);
  static void SetCY(CpuState &state, bool value);
};
