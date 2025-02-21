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

  // Arithmetic
  void Add_R(uint8_t reg, CpuState &state);
  void Add_HL(CpuState &state, Bus &bus);
  void Add_N(CpuState &state, Bus &bus);
  void Add_HL_RR(uint16_t src, CpuState &state);
  void Add_SP_E(CpuState &state, Bus &bus);

  // Helper functions
  static uint16_t ToU16(uint8_t msb, uint8_t lsb);
  static void SetZ(CpuState &state, bool value);
  static void SetN(CpuState &state, bool value);
  static void SetH(CpuState &state, bool value);
  static void SetCY(CpuState &state, bool value);
};
