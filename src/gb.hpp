#pragma once

#include "bus.hpp"
#include "cpu.hpp"
#include "timer.hpp"
#include <memory>
class GameBoy
{
  public:
    explicit GameBoy(const std::string &rom_path);
    void Run();

  private:
    std::unique_ptr<Bus> m_bus;
    Cpu m_cpu;
    Timer m_timer;
};
