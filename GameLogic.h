#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/Graphics.hpp>
#include "Board.h"

enum class gameState {playing, paused, gameOver};

namespace GameLogic
{

  extern gameState currentGameState;
  namespace Timers
  {
    extern double downMovementTimer;
    extern double playerMovementTimer;

    void update(sf::Clock& clock, Board& board);
  }

  namespace Keyboard
  {
    void update(sf::Event e, Board& board);
  }

  namespace Settings
  {
    extern bool deactivePieceAfterDrop;
  }
}

#endif
