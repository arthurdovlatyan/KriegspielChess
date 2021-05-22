

#include "Queen.h"

BoardGame::Queen::Queen(Color colour) :Figure(colour) {
    Figure::color = colour;
    if (color == Color::Black) {
       symbol = "♛";
    } else {
        symbol = "♕";
    }
}

std::vector<std::tuple<char, char>> BoardGame::Queen::getMoveList(Figure* squares[8][8], char x, char y) {
    Figure::moveList.clear();
    int i = 1;
    while ((x - i >= 0) && (squares[x - i][y] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y));
        i++;
    }
    if ((x - i >= 0) && (squares[x - i][y]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y));
    }
    i = 1;
    while ((x + i <= 7) && (squares[x + i][y] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y));
        i++;
    }
    if ((x + i <= 7) && (squares[x + i][y]->getColor()!= Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y));
    }
    i = 1;
    while ((y - i >= 0) && (squares[x][y - i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y - i));
        i++;
    }
    if ((y - i >= 0) && (squares[x][y - i]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y - i));
        i++;
    }
    i = 1;
    while ((y + i <= 7) && (squares[x][y + i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y + i));
        i++;
    }
    if ((y + i <= 7) && (squares[x][y + i]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x, y + i));
        i++;
    }
    i = 1;
    while ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y + i));
        i++;
    }
    if ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y + i));
    }
    i = 1;
    while ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y + i));
        i++;
    }
    if ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y + i));
    }
    i = 1;
    while ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y - i));
        i++;
    }
    if ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x - i, y - i));
        i++;
    }
    i = 1;
    while ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i] == nullptr)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y - i));
        i++;
    }
    if ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i]->getColor() != Queen::color)) {
        Figure::moveList.push_back(std::tuple<char, char>(x + i, y - i));
        i++;
    }
    return Figure::moveList;
}

std::vector<std::tuple<char, char>> BoardGame::Queen::getCaptureMoveList(Figure* squares[8][8], char x, char y) {
    Figure::captureMoveList.clear();
    int i = 1;
    while ((x - i >= 0) && (squares[x - i][y] == nullptr)) {
        i++;
    }
    if ((x - i >= 0) && (squares[x - i][y]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x - i, y));
    }
    i = 1;
    while ((x + i <= 7) && (squares[x + i][y] == nullptr)) {
        i++;
    }
    if ((x + i <= 7) && (squares[x + i][y]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x + i, y));
    }
    i = 1;
    while ((y - i >= 0) && (squares[x][y - i] == nullptr)) {
        i++;
    }
    if ((y - i >= 0) && (squares[x][y - i]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x, y - i));
    }
    i = 1;
    while ((y + i <= 7) && (squares[x][y + i] == nullptr)) {
        i++;
    }
    if ((y + i <= 7) && (squares[x][y + i]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x, y + i));
    }
    i = 1;
    while ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i] == nullptr)) {
        i++;
    }
    if ((x - i >= 0) && (y + i <= 7) && (squares[x - i][y + i]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x - i, y + i));
    }
    i = 1;
    while ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i] == nullptr)) {
        i++;
    }
    if ((x + i <= 7) && (y + i <= 7) && (squares[x + i][y + i]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x + i, y + i));
    }
    i = 1;
    while ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i] == nullptr)) {
        i++;
    }
    if ((x - i >= 0) && (y - i >= 0) && (squares[x - i][y - i]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x - i, y - i));
    }
    i = 1;
    while ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i] == nullptr)) {
        i++;
    }
    if ((x + i <= 7) && (y - i >= 0) && (squares[x + i][y - i]->getColor() != Queen::color)) {
        Figure::captureMoveList.push_back(std::tuple<char, char>(x + i, y - i));
    }
    return Figure::captureMoveList;
}

std::string BoardGame::Queen::getSymbol() {
    return Queen::symbol;
}

int BoardGame::Queen::getValue() {
    if (Queen::color == Color::White) {
        return Queen::value;
    }
    else {
        return -Queen::value;
    }
}

BoardGame::PieceType BoardGame::Queen::getPieceType() {
    return Queen::pieceType;
}

int BoardGame::Queen::getPositionScore(char x, char y) {
    if (Queen::color == Color::White) {
        return Queen::scoreBoard[7 - y][x];
    }
    else {
        return -Queen::scoreBoard[y][x];
    }
}
