#include "simple_bus.hpp"
#include <cstdint>

uint8_t SimpleBus::Read(uint16_t addr)
{
  return m_memory[addr];
}

void SimpleBus::Write(uint16_t addr, uint8_t data)
{
  constexpr int DIV{ 0xFF04 };
  constexpr int DMA{ 0xFF46 };

  if (addr == DIV) // Explcitily writing to DIV register reset's it to zero
  {
    m_memory[DIV] = 0;
  }
  else if (addr == DMA)
  {
    int transferSourceAddress{ data << 8U };
    Dma(transferSourceAddress);
  }
  else
  {
    m_memory[addr] = data;
  }
}

uint8_t& SimpleBus::Address(uint16_t addr)
{
  return m_memory[addr];
}

void SimpleBus::Reset()
{
  m_memory.fill(0);
}

void SimpleBus::RequestInterrupt(uint8_t id)
{
  uint8_t& IF = Address(0xFF0F);
  IF |= (1U << id);
}

// TODO: Make DMA cycle accurate as some games depend on it

// Writing to register 0xFF46 starts OAM DMA transfer
// DMA takes a total of 160 Mcycles or 640 Tcycles
// During the OAM DMA the CPU can only access HRAM and
// the PPU cannot read OAM properly either
//
// The current implementation of OAM DMA is not cycle
// accurate and instead performs the DMA instantaneously
// The reason this works is becuase during DMA the CPU
// cannot access ROM or RAM neither can the PPU access the
// OAM properly, therefore most games perform DMA during
// HBlank or VBlank during which PPU is idle and also they
// jump the CPU to HRAM and exexute a routine which just waits
// for DMA to finish before executing the next instruction,
// i.e during DMA the CPU and PPU are doing nothing
void SimpleBus::Dma(uint16_t src)
{
  constexpr int dest{ 0xFE00 };
  constexpr int bytesToCopy{ 0xA0 }; // 160 bytes

  for (int i{0}; i < bytesToCopy; ++i)
  {
    m_memory[dest + i] = m_memory[src + i];
  }
}
