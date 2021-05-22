

#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "Board.h"
#include "iostream"
#include "sstream"
#include "Engine.h"
namespace BoardGame {
    class Game {
    private:
        ChessBoard board;
        MoveData move;
        Engine engine;
        int gameCount;
        constexpr static const int alloc_time_white = 1;
        constexpr static const int alloc_time_black = 1;
        bool white_rnd = false;
        bool black_rnd = false;
        int blackWins = 0;
        int whiteWins = 0;
        int moveCount = 1;
        Color colour = Color::White;
        static const char CONV_ERROR = 127;
        static const int MAX_MOVE_COUNT = 200;

    protected:
        static char numToLetter(char coord) {
            switch (coord) {
                case 0:
                    return 'a';
                    break;
                case 1:
                    return 'b';
                    break;
                case 2:
                    return 'c';
                    break;
                case 3:
                    return 'd';
                    break;
                case 4:
                    return 'e';
                    break;
                case 5:
                    return 'f';
                    break;
                case 6:
                    return 'g';
                    break;
                case 7:
                    return 'h';
                    break;
                default:
                    return CONV_ERROR;
            }
        }

        static char letterToNum(char coord) {
            switch (coord) {
                case 'a':
                    return 0;
                    break;
                case 'b':
                    return 1;
                    break;
                case 'c':
                    return 2;
                    break;
                case 'd':
                    return 3;
                    break;
                case 'e':
                    return 4;
                    break;
                case 'f':
                    return 5;
                    break;
                case 'g':
                    return 6;
                    break;
                case 'h':
                    return 7;
                    break;
                default:
                    return CONV_ERROR;
            }
        }

        static std::string numberToString(int Number) {
            std::ostringstream ss;
            ss << Number;
            return ss.str();
        }

        static void printUpdate(Engine *engine) {
            int xOrig = std::get<0>(engine->optimalTurnSequence.at(0));
            int yOrig = std::get<1>(engine->optimalTurnSequence.at(0));
            int xDest = std::get<2>(engine->optimalTurnSequence.at(0));
            int yDest = std::get<3>(engine->optimalTurnSequence.at(0));
            if (engine->seachAborted()) std::cout << "\r" << "DONE. ";
            else std::cout << "\r" << "CALC..";
            std::cout << "opt=[" <<
                      numToLetter(xOrig) << numberToString(yOrig + 1) << numToLetter(xDest) << numberToString(yDest + 1)
                      <<
                      "]@val " << engine->optimalValue << " || "
                      << int(engine->depthLimit) + int(engine->quiescenceLimit) << "d="
                      << int(engine->depthLimit) << "n+" << int(engine->quiescenceLimit) << "h, " <<
                      (engine->getNodes() + engine->getQuiescenceNodes()) / 1000 << " kN="
                      << int(engine->getNodes() / 1000) << "n+" << int(engine->getQuiescenceNodes() / 1000) <<
                      "h, "
                      << int(((engine->getNodes() + engine->getQuiescenceNodes()) / 1000) / engine->getTimePassed()) <<
                      " kN/s, T=" << engine->getTimePassed() << "s    ";
        }

