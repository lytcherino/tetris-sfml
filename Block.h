

class Block
{
public:
  Block(int x, int y);

private:
  int mRow;
  int mCol;
  int mSize;
  int mBorder;
  int mColour[3];
};

Block::Block(int x, int y)
{
  x = mCol;
  y = mRow;
  mSize = 10;
  mBorder = 2;
  mColour = {1, 0, 0};
}
