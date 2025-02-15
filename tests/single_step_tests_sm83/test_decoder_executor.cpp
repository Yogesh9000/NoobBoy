#include "common.hpp"
#include "decoder.hpp"
#include "executor.hpp"
#include "simple_bus.hpp"
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
#define DEFINE_TEST(TEST_SUITE_NAME, TEST_NAME)                                                               \
  TEST(TEST_SUITE_NAME, TEST_NAME)                                                                            \
  {                                                                                                           \
    std::ifstream file{ "data/" EXPAND_AND_STRINGIFY(TEST_NAME) ".json" };                                    \
    ASSERT_TRUE(file.is_open());                                                                              \
    json tests = json::parse(file);                                                                           \
    SimpleBus bus{};                                                                                          \
    Executor executor;                                                                                        \
    Decoder decoder;                                                                                          \
    for (const auto &test : tests)                                                                            \
    {                                                                                                         \
      auto initialState = CreateInitialStateFromJson(test);                                                   \
      auto finalState = CreateFinalStateFromJson(test);                                                       \
      bus.Reset();                                                                                            \
      InitializeBusFromJson(bus, test["initial"]);                                                            \
      auto opcode = bus.Read(initialState.PC.reg++);                                                          \
      decoder.DecodeAndExecute(opcode, initialState, bus, executor);                                          \
      ASSERT_EQ(initialState, finalState)                                                                     \
        << std::format("Test Name: {} [Final State does not match]", static_cast<std::string>(test["name"])); \
      for (const auto &memState : test["final"]["ram"])                                                       \
      {                                                                                                       \
        uint16_t loc = memState[0];                                                                           \
        uint8_t data = memState[1];                                                                           \
        ASSERT_EQ(bus.Read(loc), data) << std::format(                                                        \
          "Test Name: {} [Memory State Does not Match]", static_cast<std::string>(test["name"]));             \
      }                                                                                                       \
    }                                                                                                         \
  }

DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 00);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 01);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 02);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 03);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 04);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 05);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 06);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 07);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 08);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 09);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 0a);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 0b);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 0c);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 0d);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 0e);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 0f);


DEFINE_TEST(SINGLE_STEP_TESTS_SM83, DISABLED_10); // TODO: find why there are extra cycles in test
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 11);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 12);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 13);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 14);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 15);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 16);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 17);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 18);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 19);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 1a);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 1b);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 1c);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 1d);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 1e);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 1f);


DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 20);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 21);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 22);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 23);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 24);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 25);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 26);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 27);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 28);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 29);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 2a);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 2b);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 2c);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 2d);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 2e);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 2f);

DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 30);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 31);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 32);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 33);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 34);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 35);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 36);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 37);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 38);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 39);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 3a);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 3b);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 3c);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 3d);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 3e);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 3f);

DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 40);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 41);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 42);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 43);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 44);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 45);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 46);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 47);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 48);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 49);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 4a);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 4b);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 4c);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 4d);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 4e);
DEFINE_TEST(SINGLE_STEP_TESTS_SM83, 4f);
