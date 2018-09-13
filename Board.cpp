#include "Board.h"
#include <iostream>

Board::Board() : startingPosition(sf::Vector2i(5, 14)),
                 mWIDTH(10), mHEIGHT(16)
{
  piecesToBePlayed = PieceFactory::generatePieces(startingPosition);
}

void Board::initialise()
{
  createPiece();
}

void Board::createPiece()
{
  if (shadowPiece) { shadowPiece = nullptr; }

  if (piecesToBePlayed.size() == 0) {
    piecesToBePlayed = PieceFactory::generatePieces(startingPosition);
  }

  if(piecesToBePlayed.size() > 0) {

    if (previewPiece != nullptr) {
      previewPiece->resetPreviewPosition();
      piecesToBePlayed[0] = std::move(previewPiece);
    }

    activePiece = std::move(piecesToBePlayed[0]);

    piecesToBePlayed.erase(piecesToBePlayed.begin());

    if (piecesToBePlayed.size() == 0) {
      piecesToBePlayed = PieceFactory::generatePieces(startingPosition);
    }

    previewPiece = std::move(piecesToBePlayed[0]);
    previewPiece->previewPosition();
  }

  if (collision(activePiece)) { gameOver(); }

  createShadowPiece();

  printBoolMatrix();
}

void Board::updateHoldPiece()
{
  if (!holdPiece) {
    holdPiece = std::move(activePiece);
    holdPiece->holdPosition();
    createPiece();
  }
  else {
    activePiece.swap(holdPiece);
    activePiece->playPosition();
    holdPiece->holdPosition();
  }
}

void Board::createShadowPiece()
{
  if (!activePiece) { return; }
  if (shadowPiece) { shadowPiece = nullptr; }
  shadowPiece = std::unique_ptr<Piece>(new Piece(*activePiece));
  //std::cout << "Shadow: " << shadowPiece->getHeightFromPivot().x << " " << shadowPiece->getHeightFromPivot().y << "\n";
  //std::cout << "Shadow2: " << shadowPiece->getBoardPosition().x << " " << shadowPiece->getBoardPosition().y << "\n";
  //std::cout << "Shadow3: " << shadowPiece->getBlocks().size() << "\n";
  shadowPiece->changeColour(sf::Color(30,30,30, 155));
  dropShadowPiece();
}

bool Board::withinBounds(std::unique_ptr<Piece>& activePiece)
{
  auto x = activePiece->getBoardPosition().x;
  auto y = activePiece->getBoardPosition().y;

  sf::Vector2i y_offset = activePiece->getHeightFromPivot();
  sf::Vector2i x_offset = activePiece->getWidthFromPivot();

  if (y >= y_offset.y && x >= -1 * x_offset.x  && x < mWIDTH - x_offset.y) {
    // std::cout << y << " " << y_offset.y << " | x: " << x << " " << -1*x_offset.x << " " << mWIDTH-x_offset.y << "\n";
    return true;
  }
  return false;
}

void Board::gameOver()
{
  gameEnded = true;
}

bool Board::collision(std::unique_ptr<Piece>& activePiece)
{
  auto& blocks = activePiece->getBlocks();
  auto boardPosition = activePiece->getBoardPosition();

  for(auto& block : blocks) {
    auto offset = block.getOffset();
    int x = boardPosition.x + offset.x;
    int y = boardPosition.y - offset.y;
    if (x >= 0 && y >= 0 && occupied[x][y] == true) {
      //std::cout << "COLL x: " << x << " y: " << y << std::endl;

      return true; }
  }
  return false;
}


void Board::clearLine(int row)
{
  for(auto& piece : mPieces) {
    auto& blockList = piece->getBlocks();
    auto blockIter = std::begin(blockList);
    while (blockIter != std::end(blockList)) {

      auto boardPosition = piece->getBoardPosition();
      auto offset = (*blockIter).getOffset();
      int x = boardPosition.x + offset.x;
      int y = boardPosition.y - offset.y;

      if (y == row) {
        occupied[x][y] = false;
        blockIter = blockList.erase(blockIter);
      }
      else { ++blockIter; }
    }
  }
  linesCleared++;

}

void Board::removePiecesWithNoBlocks()
{
  mPieces.erase(std::remove_if
                (mPieces.begin(), mPieces.end(), [](std::unique_ptr<Piece>& p)
                 -> bool
                 {
                   return p->getBlocks().size() == 0;
                 }
                 ),
                mPieces.end()
                );
  piecesCleared++;
}

