#pragma once

#include "cpu.hpp"
#include "executor.hpp"
#include "timer.hpp"
#include <gtest/gtest.h>


// Define the test macro
#define DEFINE_TEST(TEST_SUITE_NAME, TEST_NAME, ROM_PATH)                           \
  TEST(TEST_SUITE_NAME, TEST_NAME)                                                  \
  {                                                                                 \
    DummyBus bus;                                                                   \
    Cpu cpu(bus);                                                                   \
    cpu.ResetState();                                                               \
    Timer timer(bus);                                                               \
    const auto *rom_path = "data/cpu_instrs/individual/" ROM_PATH ".gb";            \
    std::ifstream rom{ rom_path, std::ios::binary };                                \
    if (!rom.is_open())                                                             \
    {                                                                               \
      throw std::invalid_argument(std::format("Unable to find rom: {}", rom_path)); \
    }                                                                               \
    uint16_t address{ 0 };                                                          \
    uint8_t byte{};                                                                 \
    while (rom.read(reinterpret_cast<char *>(&byte), 1))                            \
    {                                                                               \
      bus.Write(address, byte);                                                     \
      ++address;                                                                    \
    }                                                                               \
    rom.close();                                                                    \
                                                                                    \
    while (!bus.IsTestCompleted())                                                  \
    {                                                                               \
      auto cycles = cpu.Tick();                                                     \
      timer.Tick(cycles);                                                           \
    }                                                                               \
                                                                                    \
    EXPECT_EQ(true, bus.IsTestPassed()) << bus.GetMessage();                        \
  }
