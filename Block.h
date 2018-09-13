#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

class Block
{
public:
  Block(int x, int y, sf::Color colour);

  void move(double x, double y);

  int getSize() const;
  int getBorder() const;
  sf::Vector2f getPosition() const;
  void draw(sf::RenderWindow& window);

  sf::RectangleShape& getShape();

  bool operator==(const Block& other);

  sf::Vector2f getOffset() const;
  void moveOffset(double x, double y);
  void setOffset(double x, double y);
  void setScreenPosition(sf::Vector2f position);

private:
  sf::RectangleShape shape;

  sf::Vector2f offset;

  int mRow;
  int mCol;
  int mSize;
  int mBorder;
  sf::Color mColour;
};

#endif
