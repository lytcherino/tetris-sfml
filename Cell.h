#ifndef CELL_H
#define CELL_H

class Cell
{
public:
  bool isEmpty() const;

  void occupy();
  void release();

private:
  bool occupied;
};

#endif
