

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Figure.h"

namespace BoardGame {
    class Bishop : public Figure {
    private:
        std::string symbol;
        static const int value = 330;
        static const PieceType pieceType = PieceType::Bishop;
        int scoreBoard[8][8] = {{-20, -10, -10, -10, -10, -10, -10, -20},
                                {-10, 0,   0,   0,   0,   0,   0,   -10},
                                {-10, 0,   5,   10,  10,  5,   0,   -10},
                                {-10, 5,   5,   10,  10,  5,   5,   -10},
                                {-10, 0,   10,  10,  10,  10,  0,   -10},
                                {-10, 10,  10,  10,  10,  10,  10,  -10},
                                {-10, 5,   0,   0,   0,   0,   5,   -10},
                                {-20, -10, -10, -10, -10, -10, -10, -20}
        };
    public:
        Bishop(Color colour);

        std::vector<std::tuple<char, char>> getMoveList(Figure *squares[8][8], char x, char y) override;

        std::vector<std::tuple<char, char>> getCaptureMoveList(Figure *squares[8][8], char x, char y) override;

        std::string getSymbol() override;

        int getValue() override;

        PieceType getPieceType() override;

        int getPositionScore(char x, char y) override;
    };
}
#endif //CHESS_BISHOP_H
