
#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Figure.h"

namespace BoardGame {
    class King : public Figure{
    private:
        std::string symbol;
        static const int value = 30000;
        static const PieceType pieceType = PieceType::King;
        int scoreBoard[8][8] = {{-30, -40, -40, -50, -50, -40, -40, -30},
                                {-30, -40, -40, -50, -50, -40, -40, -30},
                                {-30, -40, -40, -50, -50, -40, -40, -30},
                                {-30, -40, -40, -50, -50, -40, -40, -30},
                                {-20, -30, -30, -40, -40, -30, -30, -20},
                                {-10, -20, -20, -20, -20, -20, -20, -10},
                                {20, 20, 0, 0, 0, 0, 20, 20},
                                {20, 30, 10, 0, 0, 10, 30, 20}
        };
    public:
        King(Color colour);
        std::vector<std::tuple<char, char>> getMoveList(Figure* squares[8][8], char x, char y) override;
        std::vector<std::tuple<char, char>> getCaptureMoveList(Figure* squares[8][8], char x, char y) override;
        std::string getSymbol() override;
        int getValue() override;
        PieceType getPieceType() override;
        int getPositionScore(char x, char y) override;
    };
}

#endif //CHESS_KING_H
