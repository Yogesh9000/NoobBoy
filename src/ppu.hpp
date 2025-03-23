#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <vector>

class PPU
{
public:
  constexpr static int LCD_WIDTH{ 160 };
  constexpr static int LCD_HEIGHT{ 144 };
  constexpr static int SCALE { 4 };
  constexpr static int PIXEL_SIZE{ 3 }; // since we are using SDL_PIXELFORMAT_RGB24 each pixel has size of 3bytes

  explicit PPU(const char *title);
  ~PPU();

  explicit PPU(const PPU &) = delete;
  explicit PPU(const PPU &&) = delete;
  PPU& operator=(const PPU &) = delete;
  PPU& operator=(const PPU &&) = delete;


  void UpdateFrame();
  void Tick(int cycles);

private:
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  SDL_Texture* m_texture;

  std::vector<int> m_pixels;
};