        void printBoard(ChessBoard *board, std::vector<std::tuple<char, char, char, char>> *moveList, MoveData *move,BoardGame::Color c) {
            // White
            int x, y;
            std::cout << "|";
            std::cout << "    a  b  c  d  e  f  g  h    ";
            std::cout << "|" << std::endl;
            for (y = 7; y >= 0; y--) {
                std::cout << "|";
                std::cout << " " << numberToString(y + 1) << " ";
                for (x = 0; x < 8; x++) {
                    if ((x + y) % 2 == 0) {
                    } else {
                    }
                    char moveAdj = ' ';
                    if (moveList != nullptr) {
                        if (c == BoardGame::Color::Black) {
                            for (unsigned int i = 0; i < moveList->size(); i++) {
                                if ((std::get<2>((*moveList)[i]) == x) && ((std::get<3>((*moveList)[i]) == y))) {
                                    moveAdj = '*';
                                }
                            }
                        }
                    }
                    if (board->squares[x][y] != nullptr) {
                        if (c == BoardGame::Color::Black) {
                            if ((move != nullptr) && (std::get<0>(move->dest) == x) && (std::get<1>(move->dest) == y)) {
                                moveAdj = '<';
                            }
                        }
                        if (board->squares[x][y]->getColor() == Color::Black) {
                            if ((x + y) % 2 == 0) {
                            } else {
                            }
                        }
                        if (board->squares[x][y]->getColor() == BoardGame::Color::Black) {
                            std::cout << " " << board->squares[x][y]->getSymbol();
                            std::cout << moveAdj;
                        } else {
                            std::cout << "  ";
                            std::cout << moveAdj;
                        }
                    } else {
                        if (move != nullptr) {
                            if (move->pieceMoved->getColor() == Color::Black) {
                                if ((x + y) % 2 == 0) {
                                } else {
                                }
                            }
                            if ((std::get<0>(move->orig) == x) && (std::get<1>(move->orig) == y)) {
                                if (c == BoardGame::Color::Black) {
                                    moveAdj = '_';
                                }
                            }
                        }
                        std::cout << " " << moveAdj << " ";
                    }
                }
                std::cout << " " << numberToString(y + 1) << " ";
                std::cout << "|" << std::endl;
            }
            std::cout << "|";
            std::cout << "    a  b  c  d  e  f  g  h    ";
            std::cout << "|" << std::endl;

//            std::vector<std::tuple<char, char, char, char>> mv = board->getPossibleMoves(BoardGame::Color::Black);
//            for (y = 7; y >= 0; y--) {
//                for (x = 0; x < 8; x++) {
//                    for (int i = 0; i < mv.size(); ++i) {
//                        if((std::get<2>((mv)[i]) == x) && ((std::get<3>((mv)[i]) == y)))
//                            std::cout << int(std::get<0>((mv.at(i)))) + 1 << " " << char(int(std::get<1>(mv.at(i))) + 65) << "  "
//                                  <<int(std::get<2>(mv.at(i)) ) + 1<< " " <<char(int( std::get<3>(mv.at(i))) + 65)<< std::endl;
//                    }
//                }
//            }
            //////////////////////////////////////////////////
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            // black
            x = 0, y = 0;
            std::cout << "|";
            std::cout << "    a  b  c  d  e  f  g  h    ";
            std::cout << "|" << std::endl;
            for (y = 7; y >= 0; y--) {
                std::cout << "|";
                std::cout << " " << numberToString(y + 1) << " ";
                for (x = 0; x < 8; x++) {
                    if ((x + y) % 2 == 0) {
                    } else {
                    }
                    char moveAdj = ' ';
                    if (moveList != nullptr) {
                        if (c == BoardGame::Color::White) {
                            for (unsigned int i = 0; i < moveList->size(); i++) {
                                if ((std::get<2>((*moveList)[i]) == x) && ((std::get<3>((*moveList)[i]) == y))) {
                                    moveAdj = '*';
                                }
                            }
                        }
                    }
                    if (board->squares[x][y] != nullptr) {
                        if ((move != nullptr) && (std::get<0>(move->dest) == x) && (std::get<1>(move->dest) == y)) {
                            if (c == BoardGame::Color::White) {
                                moveAdj = '<';
                            }
                        }
                        if (board->squares[x][y]->getColor() == Color::Black) {
                            if ((x + y) % 2 == 0) {
                            } else {
                            }
                        }
                        if (board->squares[x][y]->getColor() == BoardGame::Color::White) {
                            std::cout << " " << board->squares[x][y]->getSymbol();
                            std::cout << moveAdj;
                        } else {
                            std::cout << "  ";
                            std::cout << moveAdj;
                        }
                    } else {
                        if (move != nullptr) {
                            if (move->pieceMoved->getColor() == Color::Black) {
                                if ((x + y) % 2 == 0) {
                                } else {
                                }
                            }
                            if ((std::get<0>(move->orig) == x) && (std::get<1>(move->orig) == y)) {
                                if (c == BoardGame::Color::White) {
                                    moveAdj = '_';
                                }
                            }
                        }
                        std::cout << " " << moveAdj << " ";
                    }
                }
                std::cout << " " << numberToString(y + 1) << " ";
                std::cout << "|" << std::endl;
            }
            std::cout << "|";
            std::cout << "    a  b  c  d  e  f  g  h    ";
            std::cout << "|" << std::endl;
            char moveAdj = ' ';
            // overseer
            ///////////////////////////////////////////////////
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            x = 0, y = 0;
            std::cout << "|";
            std::cout << "    a  b  c  d  e  f  g  h    ";
            std::cout << "|" << std::endl;
            for (y = 7; y >= 0; y--) {
                std::cout << "|";
                std::cout << " " << numberToString(y + 1) << " ";
                for (x = 0; x < 8; x++) {
                    if ((x + y) % 2 == 0) {
                    } else {
                    }
                    char moveAdj = ' ';
                    if (moveList != nullptr) {
                        for (unsigned int i = 0; i < moveList->size(); i++) {
                            if ((std::get<2>((*moveList)[i]) == x) && ((std::get<3>((*moveList)[i]) == y))) {
                                moveAdj = '*';
                            }
                        }
                    }
                    if (board->squares[x][y] != nullptr) {
                        if ((move != nullptr) && (std::get<0>(move->dest) == x) && (std::get<1>(move->dest) == y)) {
                            moveAdj = '<';
                        }
                        if (board->squares[x][y]->getColor() == Color::Black) {
                            if ((x + y) % 2 == 0) {
                            } else {
                            }
                        }

                        std::cout << " " << board->squares[x][y]->getSymbol();
                        std::cout << moveAdj;
                    } else {
                        if (move != nullptr) {
                            if (move->pieceMoved->getColor() == Color::Black) {
                                if ((x + y) % 2 == 0) {
//                            SetConsoleTextAttribute(hConsole, 32);
                                } else {
//                            SetConsoleTextAttribute(hConsole, 128);
                                }
                            }
                            if ((std::get<0>(move->orig) == x) && (std::get<1>(move->orig) == y)) {
                                moveAdj = '_';
                            }
                        }
                        std::cout << " " << moveAdj << " ";
                    }
                }
                std::cout << " " << numberToString(y + 1) << " ";
                std::cout << "|" << std::endl;
            }
            std::cout << "|";
            std::cout << "    a  b  c  d  e  f  g  h    ";
            std::cout << "|" << std::endl;
        }

