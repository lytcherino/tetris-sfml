#include "GameEngine.h"

namespace GameEngine
{
  Board board;

  void initialise()
  {
    Display::initialise();
    board.initialise();
  }

  void start()
  {
    initialise();
    run();
  }

  void draw()
  {
    board.draw(Display::window);
  }

  void render()
  {
    Display::clear();
    draw();
    Display::update();
  }

  void run()
  {
    sf::Clock clock;

    while (Display::window.isOpen()) {

      sf::Event event;

      while (Display::window.pollEvent(event)) {
        // handle events
        if (event.type == sf::Event::Closed) { Display::window.close(); }
        if (event.type == sf::Event::Resized) {
          sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
          Display::window.setView(sf::View(visibleArea));
        }
        GameLogic::Keyboard::update(event, board);
      }
      // Game logic
      GameLogic::Timers::update(clock, board);
      render();
    }
  }

}
