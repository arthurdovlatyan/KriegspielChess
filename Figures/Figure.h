

#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H

#include <vector>
#include <tuple>
#include "../Utility.h"
namespace BoardGame {
    class Figure {
    private:
        // TODO can we make the symbol a static union
        std::string symbol = " ";
        static const int value = 0;
        static const PieceType pieceType = PieceType::None;
    protected:
        Color color;
        int moveCount = 0;
        std::vector<std::tuple<char,char>> moveList; // all possible moves
        std::vector<std::tuple<char,char>> captureMoveList; // all possible capture moves
    public:
        Figure(Color color);
        Color getColor();
        virtual std::vector<std::tuple<char,char>> getMoveList(Figure* squares[8][8], char x, char y);
        virtual std::vector<std::tuple<char,char>> getCaptureMoveList(Figure* squares[8][8], char x, char y);
        virtual std::string getSymbol();
        virtual int getValue();
        virtual PieceType getPieceType();
        virtual int getPositionScore(char x, char y);
        void setMoveCount(int n);
        int getMoveCount();
    };


}


#endif //CHESS_FIGURE_H
