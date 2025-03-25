#include "cpu.hpp"
#include "common.hpp"
#include <cstdint>

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


int Cpu::Tick()
{
  if (m_state.ie_delay)
  {
    --m_state.ie_delay;
    m_state.ime = m_state.ie_delay == 0;
  }

  HandleInterrupts();

  if (m_state.IsHalted)
    return 0;

  auto opcode = m_bus.Read(m_state.PC.reg);
  ++m_state.PC.reg; // increment Program Counter
  int cycles = m_executor.DecodeAndExecute(opcode, m_state, m_bus);

  m_state.t_cycles += cycles;

  return cycles;
}

// TODO: Emulate halt bug
void Cpu::HandleInterrupts()
{
  auto call = [](uint16_t address, CpuState &state, Bus &bus) {
    bus.Write(--state.SP.reg, state.PC.high);
    bus.Write(--state.SP.reg, state.PC.low);
    state.PC.reg = address;
  };

  uint8_t& IE = m_bus.Address(0xFFFF);
  uint8_t& IF = m_bus.Address(0xFF0F);
  uint8_t pendingInterrupts = IE & IF;

  // If both the interrupt request flag (IF) and the corresponding interrupt enable flag (IE) are set,
  // HALT mode is exited, even if the interrupt master enable flag (IME) is not set
  if (pendingInterrupts)
  {
    m_state.IsHalted = false;
  }

  // If IME is enabled service any pendingInterrupts based on priority
  if (pendingInterrupts && m_state.ime)
  {
    // Disable IME before calling the interrupt handler
    m_state.ime = false;
    if (pendingInterrupts & (1U << 0U)) { // VBlank
      IF &= ~(1U << 0U);
      call(0x40U, m_state, m_bus);
    }
    else if (pendingInterrupts & (1U << 1U)) { // LCD STAT
      IF &= ~(1U << 1U);
      call(0x48U, m_state, m_bus);
    }
    else if (pendingInterrupts & (1U << 2U)) { // Timer
      IF &= ~(1U << 2U);
      call(0x50U, m_state, m_bus);
    }
    else if (pendingInterrupts & (1U << 3U)) { // Serial
      IF &= ~(1U << 3U);
      call(0x58U, m_state, m_bus);
    }
    else if (pendingInterrupts & (1U << 4U)) { // Joypad
      IF &= ~(1U << 4U);
      call(0x60U, m_state, m_bus);
    }
    
    m_state.t_cycles += 20; // It takes 5 clock cycles to service a routine
  }
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
  m_state.IsHalted = false;
  m_state.ie_delay = 0;
  m_state.t_cycles = 0;
}
