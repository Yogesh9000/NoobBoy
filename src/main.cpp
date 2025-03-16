#include "gb.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "USAGE: gb <rom>\n";
    return -1;
  }
  GameBoy gb(argv[1]);
  gb.Run();
  return 0;
}
