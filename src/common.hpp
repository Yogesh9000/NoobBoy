#pragma once

#include <format>
#include <ostream>
#include <sys/stat.h>
#define RESET "\033[0m"
#define RED "\033[31m"      /* Red */
#define BOLDRED "\033[1m\033[31m"      /* Bold Red */

#include <cstdint>

class NotImplemented : public std::logic_error
{
public:
    explicit NotImplemented(const std::string& msg) : std::logic_error(msg) { };
};

union Register
{
  uint16_t reg;
  struct
  {
    uint8_t low;
    uint8_t high;
  };
};


struct CpuState
{
  Register AF;
  Register BC;
  Register DE;
  Register HL;
  Register SP;
  Register PC;
  bool IsHalted;
  bool ime;
  uint8_t ie_delay;

  uint64_t t_cycles;

  bool operator==(const CpuState &state) const
  {
    return (AF.reg == state.AF.reg) && (BC.reg == state.BC.reg) && (DE.reg == state.DE.reg) && (HL.reg == state.HL.reg)
           && (SP.reg == state.SP.reg) && (PC.reg == state.PC.reg) && (IsHalted == state.IsHalted) && (ime == state.ime);
  }

  friend std::ostream &operator<<(std::ostream &os, const CpuState &state);
};

inline std::ostream &operator<<(std::ostream &os, const CpuState &state)
{
  os << std::format("{{A={}, B={}, C={}, D={}, E={}, H={}, L={}, F={}, SP={}, PC={}, halted={}, ime={}, ie_delay={}",
    state.AF.high, state.BC.high, state.BC.low, state.DE.high, state.DE.low, state.HL.high,
    state.HL.low, state.AF.low, state.SP.reg, state.PC.reg, state.IsHalted, state.ime, state.ie_delay);
  return os;
}
