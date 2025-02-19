#pragma once


// the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#include <format>
#include <ostream>
#include <sys/stat.h>
#define RESET "\033[0m"
#define BLACK "\033[30m"      /* Black */
#define RED "\033[31m"      /* Red */
#define GREEN "\033[32m"      /* Green */
#define YELLOW "\033[33m"      /* Yellow */
#define BLUE "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN "\033[36m"      /* Cyan */
#define WHITE "\033[37m"      /* White */
#define BOLDBLACK "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"      /* Bold White */

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
  bool ime;

  uint64_t t_cycles;

  bool operator==(const CpuState &state) const
  {
    return (AF.reg == state.AF.reg) && (BC.reg == state.BC.reg) && (DE.reg == state.DE.reg) && (HL.reg == state.HL.reg)
           && (SP.reg == state.SP.reg) && (PC.reg == state.PC.reg) && (ime == state.ime) && (t_cycles == state.t_cycles);
  }

  friend std::ostream &operator<<(std::ostream &os, const CpuState &state);
};

inline std::ostream &operator<<(std::ostream &os, const CpuState &state)
{
  os << std::format("{{A={}, B={}, C={}, D={}, E={}, H={}, L={}, F={}, SP={}, PC={}, ime={}, TCyles={}",
    state.AF.high, state.BC.high, state.BC.low, state.DE.high, state.DE.low, state.HL.high,
    state.HL.low, state.AF.low, state.SP.reg, state.PC.reg, state.ime, state.t_cycles);
  return os;
}
