

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Figure.h"

namespace BoardGame {
    class Queen : public Figure{
    private:
        std::string symbol;
        static const int value = 900;
        static const PieceType pieceType = PieceType::Queen;
        int scoreBoard[8][8] = {{ 0, 0, 0, 0, 0, 0, 0, 0},
                                {5, 10, 10, 10, 10, 10, 10, 5},
                                {-5, 0, 0, 0, 0, 0, 0, -5},
                                {-5, 0, 0, 0, 0, 0, 0, -5},
                                {-5, 0, 0, 0, 0, 0, 0, -5},
                                {-5, 0, 0, 0, 0, 0, 0, -5},
                                {-5, 0, 0, 0, 0, 0, 0, -5},
                                {0, 0, 0, 5, 5, 0, 0, 0}
        };
    public:
        Queen(Color colour);
        std::vector<std::tuple<char, char>> getMoveList(Figure* squares[8][8], char x, char y) override;
        std::vector<std::tuple<char, char>> getCaptureMoveList(Figure* squares[8][8], char x, char y) override;
        std::string getSymbol() override;
        int getValue() override;
        PieceType getPieceType() override;
        int getPositionScore(char x, char y) override;
    };
}

#endif //CHESS_QUEEN_H
