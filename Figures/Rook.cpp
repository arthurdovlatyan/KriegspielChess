

#include "Rook.h"


BoardGame::Rook::Rook(Color colour) :Figure(colour) {
    Figure::color = colour;
    if (color == Color::White) {
        symbol = "♖";
    } else {
        symbol = "♜";
    }
}

std::vector<std::tuple<char, char>> BoardGame::Rook::getMoveList(Figure* squares[8][8], char x, char y) {
    Figure::moveList.clear();
    int i = 1;
    while ((x - i >= 0) && (squares[x - i][y] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y));
        i++;
    }
    if ((x - i >= 0) && (squares[x - i][y]->getColor() != Rook::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y));
    }
    i = 1;
    while ((x + i <= 7) && (squares[x + i][y] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y));
        i++;
    }
    if ((x + i <= 7) && (squares[x + i][y]->getColor() != Rook::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y));
    }
    i = 1;
    while ((y - i >= 0) && (squares[x][y - i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y - i));
        i++;
    }
    if ((y - i >= 0) && (squares[x][y - i]->getColor() != Rook::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y - i));
    }
    i = 1;
    while ((y + i <= 7) && (squares[x][y + i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y + i));
        i++;
    }
    if ((y + i <= 7) && (squares[x][y + i]->getColor() != Rook::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y + i));
    }
    return Figure::moveList;
}

std::vector<std::tuple<char, char>> BoardGame::Rook::getCaptureMoveList(Figure* squares[8][8], char x, char y) {
    Figure::captureMoveList.clear();
    int i = 1;
    while ((x - i >= 0) && (squares[x - i][y] == nullptr)) {
        i++;
    }
    if ((x - i >= 0) && (squares[x - i][y]->getColor() != Rook::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x - i, y));
    }
    i = 1;
    while ((x + i <= 7) && (squares[x + i][y] == nullptr)) {
        i++;
    }
    if ((x + i <= 7) && (squares[x + i][y]->getColor() != Rook::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x + i, y));
    }
    i = 1;
    while ((y - i >= 0) && (squares[x][y - i] == nullptr)) {
        i++;
    }
    if ((y - i >= 0) && (squares[x][y - i]->getColor()!= Rook::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x, y - i));
    }
    i = 1;
    while ((y + i <= 7) && (squares[x][y + i] == nullptr)) {
        i++;
    }
    if ((y + i <= 7) && (squares[x][y + i]->getColor() != Rook::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x, y + i));
    }
    return Figure::captureMoveList;
}

std::string BoardGame::Rook::getSymbol() {
    return Rook::symbol;
}

int BoardGame::Rook::getValue() {
    if (Rook::color == Color::White) {
        return Rook::value;
    }
    else {
        return -Rook::value;
    }
}

BoardGame::PieceType BoardGame::Rook::getPieceType() {
    return Rook::pieceType;
}

int BoardGame::Rook::getPositionScore(char x, char y) {
    if (Rook::color == Color::White) {
        return Rook::scoreBoard[7 - y][x];
    }
    else {
        return -Rook::scoreBoard[y][x];
    }
}