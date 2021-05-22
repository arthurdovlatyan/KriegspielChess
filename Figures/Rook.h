

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Figure.h"

namespace BoardGame {
    class Rook:  public Figure {
    private:
        std::string symbol;
        static const int value = 500;
        static const PieceType pieceType = PieceType::Rook;
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
        Rook(Color colour);
        std::vector<std::tuple<char, char>> getMoveList(Figure* squares[8][8], char x, char y) override;
        std::vector<std::tuple<char, char>> getCaptureMoveList(Figure* squares[8][8], char x, char y) override;
        std::string getSymbol() override;
        int getValue() override;
        PieceType getPieceType() override;
        int getPositionScore(char x, char y) override;
    };
}

#endif //CHESS_ROOK_H
