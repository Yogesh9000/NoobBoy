#pragma once

#include "common.hpp"

template<typename CpuStateT,
  typename BusT,
  template<typename, typename> typename ExecutorT,
  template<typename, typename, template<typename, typename> typename> typename DecoderT>
class Cpu
{
public:
  Cpu()
  {
    SetInitialState();
  }

  // Get current cpu state
  [[nodiscard]]
  CpuState GetState() const
  {
    return m_state;
  }

  // Set current cpu state
  void SetState(const CpuState &state)
  {
    m_state = state;
  }

  // Reset Cpu state to initial state
  void ResetState()
  {
    SetInitialState();
  }

  void Step()
  {
    auto opcode = m_bus.Read(m_state.PC.reg++);
    m_decoder.DecodeAndExecute(opcode, m_state, m_bus, m_executor);
  }

private:
  // helper methods
  void SetInitialState()
  {
    m_state.AF.reg = 0x01B0;
    m_state.BC.reg = 0x0013;
    m_state.DE.reg = 0x00D8;
    m_state.HL.reg = 0x014D;
    m_state.SP.reg = 0xFFFE;
    m_state.PC.reg = 0x0100;
  }

  // internal state of cpu
  CpuStateT m_state{};
  BusT m_bus{};
  ExecutorT<CpuStateT, BusT>  m_executor{};
  DecoderT<CpuStateT, BusT, ExecutorT> m_decoder{};
};
