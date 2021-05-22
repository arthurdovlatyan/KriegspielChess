
#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Figures/Figure.h"
#include "Figures.h"

namespace BoardGame {
    struct MoveData
    {
        std::tuple<char, char> orig;
        std::tuple<char, char> dest;
        std::tuple<char, char> prevEnPassantPawn;
        Figure* pieceMoved = nullptr;
        Figure* pieceTaken = nullptr;
        bool isWhiteLRookCastling = false;
        bool isWhiteRRookCastling = false;
        bool isBlackLRookCastling = false;
        bool isBlackRRookCastling = false;
        bool isPromotion = false;
        bool isEnPassant = false;
        bool validMove = false;
    };
    class ChessBoard {
    private:
        void initializeOriginalSquares();
        Figure* originalSquares[8][8];
        int plyCount;
        std::vector<Figure*> promotedQueens;
        std::tuple<char, char> kingWhiteLocation;
        std::tuple<char, char> kingBlackLocation;
        std::tuple<char, char> enPassantPawn = std::tuple<char,char>(127,127);
    public:
        bool allowIllegalMoves = false;
        bool whiteCastled = false;
        bool blackCastled = false;
        Figure* squares[8][8];
        void resetToDebugBoard();
        void resetBoard();
        int getPlyCount();
        bool isChecked(Color colour);
        bool squareAttackedBy(std::tuple<char, char> square, Color colour);
        std::vector<std::tuple<char, char, char, char>> getPossibleCaptures(Color colour);
        std::vector<std::tuple<char, char, char, char>> getPossibleMoves(Color colour);
        MoveData moveTo(std::tuple<char, char> orig, std::tuple<char, char> dest);
        void undoMove(MoveData move);
        ChessBoard();
    };
}

#endif //CHESS_BOARD_H
