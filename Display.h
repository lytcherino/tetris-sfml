#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>

namespace Display
{
  constexpr int WIDTH = 1920;
  constexpr int HEIGHT = 1080;

  void initialise();

  void clear();
  void update();
  void close();
}

#endif
