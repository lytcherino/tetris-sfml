#ifndef PIECE_H
#define PIECE_H

#include "Block.h"
#include <vector>
#include <memory>
#include <cmath>

enum class Type {I, O, T, S, Z, J, L};
enum class Direction{CLOCKWISE, ANTICLOCKWISE};

struct Colour
{
  sf::Color I = sf::Color(100, 100, 100);
  sf::Color O = sf::Color(255, 0, 0);
  sf::Color T = sf::Color(0, 255, 0);
  sf::Color S = sf::Color(0, 0, 255);
  sf::Color J = sf::Color(100, 100, 0);
  sf::Color L = sf::Color(0, 100, 100);
  sf::Color Z = sf::Color(155, 34, 72);

  sf::Color pivot = sf::Color(255,0, 100);
  sf::Color clear = sf::Color(0, 34, 72);

};
 
class Piece
{
public:
  Piece(Type t, sf::Vector2i position);
  Piece(const Piece& piece);

  void moveDown();
  void moveDown(Block& block);
  void moveRight();
  void moveLeft();
  void moveUp();

  void draw(sf::RenderWindow& window);

  void rotate(Direction dir);

  void previewPosition();
  void resetPreviewPosition();
  void removeBlock(Block& block);
  void changeColour(sf::Color colour);

  void playPosition();
  void holdPosition();

  sf::Vector2i getWidthFromPivot();
  sf::Vector2i getHeightFromPivot();
  sf::Vector2i getBlockPositionBoard(Block& block);
  bool otherAt(sf::Vector2i position, Block& block);

  sf::Vector2i getBoardPosition() const;
  std::vector<Block>&  getBlocks();

  Colour colour;
  bool getActive();
  bool setActive(bool state);


  Type getType() const;

private:
  std::vector<Block> mBlocks;
  sf::Vector2i boardPosition;
  sf::Vector2f currentBoardPosition;
  sf::Vector2f globalHoldPosition;

  bool active;
  Type type;
};


#endif
