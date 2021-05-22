
#include "Pawn.h"

BoardGame::Pawn::Pawn(BoardGame::Color color) : Figure(color) {
    Figure::color = color;
    if (color == Color::Black) {
        symbol = "♟︎";
    } else {
        symbol = "♙";
    }
}

std::vector<std::tuple<char, char>> BoardGame::Pawn::getMoveList(BoardGame::Figure *(*squares)[8], char x, char y) {
    Figure::moveList.clear();
    if (Pawn::color == Color::White) {
        if (y < 7) {
            //Move one square ahead
            if (squares[x][y + 1] == nullptr) {
                Figure::moveList.push_back(std::tuple<char, char>(x, y + 1));
            }
            //Move two squares ahead
            if (y == 1) {
                if ((squares[x][y + 1] == nullptr) && (squares[x][y + 2] == nullptr)) {
                    Figure::moveList.push_back(std::tuple<char, char>(x, y + 2));
                }
            }
            //Move that corresponds to taking a piece to the right
            if ((x < 7) && squares[x + 1][y + 1] != nullptr) {
                if (squares[x + 1][y + 1]->getColor() != Pawn::color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x + 1, y + 1));
                }
            }
            //Move that corresponds to taking a piece to the left
            if ((x > 0) && squares[x - 1][y + 1] != nullptr) {
                if (squares[x - 1][y + 1]->getColor() != Pawn::color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x - 1, y + 1));
                }
            }
            if (y == 4) {
                if ((x > 0) && (squares[x - 1][y] != nullptr) && (squares[x - 1][y + 1] == nullptr) && (squares[x - 1][y]->getPieceType() == PieceType::Pawn) && squares[x - 1][y]->getColor() != color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x - 1, y + 1)); //white left en passant possible; board needs to check if the pawn to be captured moved in the prev. round
                }
                if ((x < 7) && (squares[x + 1][y] != nullptr) && (squares[x + 1][y + 1] == nullptr) && (squares[x + 1][y]->getPieceType() == PieceType::Pawn) && squares[x + 1][y]->getColor() != color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x + 1, y + 1)); //white right en passant possible; board needs to check if the pawn to be captured moved in the prev. round
                }
            }
        }
    }
    else if (Pawn::color == Color::Black) {
        if (y > 0) {
            //Move one square ahead
            if (squares[x][y - 1] == nullptr) {
                Figure::moveList.push_back(std::tuple<char, char>(x, y - 1));
            }
            //Move two squares ahead
            if (y == 6) {
                if ((squares[x][y - 1] == nullptr) && (squares[x][y - 2] == nullptr)) {
                    Figure::moveList.push_back(std::tuple<char, char>(x, y - 2));
                }
            }
            //Move that corresponds to taking a piece to the right
            if ((x < 7) && squares[x + 1][y - 1] != nullptr) {
                if (squares[x + 1][y - 1]->getColor() != Pawn::color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x + 1, y - 1));
                }
            }
            //Move that corresponds to taking a piece to the left
            if ((x > 0) && squares[x - 1][y - 1] != nullptr) {
                if (squares[x - 1][y - 1]->getColor() != Pawn::color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x - 1, y - 1));
                }
            }
            if (y == 3) {
                if ((x > 0) && (squares[x - 1][y] != nullptr) && (squares[x - 1][y - 1] == nullptr) && (squares[x - 1][y]->getPieceType() == PieceType::Pawn) && squares[x - 1][y]->getColor() != color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x - 1, y - 1)); //black left en passant possible; board needs to check if the pawn to be captured moved in the prev. round
                }
                if ((x < 7) && (squares[x + 1][y] != nullptr) && (squares[x + 1][y - 1] == nullptr) && (squares[x + 1][y]->getPieceType() == PieceType::Pawn) && squares[x + 1][y]->getColor() != color) {
                    Figure::moveList.push_back(std::tuple<char, char>(x + 1, y - 1)); //black right en passant possible; board needs to check if the pawn to be captured moved in the prev. round
                }
            }
        }
    }
    return Figure::moveList;
}

std::vector<std::tuple<char, char>> BoardGame::Pawn::getCaptureMoveList(Figure* squares[8][8], char x, char y) {
    Figure::captureMoveList.clear();
    if (Pawn::color == Color::White) {
        if (y < 7) {
            //Move that corresponds to taking a piece to the right
            if ((x < 7) && squares[x + 1][y + 1] != nullptr) {
                if (squares[x + 1][y + 1]->getColor() != Pawn::color) {
                    Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y + 1));
                }
            }
            //Move that corresponds to taking a piece to the left
            if ((x > 0) && squares[x - 1][y + 1] != nullptr) {
                if (squares[x - 1][y + 1]->getColor() != Pawn::color) {
                    Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y + 1));
                }
            }
        }
    }
    else if (Pawn::color == Color::Black) {
        if (y > 0) {
            //Move that corresponds to taking a piece to the right
            if ((x < 7) && squares[x + 1][y - 1] != nullptr) {
                if (squares[x + 1][y - 1]->getColor() != Pawn::color) {
                    Figure::captureMoveList.push_back(std::tuple<char, char>(x + 1, y - 1));
                }
            }
            //Move that corresponds to taking a piece to the left
            if ((x > 0) && squares[x - 1][y - 1] != nullptr) {
                if (squares[x - 1][y - 1]->getColor() != Pawn::color) {
                    Figure::captureMoveList.push_back(std::tuple<char, char>(x - 1, y - 1));
                }
            }
        }
    }
    return Figure::captureMoveList;
}

std::string BoardGame::Pawn::getSymbol() {
    return Pawn::symbol;
}

int BoardGame::Pawn::getValue() {
    if (Pawn::color == Color::White) {
        return Pawn::value;
    }
    else {
        return -Pawn::value;
    }
}

BoardGame::PieceType BoardGame::Pawn::getPieceType() {
    return Pawn::pieceType;
}

int BoardGame::Pawn::getPositionScore(char x, char y) {
    if (Pawn::color == Color::White) {
        return Pawn::scoreBoard[7 - y][x];
    }
    else {
        return -Pawn::scoreBoard[y][x];
    }
}

