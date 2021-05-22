

#include "Figure.h"

BoardGame::Figure::Figure(BoardGame::Color color) {
    Figure::color = color;
    Figure::moveCount = 0;
}

std::vector<std::tuple<char, char>> BoardGame::Figure::getMoveList(BoardGame::Figure *(*squares)[8], char x, char y) {
    Figure::moveList.clear();
    return Figure::moveList;
}

std::vector<std::tuple<char, char>>
BoardGame::Figure::getCaptureMoveList(BoardGame::Figure *(*squares)[8], char x, char y) {
    Figure::captureMoveList.clear();
    return Figure::captureMoveList;
}

std::string BoardGame::Figure::getSymbol() {
    return symbol;
}

int BoardGame::Figure::getValue() {
    return value;
}

BoardGame::PieceType BoardGame::Figure::getPieceType() {
    return Figure::pieceType;
}

int BoardGame::Figure::getPositionScore(char x, char y) {
    return 0;
}

BoardGame::Color BoardGame::Figure::getColor() {
    return Figure::color;
}

void BoardGame::Figure::setMoveCount(int n) {
    moveCount = n;
}

int BoardGame::Figure::getMoveCount() {
    return moveCount;
}












