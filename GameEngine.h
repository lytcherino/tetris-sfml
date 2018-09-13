#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Display.h"
#include "Board.h"
#include "GameLogic.h"
#include "GameResource.h"

namespace GameEngine
{

  extern Board board;

  void initialise();

  void start();

  void draw();

  void render();

  void run();
}

#endif
