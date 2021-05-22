
#include "Bishop.h"

BoardGame::Bishop::Bishop(Color colour) :Figure(color) {
    Figure::color = colour;
    if (color == Color::Black) {
        symbol = "♝";
    } else {
        symbol = "♗";
    }
}

std::vector<std::tuple<char, char>> BoardGame::Bishop::getMoveList(Figure* squares[8][8], char x, char y) {
    Figure::moveList.clear();
    int i = 1;
    while ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y + i));
        i++;
    }
    if ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i]->getColor() != Bishop::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y + i));
    }
    i = 1;
    while ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y + i));
        i++;
    }
    if ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i]->getColor() != Bishop::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y + i));
    }
    i = 1;
    while ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y - i));
        i++;
    }
    if ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i]->getColor() != Bishop::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y - i));
    }
    i = 1;
    while ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y - i));
        i++;
    }
    if ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i]->getColor() != Bishop::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y - i));
    }
    return Figure::moveList;
}

std::vector<std::tuple<char, char>> BoardGame::Bishop::getCaptureMoveList(Figure* squares[8][8], char x, char y) {
    Figure::captureMoveList.clear();
    int i = 1;
    while ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i] == nullptr)) {
        i++;
    }
    if ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i]->getColor() != Bishop::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x - i, y + i));
    }
    i = 1;
    while ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i] == nullptr)) {
        i++;
    }
    if ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i]->getColor() != Bishop::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x + i, y + i));
    }
    i = 1;
    while ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i] == nullptr)) {
        i++;
    }
    if ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i]->getColor() != Bishop::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x - i, y - i));
    }
    i = 1;
    while ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i] == nullptr)) {
        i++;
    }
    if ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i]->getColor() != Bishop::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x + i, y - i));
    }
    return Figure::captureMoveList;
}

std::string BoardGame::Bishop::getSymbol() {
    return Bishop::symbol;
}

int BoardGame::Bishop::getValue() {
    if (Bishop::color == Color::White) {
        return Bishop::value;
    }
    else {
        return -Bishop::value;
    }
}

BoardGame::PieceType BoardGame::Bishop::getPieceType() {
    return Bishop::pieceType;
}

int BoardGame::Bishop::getPositionScore(char x, char y) {
    if (Bishop::color == Color::White) {
        return Bishop::scoreBoard[7 - y][x];
    }
    else {
        return -Bishop::scoreBoard[y][x];
    }
}