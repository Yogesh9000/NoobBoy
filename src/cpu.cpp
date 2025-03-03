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


void Cpu::Tick()
{
  HandleInterrupts();

  if (m_state.ie_delay)
  {
    --m_state.ie_delay;
    m_state.ime = m_state.ie_delay == 0;
  }

  if (m_state.IsHalted)
    return;

  auto cyclesTillNow = m_state.t_cycles;
  auto opcode = m_bus.Read(m_state.PC.reg);
  ++m_state.PC.reg; // increment Program Counter
  m_executor.DecodeAndExecute(opcode, m_state, m_bus);
  m_cycles = m_state.t_cycles - cyclesTillNow;

  UpdateTimers();
}

// TODO: Emulate halt bug
void Cpu::HandleInterrupts()
{
  auto call = [](uint16_t address, CpuState &state, Bus &bus) {
    bus.Write(--state.SP.reg, state.PC.high);
    bus.Write(--state.SP.reg, state.PC.low);
    state.PC.reg = address;
  };

  uint8_t IE = m_bus.Address(0xFFFF);
  uint8_t IF = m_bus.Address(0xFF0F);
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

void Cpu::RequestInterrupt(uint8_t id)
{
  uint8_t IF = m_bus.Address(0xFF0F);
  IF |= (1U << id);
}

void Cpu::UpdateDividerRegister()
{
  m_dividerCounter += m_cycles;
  if (m_dividerCounter > 255)
  {
    m_dividerCounter = 0;
    // Using Address instead of Write to update DIV register,
    // since writing to DIV register reset's it to 0
    // TODO: Update bus to reset DIV register to 0 on Write
    auto div = m_bus.Address(0xFF04);
    ++div;
  }
}

void Cpu::UpdateTimers()
{
  UpdateDividerRegister();

  auto tima = m_bus.Address(0xFF05);
  auto tma = m_bus.Address(0xFF06);

  // Update the frequency at which TIMA is incremented
  if (m_timerFreq != GetClockFreq())
  {
    SetClockFreq();
  }

  // the clock must be enabled to update the clock 
  if (IsClockEnabled())
  {
    m_timerCounter -= m_cycles; 

    // enough cpu clock cycles have happened to update the timer
    if (m_timerCounter <= 0)
    {
      SetClockFreq();
      if (tima == 255)
      {
        tima = tma;
        RequestInterrupt(2);
      }
      else
      {
        ++tima;
      }
    }
  }

}

bool Cpu::IsClockEnabled()
{
  constexpr uint16_t TAC {0xFF07U};
  return (m_bus.Read(TAC) & (1U << 2U)) != 0;
}

uint8_t Cpu::GetClockFreq()
{
  constexpr uint16_t TAC {0xFF07U};
  return m_bus.Read(TAC) & 0x03U;
}

void Cpu::SetClockFreq()
{
  auto freq = GetClockFreq();
  switch (freq)
  {
    case 0: m_timerCounter = 1024;break;
    case 1: m_timerCounter = 16;break;
    case 2: m_timerCounter = 64;break;
    case 3: m_timerCounter = 256;break;
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
