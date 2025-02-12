#include "executor.hpp"
#include <format>

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

template<> void Executor::Execute<0>(CpuState &state, Bus &bus)
{
  state.t_cycles += 4;
}
template<> void Executor::Execute<1>(CpuState &state, Bus &bus)
{
    auto lsb = bus.Read(state.PC.reg++);
    auto msb = bus.Read(state.PC.reg++);
    state.BC.reg = ToU16(msb, lsb);
    state.t_cycles += 12;
}
template<> void Executor::Execute<2>(CpuState &state, Bus &bus)
{
    bus.Write(state.BC.reg, state.AF.high);
    state.t_cycles += 8;
}
template<> void Executor::Execute<3>(CpuState &state, Bus &bus)
{
    ++state.BC.reg;
    state.t_cycles += 8;
}
template<> void Executor::Execute<4>(CpuState &state, Bus &bus)
{
    uint16_t res = state.BC.high + 1;

    SetH(state, (res & (1U << 4U)) != (state.BC.high & (1U << 4U)));
    SetN(state, false);
    SetZ(state, (res & 0xFFU) == 0);

    state.BC.high = (res & 0xFFU);
    state.t_cycles += 4;
}
template<> void Executor::Execute<5>(CpuState &state, Bus &bus)
{
    uint8_t res = state.BC.high - 1;

    SetH(state, (res & (1U << 4U)) != (state.BC.high & (1U << 4U)));
    SetN(state, true);
    SetZ(state, res == 0);

    state.BC.high = res;
    state.t_cycles += 4;
}
template<> void Executor::Execute<6>(CpuState &state, Bus &bus)
{
    state.BC.high = bus.Read(state.PC.reg++);
    state.t_cycles += 8;
}
template<> void Executor::Execute<7>(CpuState &state, Bus &bus)
{
    SetZ(state, false);
    SetN(state, false);
    SetH(state, false);
    SetCY(state, (state.AF.high & (1U << 7U)) >> 7U);

    state.AF.high = state.AF.high << 1U;
    state.AF.high = ((state.AF.high & ~(1U << 0U)) | ((state.AF.low & (1U << 4U)) >> 4U));

    state.t_cycles += 4;
}
