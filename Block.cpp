#include "Block.h"


#include <iostream>

Block::Block(int x, int y, sf::Color colour) : mColour(colour)
{
  mSize = 75;
  mBorder = 1;

  offset.x = x;
  offset.y = y;

  shape = sf::RectangleShape(sf::Vector2f(mSize, mSize));
  shape.setFillColor(colour);
  shape.setOutlineThickness(mBorder);
  shape.setOutlineColor(sf::Color(255,255,255));

  setScreenPosition(sf::Vector2f(800, 400));
  //setScreenPosition(sf::Vector2f(800,400));
  //shape.setPosition(shape.getPosition().x + x * mSize, shape.getPosition().y + y * mSize);
}

bool Block::operator==(const Block& other)
{
  return offset.x == other.getOffset().x && offset.y == other.getOffset().y;
}

void Block::move(double x, double y)
{
  mRow += y;
  mCol += x;
  shape.move(x * mSize, y * mSize);
}

void Block::setScreenPosition(sf::Vector2f position)
{
  shape.setPosition(position.x, position.y);
  shape.setPosition(shape.getPosition().x + offset.x * mSize, shape.getPosition().y + offset.y * mSize);
}

int Block::getSize() const
{
  return mSize;
}

void Block::moveOffset(double x, double y)
{
  offset.x += x;
  offset.y += y;
  move(x, y);
}

void Block::setOffset(double x, double y)
{
  std::cout << "X: " << x << "\n";
  double xDelta = x - offset.x;
  double yDelta = y - offset.y;
  move(xDelta, yDelta);
  //auto newXPos = shape.getPosition().x + xDelta * mSize;
  //auto newYPos = shape.getPosition().y + yDelta * mSize;
  //shape.setPosition(newXPos, newYPos);

  /*
  std::cout << "\nDELTA x: " << xDelta << "y: " << yDelta << "\n";
  std::cout << "NEW x: " << x << " y: " << y << "\n";
  std::cout << "OLD x: " << offset.x << " y: " << offset.y << "\n";
  */

  offset.x = x;
  offset.y = y;
}

int Block::getBorder() const
{
  return mBorder;
}

sf::Vector2f Block::getPosition() const
{
  return sf::Vector2f(mCol, mRow);
}

void Block::draw(sf::RenderWindow& window)
{
  window.draw(shape);
}

sf::Vector2f Block::getOffset() const
{
  return offset;
}

sf::RectangleShape& Block::getShape()
{
  return shape;
}
