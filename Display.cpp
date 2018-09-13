#include "Display.h"

namespace Display
{
  sf::RenderWindow window;
  unsigned int frameRateLimit = 60;
  std::string gameName = "Tetris";

  void initialise()
  {
    window.create( sf::VideoMode(WIDTH, HEIGHT), gameName/*, sf::Style::Fullscreen*/);
    window.setFramerateLimit(frameRateLimit);
    window.setKeyRepeatEnabled(false);

  }

  void close()
  {
    window.close();
  }

  void clear()
  {
    window.clear();
  }

  void update()
  {
    window.display();
  }
}
