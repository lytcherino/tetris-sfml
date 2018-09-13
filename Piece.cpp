#include "Piece.h"
#include <iostream>


Piece::Piece(Type t, sf::Vector2i position)
{
  boardPosition = position;
  active = true;
  type = t;
  globalHoldPosition = sf::Vector2f(200,400);

  if (t == Type::I) {
    mBlocks.push_back(Block(0,1, colour.I));
    mBlocks.push_back(Block(0,0, colour.pivot));
    mBlocks.push_back(Block(0,-1, colour.I));
    mBlocks.push_back(Block(0,-2, colour.I));
  }
  else if (t == Type::O) {
    mBlocks.push_back(Block(0,0, colour.pivot));
    mBlocks.push_back(Block(0,1, colour.O));
    mBlocks.push_back(Block(1,0, colour.O));
    mBlocks.push_back(Block(1,1, colour.O));
  }
  else if (t == Type::T) {
    mBlocks.push_back(Block(0,0, colour.pivot));
    mBlocks.push_back(Block(0,-1, colour.T));
    mBlocks.push_back(Block(-1,0, colour.T));
    mBlocks.push_back(Block(1,0, colour.T));
  }
  else if (t == Type::Z) {
    mBlocks.push_back(Block(0,0, colour.pivot));
    mBlocks.push_back(Block(1,0, colour.Z));
    mBlocks.push_back(Block(0,-1, colour.Z));
    mBlocks.push_back(Block(-1,-1, colour.Z));
  }
  else if (t == Type::J) {
    mBlocks.push_back(Block(0,1, colour.J));
    mBlocks.push_back(Block(0,0, colour.J));
    mBlocks.push_back(Block(0,-1, colour.J));
    mBlocks.push_back(Block(-1,-1, colour.pivot));
  }
  else if (t == Type::L) {
    mBlocks.push_back(Block(1,-1, colour.L));
    mBlocks.push_back(Block(0,1, colour.L));
    mBlocks.push_back(Block(0,0, colour.pivot));
    mBlocks.push_back(Block(0,-1, colour.L));
  }
  else if (t == Type::S) {
    mBlocks.push_back(Block(1,-1, colour.S));
    mBlocks.push_back(Block(0,-1, colour.S));
    mBlocks.push_back(Block(0,0, colour.pivot));
    mBlocks.push_back(Block(-1,0, colour.S));
  }
}

Piece::Piece(const Piece& piece)
{
  boardPosition = piece.boardPosition;
  type = piece.type;
  mBlocks = piece.mBlocks;
  active = piece.active;
}

void Piece::moveDown()
{
  for (auto& block : mBlocks) {
    block.move(0, 1);
  }
  boardPosition.y--;
}

Type Piece::getType() const
{
  return type;
}

void Piece::holdPosition()
{
  for (auto& block : mBlocks) {
    auto offset = block.getOffset();
    if (offset.x == 0 && offset.y == 0) {
      currentBoardPosition = block.getShape().getPosition();
    }
    block.setScreenPosition(globalHoldPosition);
  }
}

void Piece::playPosition()
{
  for (auto& block : mBlocks) {
    block.setScreenPosition(currentBoardPosition);
  }
}

sf::Vector2i Piece::getBlockPositionBoard(Block& block)
{
  auto offset = block.getOffset();
  auto x = boardPosition.x + offset.x;
  auto y = boardPosition.y - offset.y;

  return sf::Vector2i(x, y);
}

void Piece::moveDown(Block& block)
{
  //block.move(0, 1);
  block.moveOffset(0, 1);
}

bool Piece::otherAt(sf::Vector2i position, Block& block)
{
  for (auto& other : mBlocks){
    if (block == other) { continue; }
    if (getBlockPositionBoard(other) == position) {
      // std::cout << &block << " " << position.x << " " << position.y << " " << &other <<
      //  " " << getBlockPositionBoard(other).x << " " <<  getBlockPositionBoard(other).y << std::endl;
      return true;
    }


  }
  return false;
}

void Piece::moveLeft()
{
  for (auto& block : mBlocks) {
    block.move(-1, 0);
  }
  boardPosition.x--;
}

void Piece::moveUp()
{
  for (auto& block : mBlocks) {
    block.move(0, -1);
  }
  boardPosition.y++;
}

void Piece::moveRight()
{
  for (auto& block : mBlocks) {
    block.move(1, 0);
  }
  boardPosition.x++;
}

void Piece::rotate(Direction dir)
{

  int angle;
  if (dir == Direction::ANTICLOCKWISE) { angle = -90; }
  if (dir == Direction::CLOCKWISE) { angle = 90; }

  std::cout << "rot: " << angle << "\n";

  // x'  cos -sin  x
  //   =         *
  // y'  sin cos   y

  // +ve angle, anticlockwise for right-handed coordinate system

  for (auto& block : mBlocks) {
    auto offset = block.getOffset();
    double x = offset.x * cos(M_PI * (angle) / 180.0) -
      sin(M_PI * (angle) / 180) * offset.y;
    double y = offset.x * sin(M_PI * (angle) / 180.0) +
      cos(M_PI * (angle) / 180) * offset.y;

    block.setOffset(x, y);
  }
}

void Piece::resetPreviewPosition()
{
  for(int i = 0; i < 10; i++) {moveLeft();}
}

void Piece::previewPosition()
{
  for(int i = 0; i < 10; i++) {moveRight();}
}

sf::Vector2i Piece::getBoardPosition() const
{
  return boardPosition;
}

void Piece::draw(sf::RenderWindow& window)
{
  for (auto& block : mBlocks) {
    block.draw(window);
  }
}

std::vector<Block>& Piece::getBlocks()
{
  return mBlocks;
}

void Piece::removeBlock(Block& block)
{
  auto it = mBlocks.begin();
  while (it != mBlocks.end()){
    if (*it == block) { it = mBlocks.erase(it); return; }
    else { it++;}
  }
}

sf::Vector2i Piece::getWidthFromPivot()
{
  int max = -10000;
  int min = 10000;

  for(auto& block : mBlocks) {
    if (block.getOffset().x > max) { max = block.getOffset().x; }
    if (block.getOffset().x < min) { min = block.getOffset().x; }
  }

  return sf::Vector2i(min, max);
}

sf::Vector2i Piece::getHeightFromPivot()
{
  int max = -10000;
  int min = 10000;

  for(auto& block : mBlocks) {
    if (block.getOffset().y > max) { max = block.getOffset().y; }
    if (block.getOffset().y < min) { min = block.getOffset().y; }
  }

  return sf::Vector2i(min, max);
}

void Piece::changeColour(sf::Color colour)
{
  for (auto& block : mBlocks) {
    block.getShape().setFillColor(colour);
  }
}

bool Piece::setActive(bool state)
{
  active = state;
}
bool Piece::getActive()
{
  return active;
}
