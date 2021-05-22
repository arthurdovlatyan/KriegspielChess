
#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Figure.h"

namespace BoardGame {
    class Knight : public Figure{
    private:
        std::string symbol;
        static const int value = 320;
        static const PieceType pieceType = PieceType::Knight;
        int scoreBoard[8][8] = {
                {-50,-40,-30,-30,-30,-30,-40,-50},
                {-40,-20,  0,  0,  0,  0,-20,-40},
                {-30,  0, 10, 15, 15, 10,  0,-30},
                {-30,  5, 15, 20, 20, 15,  5,-30},
                {-30,  0, 15, 20, 20, 15,  0,-30},
                {-30,  5, 10, 15, 15, 10,  5,-30},
                {-40,-20,  0,  5,  5,  0,-20,-40},
                {-50,-40,-30,-30,-30,-30,-40,-50}
        };
    public:
        Knight(Color colour);
        std::vector<std::tuple<char, char>> getMoveList(Figure* squares[8][8], char x, char y) override;
        std::vector<std::tuple<char, char>> getCaptureMoveList(Figure* squares[8][8], char x, char y) override;
        std::string getSymbol() override;
        int getValue() override;
        PieceType getPieceType() override;
        int getPositionScore(char x, char y) override;
    };
}

#endif //CHESS_KNIGHT_H
