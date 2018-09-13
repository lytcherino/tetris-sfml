#include "Cell.h"

bool Cell::isEmpty() const
{
  return occupied;
}

void Cell::occupy()
{
  occupied = true;
}

void Cell::release()
{
  occupied = false;
}