        Color switchColour(Color colour) {
            if (colour == Color::White) {
                return Color::Black;
            } else {
                return Color::White;
            }
        }

        void printHelp() {
            std::cout << "Game Commands:" << std::endl;
            std::cout << "  'reset' restores the board to its initial state" << std::endl;
            std::cout << "  'help' displays the command list" << std::endl;
            std::cout << "Move Commands:" << std::endl;
            std::cout << "  'PQXY' moves the piece on PQ to XY (e.g. a4a5)" << std::endl;
            std::cout << "  'undo' reverts the last move" << std::endl;
            std::cout << "  'getmoves' displays all squares that can be moved to" << std::endl;
//            std::cout << "  'getcaptures' displays all attacked opponent pieces" << std::endl;
            std::cout << "Engine Commands:" << std::endl;
            std::cout << "  'engine' makes the engine respond with a move" << std::endl;
            std::cout << "  'engine_loop' lets the black and white engines play each other" << std::endl;
            std::cout
                    << "  'white_alloctime w' allocates a maximum computation time of w seconds to white (default: 2.5s)"
                    << std::endl;
            std::cout << "  'black_alloctime b' does the same for black (default: 2.5s)" << std::endl;
            std::cout << "  'white_rnd' toggles from calculated moves by white to completely random moves" << std::endl;
            std::cout << "  'black_rnd' does the same for black" << std::endl;
            std::cout << "  'quiet_limit h' to set the maximum horizon search depth to h (default: h=2)" << std::endl;
        }

