#include "GameLogic.h"
#include <iostream>

namespace GameLogic
{
  gameState currentGameState = gameState::playing;

  namespace Settings
  {
    bool deactivePieceAfterDrop = true;
  }

  namespace Timers
  {
    double downMovementTimer = 1.0;
    double playerMovementTimer = 0.25;

    void update(sf::Clock& clock, Board& board)
    {

      if (board.getGameOver()) {
        currentGameState == gameState::gameOver;
      }

      if (currentGameState != gameState::playing) { return; }
      sf::Time time = clock.getElapsedTime();
      if (time.asSeconds() >= downMovementTimer) {
        //board.createShadowPiece();
        board.moveDown();
        clock.restart();

      }
    }

  }

  namespace Keyboard
  {

    void update(sf::Event e, Board& board)
    {

      if (currentGameState == gameState::gameOver) { return; }

      if(e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Left) {
          if (currentGameState == gameState::playing) {
            board.moveLeft();
          }
        }
        else if (e.key.code == sf::Keyboard::Right) {
          if (currentGameState == gameState::playing) {
            board.moveRight();
          }
        }
        else if (e.key.code == sf::Keyboard::Down) {
          if (currentGameState == gameState::playing) {
            board.moveDown();
          }
        }
        else if (e.key.code == sf::Keyboard::Space) {
          if (currentGameState == gameState::playing) {
            board.dropPiece();
            if (GameLogic::Settings::deactivePieceAfterDrop) { board.deactivatePiece(); }
          }
        }
        else if (e.key.code == sf::Keyboard::RShift) {
          if (currentGameState == gameState::playing) { currentGameState = gameState::paused;}
          else { currentGameState = gameState::playing; }
        }
        else if (e.key.code == sf::Keyboard::Return) {
          if (currentGameState == gameState::playing) {
            board.updateHoldPiece();
          }
        }
        else if (e.key.code == sf::Keyboard::Up) {
          if (currentGameState == gameState::playing) {
            board.rotatePiece();
          }
        }
        board.createShadowPiece();
      }
    }
  }
}
