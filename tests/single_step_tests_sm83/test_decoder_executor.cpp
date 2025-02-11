#include "bus.hpp"
#include "common.hpp"
#include "decoder.hpp"
#include "executor.hpp"
#include <cstdint>
#include <fstream>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace
{
  CpuState CreateStateFromJson(const auto &cpuState)
  {
    CpuState state{};
    state.AF.low = cpuState["f"];
    state.AF.high = cpuState["a"];
    state.BC.low = cpuState["c"];
    state.BC.high = cpuState["b"];
    state.DE.low = cpuState["e"];
    state.DE.high = cpuState["d"];
    state.HL.low = cpuState["l"];
    state.HL.high = cpuState["h"];
    state.SP.reg = cpuState["sp"];
    state.PC.reg = cpuState["pc"];
    state.t_cycles = 0;
    return state;
  }

  CpuState CreateInitialStateFromJson(const auto &test)
  {
    return CreateStateFromJson(test["initial"]);
  }

  CpuState CreateFinalStateFromJson(const auto &test)
  {
    auto state = CreateStateFromJson(test["final"]);
    state.t_cycles = test["cycles"].size() * 4;
    return state;
  }

  void InitializeBusFromJson(auto &bus, const auto &cpuState)
  {
    for (const auto &memState : cpuState["ram"])
    {
      uint16_t loc = memState[0];
      uint8_t data = memState[1];
      bus.Write(loc, data);
    }
  }
}// namespace


// helper macros
#define STRINGIFY(x) #x
#define EXPAND_AND_STRINGIFY(x) STRINGIFY(x)

// Define the test macro
#define DEFINE_TEST(TEST_SUITE_NAME, TEST_NAME)                            \
  TEST(TEST_SUITE_NAME, TEST_NAME)                                         \
  {                                                                        \
    std::ifstream file{ "data/" EXPAND_AND_STRINGIFY(TEST_NAME) ".json" }; \
    ASSERT_TRUE(file.is_open());                                           \
    json tests = json::parse(file);                                        \
    Bus bus{};                                                             \
    Executor<CpuState, Bus> executor;                                      \
    Decoder<CpuState, Bus, Executor> decoder;                              \
    for (const auto &test : tests)                                         \
    {                                                                      \
      auto initialState = CreateInitialStateFromJson(test);                \
      auto finalState = CreateFinalStateFromJson(test);                    \
      bus.Reset();                                                         \
      InitializeBusFromJson(bus, test["initial"]);                         \
      auto opcode = bus.Read(initialState.PC.reg++);                       \
      decoder.DecodeAndExecute(opcode, initialState, bus, executor);       \
      ASSERT_EQ(initialState, finalState);                                 \
      for (const auto &memState : test["final"]["ram"])                    \
      {                                                                    \
        uint16_t loc = memState[0];                                        \
        uint8_t data = memState[1];                                        \
        ASSERT_EQ(bus.Read(loc), data);                                    \
      }                                                                    \
    }                                                                      \
  }
