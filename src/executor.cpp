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

// STOP
template <> void Executor::Execute<0x10>(CpuState &state, Bus &bus)
{
  state.t_cycles += 4;
}

// LD DE, u16
template <> void Executor::Execute<0x11>(CpuState &state, Bus &bus)
{
  auto lsb = bus.Read(state.PC.reg++);
  auto msb = bus.Read(state.PC.reg++);
  state.DE.reg = ToU16(msb, lsb);
  state.t_cycles += 12;
}

// LD (DE), A
template <> void Executor::Execute<0x12>(CpuState &state, Bus &bus)
{
  bus.Write(state.DE.reg, state.AF.high);
  state.t_cycles += 8;
}

// INC DE
template <> void Executor::Execute<0x13>(CpuState &state, Bus &bus)
{
  state.DE.reg = state.DE.reg + 1;
  state.t_cycles += 8;
}

// INC D
template <> void Executor::Execute<0x14>(CpuState &state, Bus &bus)
{
  uint16_t res = static_cast<uint16_t>(state.DE.high) + 1;

  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.DE.high & 0x0FU) + 1) > 0x0FU);

  state.DE.high = (res & 0xFFU);
  state.t_cycles += 4;
}

// DEC D
template <> void Executor::Execute<0x15>(CpuState &state, Bus &bus)
{
  uint8_t res = state.DE.high - 1;

  SetZ(state, res == 0);
  SetN(state, true);
  SetH(state, ((state.DE.high & 0xFU) - 1) > 0xFU);

  state.DE.high = res;
  state.t_cycles += 4;
}

// LD D, u8
template <> void Executor::Execute<0x16>(CpuState &state, Bus &bus)
{
  state.DE.high = bus.Read(state.PC.reg++);
  state.t_cycles += 8;
}

// RLA
template <> void Executor::Execute<0x17>(CpuState &state, Bus &bus)
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

// JR i8
template <> void Executor::Execute<0x18>(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  state.PC.reg = state.PC.reg + i8;
  state.t_cycles += 12;
}

// ADD HL, DE
template <> void Executor::Execute<0x19>(CpuState &state, Bus &bus)
{
  uint32_t res = static_cast<uint32_t>(state.HL.reg) + static_cast<uint32_t>(state.DE.reg);

  SetN(state, false);
  SetH(state, ((state.HL.reg & 0xFFFU) + (state.DE.reg & 0xFFFU)) > 0xFFFU);
  SetCY(state, res > 0xFFFF);

  state.HL.reg = (res & 0xFFFFU);
  state.t_cycles += 8;
}

// LD A, (DE)
template <> void Executor::Execute<0x1A>(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.DE.reg);
  state.t_cycles += 8;
}

// DEC DE
template <> void Executor::Execute<0x1B>(CpuState &state, Bus &bus)
{
  state.DE.reg = state.DE.reg - 1;
  state.t_cycles += 8;
}

// INC E
template <> void Executor::Execute<0x1C>(CpuState &state, Bus &bus)
{
  uint16_t res = static_cast<uint16_t>(state.DE.low) + 1;
  SetZ(state, (res & 0xFFU) == 0);
  SetN(state, false);
  SetH(state, ((state.DE.low & 0x0FU) + 1) > 0x0FU);

  state.DE.low = (res & 0xFFU);
  state.t_cycles += 4;
}

// DEC E
template <> void Executor::Execute<0x1D>(CpuState &state, Bus &bus)
{
  uint8_t res = state.DE.low - 1;
  SetZ(state, res == 0);
  SetN(state, true);
  SetH(state, ((state.DE.low & 0xFU) - 1) > 0xFU);

  state.DE.low = res;
  state.t_cycles += 4;
}

// LD E, u8
template <> void Executor::Execute<0x1E>(CpuState &state, Bus &bus)
{
  state.DE.low = bus.Read(state.PC.reg++);
  state.t_cycles += 8;
}

// RRA
template <> void Executor::Execute<0x1F>(CpuState &state, Bus &bus)
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

// JR NZ, i8
template <> void Executor::Execute<0x20>(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  if ((state.AF.low & (1U << 7U)) == 0)
  {
    state.PC.reg = state.PC.reg + i8;
    state.t_cycles += 12;
  }
  else
  {
    state.t_cycles += 8;
  }
}

// LD HL, u16
template <> void Executor::Execute<0x21>(CpuState &state, Bus &bus)
{
  auto lsb = bus.Read(state.PC.reg++);
  auto msb = bus.Read(state.PC.reg++);

  state.HL.reg = ToU16(msb, lsb);

  state.t_cycles += 12;
}

