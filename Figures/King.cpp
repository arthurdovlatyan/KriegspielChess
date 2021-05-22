
#include "King.h"
BoardGame::King::King(Color colour) :Figure(colour) {
    Figure::color = colour;
    if (color == Color::Black) {
        symbol = "♚";
    } else {
        symbol = "♔";
    }
}

std::vector<std::tuple<char, char>> BoardGame::King::getMoveList(Figure* squares[8][8], char x, char y) {
    Figure::moveList.clear();
    if ((x - 1 >= 0) && (y + 1 <= 7)) {
        if ((squares[x - 1][y + 1] == nullptr) || (King::color != squares[x - 1][y + 1]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 1, y + 1));
        }
    }
    if ((x - 1 >= 0) && (y - 1 >= 0)) {
        if ((squares[x - 1][y - 1] == nullptr) || (King::color != squares[x - 1][y - 1]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 1, y - 1));
        }
    }
    if ((x + 1 <= 7) && (y + 1 <= 7)) {
        if ((squares[x + 1][y + 1] == nullptr) || (King::color != squares[x + 1][y + 1]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 1, y + 1));
        }
    }
    if ((x + 1 <= 7) && (y - 1 >= 0)) {
        if ((squares[x + 1][y - 1] == nullptr) || (King::color != squares[x + 1][y - 1]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 1, y - 1));
        }
    }
    if ((x + 1 <= 7)) {
        if ((squares[x + 1][y] == nullptr) || (King::color != squares[x + 1][y]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x + 1, y));
        }
    }
    if ((x - 1 >= 0)) {
        if ((squares[x - 1][y] == nullptr) || (King::color != squares[x - 1][y]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x - 1, y));
        }
    }
    if ((y + 1 <= 7)) {
        if ((squares[x][y + 1] == nullptr) || (King::color != squares[x][y + 1]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x, y + 1));
        }
    }
    if ((y - 1 >= 0)) {
        if ((squares[x][y - 1] == nullptr) || (King::color != squares[x][y - 1]->getColor())) {
            Figure::moveList.push_back(std::tuple<char, char>(x, y - 1));
        }
    }
    //White queenside castling
    if ((King::color == Color::White) && (x == 4) && (y == 0) && (squares[3][0] == nullptr) && (squares[2][0] == nullptr))
        Figure::moveList.push_back(std::tuple<char, char>(2, 0));
    //White kingside castling
    if ((King::color == Color::White) && (x == 4) && (y == 0) && (squares[6][0] == nullptr) && (squares[5][0] == nullptr))
        Figure::moveList.push_back(std::tuple<char, char>(6, 0));
    //Black queenside castling
    if ((King::color == Color::Black) && (x == 4) && (y == 7) && (squares[3][7] == nullptr) && (squares[2][7] == nullptr))
        Figure::moveList.push_back(std::tuple<char, char>(2, 7));
    //Black kingside castling
    if ((King::color == Color::Black) && (x == 4) && (y == 7) && (squares[6][7] == nullptr) && (squares[5][7] == nullptr))
        Figure::moveList.push_back(std::tuple<char, char>(6, 7));
    return Figure::moveList;
}

std::vector<std::tuple<char, char>> BoardGame::King::getCaptureMoveList(Figure* squares[8][8], char x, char y) {
    Figure::captureMoveList.clear();
    if ((x - 1 >= 0) && (y + 1 <= 7)) {
        if ((squares[x - 1][y + 1] != nullptr) && (King::color != squares[x - 1][y + 1]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y + 1));
        }
    }
    if ((x - 1 >= 0) && (y - 1 >= 0)) {
        if ((squares[x - 1][y - 1] != nullptr) && (King::color != squares[x - 1][y - 1]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y - 1));
        }
    }
    if ((x + 1 <= 7) && (y + 1 <= 7)) {
        if ((squares[x + 1][y + 1] != nullptr) && (King::color != squares[x + 1][y + 1]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y + 1));
        }
    }
    if ((x + 1 <= 7) && (y - 1 >= 0)) {
        if ((squares[x + 1][y - 1] != nullptr) && (King::color != squares[x + 1][y - 1]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y - 1));
        }
    }
    if ((x + 1 <= 7)) {
        if ((squares[x + 1][y] != nullptr) && (King::color != squares[x + 1][y]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y));
        }
    }
    if ((x - 1 >= 0)) {
        if ((squares[x - 1][y] != nullptr) && (King::color != squares[x - 1][y]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y));
        }
    }
    if ((y + 1 <= 7)) {
        if ((squares[x][y + 1] != nullptr) && (King::color != squares[x][y + 1]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x, y + 1));
        }
    }
    if ((y - 1 >= 0)) {
        if ((squares[x][y - 1] != nullptr) && (King::color != squares[x][y - 1]->getColor())) {
            Figure::captureMoveList.push_back(std::tuple<char, char>(x, y - 1));
        }
    }
    return Figure::captureMoveList;
}

std::string BoardGame::King::getSymbol() {
    return King::symbol;
}

int BoardGame::King::getValue() {
    if (King::color == Color::White) {
        return King::value;
    }
    else {
        return -King::value;
    }
}


BoardGame::PieceType BoardGame::King::getPieceType() {
    return King::pieceType;
}

int BoardGame::King::getPositionScore(char x, char y) {
    if (King::color == Color::White) {
        return King::scoreBoard[7 - y][x];
    }
    else {
        return -King::scoreBoard[y][x];
    }
}