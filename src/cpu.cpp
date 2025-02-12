#include "cpu.hpp"
#include "common.hpp"

Cpu::Cpu(Bus &bus) : m_bus(bus) {}


CpuState Cpu::GetState() const
{
  return m_state;
}


void Cpu::SetState(const CpuState &state)
{
  m_state = state;
}


void Cpu::ResetState()
{
  SetInitialState();
}


void Step()
{
  throw NotImplemented("Cpu is not yet functional");
}

void Cpu::SetInitialState()
{
  m_state.AF.reg = 0x01B0;
  m_state.BC.reg = 0x0013;
  m_state.DE.reg = 0x00D8;
  m_state.HL.reg = 0x014D;
  m_state.SP.reg = 0xFFFE;
  m_state.PC.reg = 0x0100;
}
