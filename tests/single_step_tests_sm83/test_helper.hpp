#pragma once

#include "common.hpp"
#include "executor.hpp"
#include "dummy_bus.hpp"
#include <cstdint>
#include <fstream>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
  state.ime = static_cast<uint8_t>(cpuState["ime"]);
  state.t_cycles = 0;
  return state;
}

CpuState CreateInitialStateFromJson(const auto &test)
{
  return CreateStateFromJson(test["initial"]);
}

CpuState CreateFinalStateFromJson(const auto &test)
{
  return CreateStateFromJson(test["final"]);
}

void InitializeBusFromJson(auto &bus, const auto &cpuState, uint8_t ie)
{
  bus.Write(0xFFFFU, ie);
  for (const auto &memState : cpuState["ram"])
  {
    uint16_t loc = memState[0];
    uint8_t data = memState[1];
    bus.Write(loc, data);
  }
}


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
    DummyBus bus{};                                                                                           \
    Executor executor;                                                                                        \
    for (const auto &test : tests)                                                                            \
    {                                                                                                         \
      auto initialState = CreateInitialStateFromJson(test);                                                   \
      auto finalState = CreateFinalStateFromJson(test);                                                       \
      auto cycles = test["cycles"].size() * 4;                                                                \
      bus.Reset();                                                                                            \
      InitializeBusFromJson(bus, test["initial"], test["initial"]["ie"]);                                     \
      auto opcode = bus.Read(initialState.PC.reg++);                                                          \
      ASSERT_EQ(cycles, executor.DecodeAndExecute(opcode, initialState, bus));                                \
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

// Define the test macro
#define DEFINE_TEST_CB(TEST_SUITE_NAME, TEST_NAME)                                                            \
  TEST(TEST_SUITE_NAME, TEST_NAME)                                                                            \
  {                                                                                                           \
    std::ifstream file{ "data/cb " EXPAND_AND_STRINGIFY(TEST_NAME) ".json" };                                 \
    ASSERT_TRUE(file.is_open());                                                                              \
    json tests = json::parse(file);                                                                           \
    DummyBus bus{};                                                                                           \
    Executor executor;                                                                                        \
    for (const auto &test : tests)                                                                            \
    {                                                                                                         \
      auto initialState = CreateInitialStateFromJson(test);                                                   \
      auto finalState = CreateFinalStateFromJson(test);                                                       \
      auto cycles = test["cycles"].size() * 4;                                                                \
      bus.Reset();                                                                                            \
      InitializeBusFromJson(bus, test["initial"], test["initial"]["ie"]);                                     \
      auto opcode = bus.Read(initialState.PC.reg++);                                                          \
      ASSERT_EQ(cycles, executor.DecodeAndExecute(opcode, initialState, bus));                                \
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