        void printHeuristicVal(Engine *engine, ChessBoard *board) {
            engine->randomness = false;
            std::cout << "  " << engine->evalHeuristic(board) << "=Heuristic Valuation";
            engine->randomness = true;
        }

        void printMoveType(MoveData *move) {
            if (move->isPromotion) {
                if (move->pieceMoved->getColor() == Color::White) std::cout << "White promoted a Pawn!" << std::endl;
                else std::cout << "Black promoted a Pawn!" << std::endl;
            }
            if ((move->isWhiteLRookCastling) || (move->isWhiteRRookCastling))
                std::cout << "White castled!" << std::endl;
            if ((move->isBlackLRookCastling) || (move->isBlackRRookCastling))
                std::cout << "Black castled!" << std::endl;
            if (move->isEnPassant) {
                if (move->pieceMoved->getColor() == Color::White)
                    std::cout << "White captured en passant!" << std::endl;
                else std::cout << "Black captured en passant!" << std::endl;
            }
        }

    public:
        void play() {
            std::cout << "CONSOLE CHESS ENGINE" << std::endl;
            printHelp();
            engine.updateFct = printUpdate;
            std::string command = " ";
            printBoard(&board, nullptr, nullptr,colour);
            while ((command != "exit") && (command != "")) {
                //Prints the player whose turn it is and the heuristic valuation
                if (command != "skip_print") {
                    std::cout << "[" << moveCount << "] ";
                    if (colour == Color::White)
                        std::cout << "White's turn.";
                    else
                        std::cout << "Black's turn.";
                    if (moveCount < 10) std::cout << " ";
                    if (moveCount < 100) std::cout << " ";
                    printHeuristicVal(&engine, &board);
                    std::cout << std::endl;
                }
                //Get player command unless the engines are running a loop
                if (command != "engine_loop") {
                    std::cout << ">";
                    std::cin >> command;
                }

                //cycle through the different commands
                if (command == "undo") {
                    if (move.validMove) {
                        board.undoMove(move);
                        colour = switchColour(colour);
                        printBoard(&board, nullptr, nullptr,colour);
                    }
                    move.validMove = false;
                } else if (command == "debug") {
                    board.resetToDebugBoard();
                    colour = Color::White;
                    printBoard(&board, nullptr, nullptr,colour);
                } else if (command == "help") {
                    printHelp();
                    printBoard(&board, nullptr, nullptr,colour);
                    printHeuristicVal(&engine, &board);
                } else if (command == "reset") {
                    board.resetBoard();
                    colour = Color::White;
                    moveCount = 1;
                    printBoard(&board, nullptr, nullptr,colour);
                } else if (command == "exit") {
                    continue;
                } else if (command == "black_alloctime") {
                    std::cin >> (double &) alloc_time_black;
                    command = "skip_print";
                } else if (command == "white_alloctime") {
                    std::cin >> (double &) alloc_time_white;
                    command = "skip_print";
                } else if (command == "white_rnd") {
                    white_rnd = !white_rnd;
                    if (white_rnd) std::cout << "The engine now randomizes moves for white" << std::endl;
                    else std::cout << "Move randomization is switched off for white" << std::endl;
                    command = "skip_print";
                } else if (command == "black_rnd") {
                    black_rnd = !black_rnd;
                    if (black_rnd) std::cout << "The engine now randomizes moves for black" << std::endl;
                    else std::cout << "Move randomization is switched off for black" << std::endl;
                    command = "skip_print";
                } else if (command == "quiet_limit") {
                    std::cin >> engine.quiescenceLimit;
                    command = "skip_print";
                } else if (command == "engine") {
                    int val;
                    if (colour == Color::White) {
                        if (white_rnd)
                            engine.calculateMove_random(&board, colour);
                        else {
                            engine.timeLimit = alloc_time_white;
                            val = engine.calculateMove_iterativeDeepening(&board, colour);
                        }
                    } else {
                        if (black_rnd) {
                            engine.calculateMove_random(&board, colour);
                        } else {
                            engine.timeLimit = alloc_time_black;
                            val = engine.calculateMove_iterativeDeepening(&board, colour);
                        }
                    }
                    std::cout << std::endl;
                    int xOrig = std::get<0>(engine.optimalTurnSequence.at(0));
                    int yOrig = std::get<1>(engine.optimalTurnSequence.at(0));
                    int xDest = std::get<2>(engine.optimalTurnSequence.at(0));
                    int yDest = std::get<3>(engine.optimalTurnSequence.at(0));
                    move = board.moveTo(std::tuple<char, char>(xOrig, yOrig), std::tuple<char, char>(xDest, yDest));
                    if (move.validMove) {
                        if (((colour == Color::White) && (white_rnd)) || ((colour == Color::Black) && (black_rnd)))
                            std::cout << "RND=" << numToLetter(xOrig) << numberToString(yOrig + 1) <<
                                      numToLetter(xDest) << numberToString(yDest + 1) << std::endl;
                        else
                            std::cout << std::endl;
                        printBoard(&board, nullptr, &move,colour);
                        printMoveType(&move);
                        colour = switchColour(colour);
                        moveCount++;
                    }
                } else if (command == "engine_d") {
                    engine.depthLimit = 4;
                    int val = engine.calculateMove_fixedDepth(&board, colour);
                    std::cout << std::endl;
                    int xOrig = std::get<0>(engine.optimalTurnSequence.at(0));
                    int yOrig = std::get<1>(engine.optimalTurnSequence.at(0));
                    int xDest = std::get<2>(engine.optimalTurnSequence.at(0));
                    int yDest = std::get<3>(engine.optimalTurnSequence.at(0));
                    move = board.moveTo(std::tuple<char, char>(xOrig, yOrig), std::tuple<char, char>(xDest, yDest));
                    if (move.validMove) {
                        printBoard(&board, nullptr, &move,colour);
                        printMoveType(&move);
                        colour = switchColour(colour);
                        moveCount++;
                    }
                    std::cout << "=> Engine Move: " << numToLetter(xOrig) << numberToString(yOrig + 1) << " "
                              << numToLetter(xDest) << numberToString(yDest + 1) << std::endl;
                } else if (command == "engine_loop") {
                    int val;
                    if (colour == Color::White) {
                        if (white_rnd)
                            engine.calculateMove_random(&board, colour);
                        else {
                            engine.timeLimit = alloc_time_white;
                            val = engine.calculateMove_iterativeDeepening(&board, colour);
                        }
                    } else {
                        if (black_rnd) {
                            engine.calculateMove_random(&board, colour);
                        } else {
                            engine.timeLimit = alloc_time_black;
                            val = engine.calculateMove_iterativeDeepening(&board, colour);
                        }
                    }
                    int xOrig = std::get<0>(engine.optimalTurnSequence.at(0));
                    int yOrig = std::get<1>(engine.optimalTurnSequence.at(0));
                    int xDest = std::get<2>(engine.optimalTurnSequence.at(0));
                    int yDest = std::get<3>(engine.optimalTurnSequence.at(0));
                    move = board.moveTo(std::tuple<char, char>(xOrig, yOrig), std::tuple<char, char>(xDest, yDest));
                    if (move.validMove) {
                        if (((colour == Color::White) && (white_rnd)) || ((colour == Color::Black) && (black_rnd)))
                            std::cout << "RND=" << numToLetter(xOrig) << numberToString(yOrig + 1) <<
                                      numToLetter(xDest) << numberToString(yDest + 1) << std::endl;
                        else
                            std::cout << std::endl;
                        printBoard(&board, nullptr, &move,colour);
                        printMoveType(&move);
                        colour = switchColour(colour);
                        moveCount++;
                    }
                    if (moveCount > MAX_MOVE_COUNT) {
                        std::cout << "Move limit of " << MAX_MOVE_COUNT << " reached, resetting board." << std::endl;
                        board.resetBoard();
                        moveCount = 1;
                        colour = Color::White;
                        printBoard(&board, nullptr, nullptr,colour);
                        command = " ";
                    }
                }
//                else if (command == "getcapturemoves") {
//                    std::vector<std::tuple<char, char, char, char>> a = board.getPossibleCaptures(colour);
//                    printBoard(&board, &a, nullptr);
//                }
                else if (command == "getmoves") {
                    std::vector<std::tuple<char, char, char, char>> a = board.getPossibleMoves(colour);
                    printBoard(&board, &a, nullptr,colour);
                } else if (command == "isattacked") {
                    std::cin >> command;
                    std::tuple<char, char> orig = std::tuple<char, char>(letterToNum(command.at(0)),
                                                                         (command.at(1) - '0') -
                                                                         1); //Write error handler
                    if ((std::get<0>(orig) != CONV_ERROR) && (std::get<1>(orig) > 0) && (std::get<1>(orig) < 9)) {
                        std::cout << std::endl;
                        if (board.squareAttackedBy(orig, colour)) {
                            std::cout << "Attacked" << std::endl;
                        } else {
                            std::cout << "Not Attacked" << std::endl;
                        }
                    }
                } else if (command.length() == 4) {
                    std::tuple<char, char> orig = std::tuple<char, char>(letterToNum(command.at(0)),
                                                                         (command.at(1) - '0') -
                                                                         1); //Write error handler
                    std::tuple<char, char> dest = std::tuple<char, char>(letterToNum(command.at(2)),
                                                                         (command.at(3) - '0') - 1);
                    if ((std::get<0>(orig) != CONV_ERROR) && (std::get<1>(orig) >= 0) && (std::get<1>(orig) <= 7) &&
                        (std::get<0>(dest) != CONV_ERROR) && (std::get<1>(dest) >= 0) && (std::get<1>(dest) <= 7) &&
                        (board.squares[std::get<0>(orig)][std::get<1>(orig)] != nullptr) &&
                        (board.squares[std::get<0>(orig)][std::get<1>(orig)]->getColor() == colour)) {
                        std::cout << std::endl;
                        move = board.moveTo(orig, dest);
                        if (!move.validMove) {
                            std::cout << "Invalid move" << std::endl;
                        } else {
                            printBoard(&board, nullptr, &move,colour);
                            printMoveType(&move);
                            colour = switchColour(colour);
                        }
                    } else std::cout << "Invalid coordinates" << std::endl;
                } else std::cout << "Invalid command" << std::endl;

                //Evaluate the game state for checks & checkmates
                if (board.getPossibleMoves(Color::White).empty()) {
                    std::cout << "White is checkmate!" << std::endl;
                    blackWins++;
                    std::vector<std::tuple<char, char, char, char>> a = board.getPossibleMoves(Color::Black);
                    printBoard(&board, &a, nullptr,colour);
                    std::cout << "White wins:  " << whiteWins << ", Black wins: " << blackWins << std::endl;
                    std::cout << "Resetting Board." << std::endl;
                    board.resetBoard();
                    colour = Color::White;
                    printBoard(&board, nullptr, nullptr,colour);
                    moveCount = 1;
                    command = " ";
                }
                if (board.isChecked(Color::White)) {
                    std::cout << "White is checked" << std::endl;
                }
                if (board.getPossibleMoves(Color::Black).empty()) {
                    std::cout << "Black is checkmate!" << std::endl;
                    whiteWins++;
                    std::vector<std::tuple<char, char, char, char>> a = board.getPossibleMoves(Color::White);
                    printBoard(&board, &a, nullptr,colour);
                    std::cout << "White wins:  " << whiteWins << ", Black wins: " << blackWins << std::endl;
                    std::cout << "Resetting Board." << std::endl;
                    board.resetBoard();
                    colour = Color::White;
                    printBoard(&board, nullptr, nullptr,colour);
                    moveCount = 1;
                    command = " ";
                }
                if (board.isChecked(Color::Black)) {
                    std::cout << "Black is checked" << std::endl;
                }
            }
        }
    };

}
#endif //CHESS_GAME_H
