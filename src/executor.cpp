#include "executor.hpp"
#include "common.hpp"
#include <cstdint>

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

// NOP
template<> void Executor::Execute<0x00>(CpuState &state, Bus &bus)
{
  state.t_cycles += 4;
}

// LD BC, u16
template<> void Executor::Execute<0x01>(CpuState &state, Bus &bus)
{
    auto lsb = bus.Read(state.PC.reg++);
    auto msb = bus.Read(state.PC.reg++);
    state.BC.reg = ToU16(msb, lsb);
    state.t_cycles += 12;
}

// LD (BC), A
template<> void Executor::Execute<0x02>(CpuState &state, Bus &bus)
{
    bus.Write(state.BC.reg, state.AF.high);
    state.t_cycles += 8;
}

// INC BC
template<> void Executor::Execute<0x03>(CpuState &state, Bus &bus)
{
    ++state.BC.reg;
    state.t_cycles += 8;
}

// INC B
template<> void Executor::Execute<0x04>(CpuState &state, Bus &bus)
{
    uint16_t res = state.BC.high + 1;

    SetH(state, (res & (1U << 4U)) != (state.BC.high & (1U << 4U)));
    SetN(state, false);
    SetZ(state, (res & 0xFFU) == 0);

    state.BC.high = (res & 0xFFU);
    state.t_cycles += 4;
}

// DEC B
template<> void Executor::Execute<0x05>(CpuState &state, Bus &bus)
{
    uint8_t res = state.BC.high - 1;

    SetZ(state, res == 0);
    SetN(state, true);
    SetH(state, ((state.BC.high & 0xFU) - 1) > 0xFU);

    state.BC.high = res;
    state.t_cycles += 4;
}

// LD B, u8
template<> void Executor::Execute<0x06>(CpuState &state, Bus &bus)
{
    state.BC.high = bus.Read(state.PC.reg++);
    state.t_cycles += 8;
}

// RLCA
template<> void Executor::Execute<0x07>(CpuState &state, Bus &bus)
{
    SetZ(state, false);
    SetN(state, false);
    SetH(state, false);
    SetCY(state, (state.AF.high & (1U << 7U)) >> 7U);

    state.AF.high = state.AF.high << 1U;
    state.AF.high = ((state.AF.high & ~(1U << 0U)) | ((state.AF.low & (1U << 4U)) >> 4U));

    state.t_cycles += 4;
}

// LD (u16), SP
template <> void Executor::Execute<0x08>(CpuState &state, Bus &bus)
{
  uint8_t lsb = bus.Read(state.PC.reg++);
  uint8_t msb = bus.Read(state.PC.reg++);
  uint16_t nn = ToU16(msb, lsb);
  bus.Write(nn, state.SP.low);
  ++nn;
  bus.Write(nn, state.SP.high);
  state.t_cycles += 20;
}

// ADD HL, BC
template <> void Executor::Execute<0x09>(CpuState &state, Bus &bus)
{
  uint32_t res = static_cast<uint32_t>(state.HL.reg) + static_cast<uint32_t>(state.BC.reg);

  SetN(state, false);
  SetH(state, ((state.HL.reg & 0xFFFU) + (state.BC.reg & 0xFFFU)) > 0xFFFU);
  SetCY(state, res >= 0xFFFFU);

  state.HL.reg = res & 0xFFFFU;
  state.t_cycles += 8;
}

// LD A, (BC)
template <> void Executor::Execute<0x0A>(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.BC.reg);
  state.t_cycles += 8;
}

// DEC BC
template <> void Executor::Execute<0x0B>(CpuState &state, Bus &bus)
{
  state.BC.reg = state.BC.reg - 1;
  state.t_cycles += 8;
}

// INC C
template <> void Executor::Execute<0x0C>(CpuState &state, Bus &bus)
{
  uint16_t res = static_cast<uint16_t>(state.BC.low) + 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.BC.low & 0xFU) + 1) > 0xFU);

  state.BC.low = (res & 0xFFU);
  state.t_cycles += 4;
}

// DEC C
template <> void Executor::Execute<0x0D>(CpuState &state, Bus &bus)
{
  uint8_t res = state.BC.low - 1;

  SetZ(state, res == 0);
  SetN(state, true);
  SetH(state, ((state.BC.low & 0xFU) - 1) > 0xFU);

  state.BC.low = res;
  state.t_cycles += 4;
}

// LD C, u8
template <> void Executor::Execute<0x0E>(CpuState &state, Bus &bus)
{
  state.BC.low = bus.Read(state.PC.reg++);
  state.t_cycles += 8;
}

// RRCA
template <> void Executor::Execute<0x0F>(CpuState &state, Bus &bus)
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
