
#include "Knight.h"

BoardGame::Knight::Knight(BoardGame::Color colour) : Figure(colour) {
    Figure::color = colour;
    if (color == Color::Black) {
        symbol = "♞";
    } else {
        symbol = "♘";
    }
}


std::vector<std::tuple<char, char>> BoardGame::Knight::getMoveList(Figure* squares[8][8], char x, char y) {
    Figure::moveList.clear();
    if ((x - 1 >= 0) && (y + 2 <= 7)) {
        if ((squares[x - 1][y + 2] == nullptr) || squares[x - 1][y + 2]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 1, y + 2));
        }
    }
    if ((x - 1 >= 0) && (y - 2 >= 0)) {
        if ((squares[x - 1][y - 2] == nullptr) || squares[x - 1][y - 2]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 1, y - 2));
        }
    }
    if ((x + 1 <= 7) && (y + 2 <= 7)) {
        if ((squares[x + 1][y + 2] == nullptr) || squares[x + 1][y + 2]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 1, y + 2));
        }
    }
    if ((x + 1 <= 7) && (y - 2 >= 0)) {
        if ((squares[x + 1][y - 2] == nullptr) || squares[x + 1][y - 2]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 1, y - 2));
        }
    }
    if ((x - 2 >= 0) && (y + 1 <= 7)) {
        if ((squares[x - 2][y + 1] == nullptr) || squares[x - 2][y + 1]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 2, y + 1));
        }
    }
    if ((x - 2 >= 0) && (y - 1 >= 0)) {
        if ((squares[x - 2][y - 1] == nullptr) || squares[x - 2][y - 1]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 2, y - 1));
        }
    }
    if ((x + 2 <= 7) && (y + 1 <= 7)) {
        if ((squares[x + 2][y + 1] == nullptr) || squares[x + 2][y + 1]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 2, y + 1));
        }
    }
    if ((x + 2 <= 7) && (y - 1 >= 0)) {
        if ((squares[x + 2][y - 1] == nullptr) || squares[x + 2][y - 1]->getColor() != Knight::color) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 2, y - 1));
        }
    }
    return Figure::moveList;
}

std::vector<std::tuple<char, char>> BoardGame::Knight::getCaptureMoveList(Figure* squares[8][8], char x, char y) {
    Figure::captureMoveList.clear();
    if ((x - 1 >= 0) && (y + 2 <= 7)) {
        if ((squares[x - 1][y + 2] != nullptr) && squares[x - 1][y + 2]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y + 2));
        }
    }
    if ((x - 1 >= 0) && (y - 2 >= 0)) {
        if ((squares[x - 1][y - 2] != nullptr) && squares[x - 1][y - 2]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y - 2));
        }
    }
    if ((x + 1 <= 7) && (y + 2 <= 7)) {
        if ((squares[x + 1][y + 2] != nullptr) && squares[x + 1][y + 2]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y + 2));
        }
    }
    if ((x + 1 <= 7) && (y - 2 >= 0)) {
        if ((squares[x + 1][y - 2] != nullptr) && squares[x + 1][y - 2]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y - 2));
        }
    }
    if ((x - 2 >= 0) && (y + 1 <= 7)) {
        if ((squares[x - 2][y + 1] != nullptr) && squares[x - 2][y + 1]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 2, y + 1));
        }
    }
    if ((x - 2 >= 0) && (y - 1 >= 0)) {
        if ((squares[x - 2][y - 1] != nullptr) && squares[x - 2][y - 1]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 2, y - 1));
        }
    }
    if ((x + 2 <= 7) && (y + 1 <= 7)) {
        if ((squares[x + 2][y + 1] != nullptr) && squares[x + 2][y + 1]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 2, y + 1));
        }
    }
    if ((x + 2 <= 7) && (y - 1 >= 0)) {
        if ((squares[x + 2][y - 1] != nullptr) && squares[x + 2][y - 1]->getColor() != Knight::color) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 2, y - 1));
        }
    }
    return Figure::captureMoveList;
}

std::string BoardGame::Knight::getSymbol() {
    return Knight::symbol;
}

int BoardGame::Knight::getValue() {
    if (Knight::color == Color::White) {
        return Knight::value;
    }
    else {
        return -Knight::value;
    }
}

BoardGame::PieceType BoardGame::Knight::getPieceType() {
    return Knight::pieceType;
}

int BoardGame::Knight::getPositionScore(char x, char y) {
    if (Knight::color == Color::White) {
        return Knight::scoreBoard[7 - y][x];
    }
    else {
        return -Knight::scoreBoard[y][x];
    }
}
