#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include <memory>
#include <vector>
#include "Piece.h"

namespace PieceFactory
{

  std::vector<std::unique_ptr<Piece>> generatePieces(sf::Vector2i startPosition);
}

#endif
