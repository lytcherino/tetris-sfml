#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Cell.h"
#include "PieceFactory.h"

class Board
{
public:
  Board();


  void initialise();

  void draw(sf::RenderWindow& window);

  void moveDown();
  void moveLeft();
  void moveRight();
  void dropPiece();
  void rotatePiece();

  bool getGameOver();
  void createShadowPiece();
  void updateHoldPiece();
  void deactivatePiece();

  bool isValidMove();

private:
  std::vector<std::unique_ptr<Piece>> mPieces;
  std::vector<std::unique_ptr<Piece>> piecesToBePlayed;
  
  sf::Vector2i startingPosition;
  std::unique_ptr<Piece> activePiece;
  std::unique_ptr<Piece> previewPiece;
  std::unique_ptr<Piece> shadowPiece;
  std::unique_ptr<Piece> holdPiece;

  void dropShadowPiece();

  int mWIDTH;
  int mHEIGHT;

  int piecesCleared;
  int linesCleared;

  int getLinesCleared() const;
  int getPiecesCleared() const;

  bool gameEnded;

  void gameOver();
  void createPiece();
  bool withinBounds(std::unique_ptr<Piece>& piece);
  void moveBlocksDown(int row);


  void removePiecesWithNoBlocks();
  void restoreShadowPieceHeight();

  void adjustBoolValueInactivePieces(bool state, std::unique_ptr<Piece>& piece);
  void dropInactivePiece(std::unique_ptr<Piece>& piece);
  void dropInactivePieces();
  void completeLines();
  int occupied[10][16];

  void clearLine(int row);
  void printBoolMatrix();

  bool collision(std::unique_ptr<Piece>& piece);
};


#endif
