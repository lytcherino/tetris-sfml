#include "PieceFactory.h"

namespace PieceFactory
{

  std::vector<std::unique_ptr<Piece>> generatePieces(sf::Vector2i startPosition)
  {
    std::vector<std::unique_ptr<Piece>> pieceList;
    pieceList.push_back(std::make_unique<Piece>(Type::I, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::I, startPosition));
   
    
    pieceList.push_back(std::make_unique<Piece>(Type::J, startPosition));
    
    pieceList.push_back(std::make_unique<Piece>(Type::J, startPosition));
    
    pieceList.push_back(std::make_unique<Piece>(Type::O, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::O, startPosition));
    
    pieceList.push_back(std::make_unique<Piece>(Type::L, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::L, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::Z, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::Z, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::T, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::T, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::S, startPosition));
    pieceList.push_back(std::make_unique<Piece>(Type::S, startPosition));
    
    std::random_shuffle(pieceList.begin(), pieceList.end());

    return pieceList;

  }
}
