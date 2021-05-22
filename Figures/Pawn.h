
#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Figure.h"

namespace BoardGame {
    class Pawn : public Figure{
    private:
        std::string symbol;
        static const int value = 100;
        static const PieceType pieceType = PieceType::Pawn;
        int scoreBoard[8][8] = {
                { 0,  0,  0,  0,  0,  0,  0,  0},
                {50, 50, 50, 50, 50, 50, 50, 50},
                {10, 10, 20, 30, 30, 20, 10, 10},
                {5,  5, 10, 25, 25, 10,  5,  5},
                {0,  0,  0, 20, 20,  0,  0,  0},
                {5, -5,-10,  0,  0,-10, -5,  5},
                {5, 10, 10,-20,-20, 10, 10,  5},
                {0,  0,  0,  0,  0,  0,  0,  0}
        };
    public:
        Pawn(Color color);
        std::vector<std::tuple<char, char>> getMoveList(Figure* squares[8][8], char x, char y) override;
        std::vector<std::tuple<char, char>> getCaptureMoveList(Figure* squares[8][8], char x, char y) override;
        std::string getSymbol() override;
        int getValue() override;
        PieceType getPieceType() override;
        int getPositionScore(char x, char y) override;
    };
}

#endif //CHESS_PAWN_H
