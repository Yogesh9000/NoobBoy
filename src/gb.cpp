#include "gb.hpp"
#include "simple_bus.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <fstream>
#include <format>
#include <stdexcept>
#include <SDL3/SDL_events.h>

GameBoy::GameBoy(const std::string &rom_path)
  : m_bus(std::make_unique<SimpleBus>()), m_cpu{ *m_bus }, m_timer(*m_bus), m_ppu("NoobBoy")
{
  std::ifstream rom(rom_path, std::ios::binary);
  if (!rom.is_open())
  {
    throw std::invalid_argument(std::format("Unable to find rom: {}", rom_path));
  }
  uint16_t address{0};
  uint8_t byte{};
  while (rom.read(reinterpret_cast<char*>(&byte), 1))
  {
    m_bus->Write(address, byte);
    ++address;
  }
  rom.close();
}

void GameBoy::Run()
{
  constexpr int MAX_CYCLES_BEFORE_RENDER{ 69905 };
  uint64_t elapsedCpuCycles{0};
  m_cpu.ResetState(); // Set's Cpu to state just after boot rom is finished running

  SDL_Event event;
  bool quit{ false };
  while(!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        quit = true;
      }
    }

    while(elapsedCpuCycles < MAX_CYCLES_BEFORE_RENDER)
    {
      int cycles = m_cpu.Tick();
      m_timer.Tick(cycles); // Synchronize Timer with CPU
      m_ppu.Tick(cycles);

      elapsedCpuCycles += cycles;
    }

    m_ppu.UpdateFrame();

    elapsedCpuCycles = 0; // Reset to zero
  }
}