void Board::deactivatePiece()
{
  auto& blocks = activePiece->getBlocks();
  auto boardPosition = activePiece->getBoardPosition();

  for(auto& block : blocks) {
    auto offset = block.getOffset();
    int x = boardPosition.x + offset.x;
    int y = boardPosition.y - offset.y;

    // update bool matrix
    occupied[x][y] = true;

    if (y >= startingPosition.y) { gameOver(); }

    //std::cout << "x: " << x << " y: " << y << std::endl;
  }
  activePiece->setActive(false);

  mPieces.push_back(std::move(activePiece));

  // Check for any complete rows
  completeLines();

  //printBoolMatrix();
  createPiece();
}

void Board::completeLines()
{
  for (int i = mHEIGHT - 1; i >= 0; i--) {
    int sum = 0;
    for (int j = 0; j < mWIDTH; j++) {
      if (occupied[j][i] == true) { sum++; }
    }
    if (sum == mWIDTH) {
      std::cout << "clear line " << i << "\n";
      clearLine(i);
      removePiecesWithNoBlocks();
      moveBlocksDown(i);
    }
  }
}

void Board::moveBlocksDown(int row)
{
  for (auto& piece : mPieces) {
    auto& blocks = piece->getBlocks();
    for (auto& block : blocks) {
      auto blockPosition = piece->getBlockPositionBoard(block);
      if (blockPosition.y >= row) {

        /*
        if (!piece->otherAt(blockPosition, block)) {
          occupied[blockPosition.x][blockPosition.y] = false;
        }
        */
        occupied[blockPosition.x][blockPosition.y]--;

        //std::cout << "be x: " << blockPosition.x << " y: " << blockPosition.y << std::endl;
        piece->moveDown(block);
        blockPosition = piece->getBlockPositionBoard(block);
        //std::cout << "af x: " << blockPosition.x << " y: " << blockPosition.y << std::endl;
        occupied[blockPosition.x][blockPosition.y]++;
        printBoolMatrix();
      }
    }
  }
}

void Board::draw(sf::RenderWindow& window)
{
  for (auto& piece : mPieces) {
    piece->draw(window);
  }
  activePiece->draw(window);
  previewPiece->draw(window);

  //std::cout << shadowPiece->getBoardPosition().y << "\n";
  if (shadowPiece) { shadowPiece->draw(window); }
  if (holdPiece) { holdPiece->draw(window); }

}

void Board::moveDown()
{
  // if legal for piece to move, move it down 1 step
  activePiece->moveDown();
  if (collision(activePiece) || !withinBounds(activePiece)) {
    activePiece->moveUp();
    deactivatePiece();
  }
}

void Board::moveLeft()
{
  // if legal
  activePiece->moveLeft();
  //shadowPiece->moveLeft();
  if (collision(activePiece) || !withinBounds(activePiece)) {
    //shadowPiece->moveRight();
    activePiece->moveRight();
  }
}

void Board::moveRight()
{
  // if legal
  activePiece->moveRight();
  //  shadowPiece->moveRight();
  if (collision(activePiece) || !withinBounds(activePiece)) {

    //shadowPiece->moveLeft();
    activePiece->moveLeft();
  }
}

void Board::dropShadowPiece()
{
  do {
    shadowPiece->moveDown();
  } while (!collision(shadowPiece) && withinBounds(shadowPiece));
  shadowPiece->moveUp();
}

void Board::restoreShadowPieceHeight()
{

  int shadowY = shadowPiece->getBoardPosition().y;
  int activeY = activePiece->getBoardPosition().y;
  while(shadowY < activeY) {

    shadowPiece->moveUp();

    shadowY = shadowPiece->getBoardPosition().y;
    activeY = activePiece->getBoardPosition().y;
  }
}

void Board::dropPiece()
{
  do {
    activePiece->moveDown();
  } while (!collision(activePiece) && withinBounds(activePiece));
  activePiece->moveUp();
  // deactive piece immediately
}

void Board::rotatePiece()
{
  activePiece->rotate(Direction::CLOCKWISE);
  if (collision(activePiece) || !withinBounds(activePiece)) {
    activePiece->rotate(Direction::ANTICLOCKWISE);
  }
}

bool Board::isValidMove()
{
  return true;
}

void Board::printBoolMatrix()
{
  std::cout << "\n\n";
  for(int i = mHEIGHT - 1; i >= 0; i--){
    for(int j = 0; j < mWIDTH; j++) {
      std::cout << occupied[j][i] << " ";
    }
    std::cout << "\n";
  }
}

bool Board::getGameOver()
{
  return gameEnded;
}

int Board::getLinesCleared() const
{
  return linesCleared;
}

int Board::getPiecesCleared() const
{
  return piecesCleared;
}