// LD (HL+), A
template <> void Executor::Execute<0x22>(CpuState &state, Bus &bus)
{
  bus.Write(state.HL.reg, state.AF.high);
  state.HL.reg = state.HL.reg + 1;
  state.t_cycles += 8;
}

// INC HL
template <> void Executor::Execute<0x23>(CpuState &state, Bus &bus)
{
  state.HL.reg = state.HL.reg + 1;
  state.t_cycles += 8;
}

// INC H
template<> void Executor::Execute<0x24>(CpuState &state, Bus &bus)
{
    uint16_t res = state.HL.high + 1;

    SetH(state, (res & (1U << 4U)) != (state.HL.high & (1U << 4U)));
    SetN(state, false);
    SetZ(state, (res & 0xFFU) == 0);

    state.HL.high = (res & 0xFFU);
    state.t_cycles += 4;
}

// DEC B
template<> void Executor::Execute<0x25>(CpuState &state, Bus &bus)
{
    uint8_t res = state.HL.high - 1;

    SetZ(state, res == 0);
    SetN(state, true);
    SetH(state, ((state.HL.high & 0xFU) - 1) > 0xFU);

    state.HL.high = res;
    state.t_cycles += 4;
}

// LD H, u8
template<> void Executor::Execute<0x26>(CpuState &state, Bus &bus)
{
    state.HL.high = bus.Read(state.PC.reg++);
    state.t_cycles += 8;
}

// DAA (https://forums.nesdev.org/viewtopic.php?p=196282&sid=a1cdd6adc0b01ea3d77f61aee9527449#p196282)
template <> void Executor::Execute<0x27>(CpuState &state, Bus &bus)
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

// JR Z, i8
template <> void Executor::Execute<0x28>(CpuState &state, Bus &bus)
{
  auto i8 = static_cast<int8_t>(bus.Read(state.PC.reg++));
  if ((state.AF.low & (1U << 7U)) != 0)
  {
    state.PC.reg = state.PC.reg + i8;
    state.t_cycles += 12;
  }
  else
  {
    state.t_cycles += 8;
  }
}

// ADD HL, HL
template <> void Executor::Execute<0x29>(CpuState &state, Bus &bus)
{
  uint32_t res = static_cast<uint32_t>(state.HL.reg) + static_cast<uint32_t>(state.HL.reg);

  SetN(state, false);
  SetH(state, ((state.HL.reg & 0xFFFU) + (state.HL.reg & 0xFFFU)) > 0xFFFU);
  SetCY(state, res >= 0xFFFFU);

  state.HL.reg = res & 0xFFFFU;
  state.t_cycles += 8;
}

// LD A, (HL+)
template <> void Executor::Execute<0x2A>(CpuState &state, Bus &bus)
{
  state.AF.high = bus.Read(state.HL.reg);
  state.HL.reg = state.HL.reg + 1;
  state.t_cycles += 8;
}

// DEC BC
template <> void Executor::Execute<0x2B>(CpuState &state, Bus &bus)
{
  state.HL.reg = state.HL.reg - 1;
  state.t_cycles += 8;
}

// INC L
template<> void Executor::Execute<0x2C>(CpuState &state, Bus &bus)
{
    uint16_t res = state.HL.low + 1;

    SetH(state, (res & (1U << 4U)) != (state.HL.low & (1U << 4U)));
    SetN(state, false);
    SetZ(state, (res & 0xFFU) == 0);

    state.HL.low = (res & 0xFFU);
    state.t_cycles += 4;
}

// DEC L
template<> void Executor::Execute<0x2D>(CpuState &state, Bus &bus)
{
    uint8_t res = state.HL.low - 1;

    SetZ(state, res == 0);
    SetN(state, true);
    SetH(state, ((state.HL.low & 0xFU) - 1) > 0xFU);

    state.HL.low = res;
    state.t_cycles += 4;
}

// LD L, u8
template<> void Executor::Execute<0x2E>(CpuState &state, Bus &bus)
{
    state.HL.low = bus.Read(state.PC.reg++);
    state.t_cycles += 8;
}

// CPL
template <> void Executor::Execute<0x2F>(CpuState &state, Bus &bus)
{
  SetN(state, true);
  SetH(state, true);

  state.AF.high = ~state.AF.high;
  state.t_cycles += 4;
}
