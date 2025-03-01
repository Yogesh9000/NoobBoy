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


void Cpu::Tick()
{
  throw NotImplemented("Cpu is not yet functional");
  if (m_state.ie_delay)
  {
    --m_state.ie_delay;
    m_state.ime = m_state.ie_delay == 0;
  }

  if (m_state.Ishalted)
    return;

  auto opcode = m_bus.Read(m_state.PC.reg);
  ++m_state.PC.reg; // increment Program Counter
  m_executor.DecodeAndExecute(opcode, m_state, m_bus);
}

void Cpu::SetInitialState()
{
  m_state.AF.reg = 0x01B0;
  m_state.BC.reg = 0x0013;
  m_state.DE.reg = 0x00D8;
  m_state.HL.reg = 0x014D;
  m_state.SP.reg = 0xFFFE;
  m_state.PC.reg = 0x0100;
  m_state.ime = false;
  m_state.Ishalted = false;
  m_state.ie_delay = 0;
  m_state.t_cycles = 0;
}
