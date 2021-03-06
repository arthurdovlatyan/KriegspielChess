
#include "Engine.h"


void BoardGame::Engine::updateSearchProgress(ChessBoard* board) {
    if ((Engine::nodes+Engine::quiescenceNodes) % updateAfterNodes == 0) {
        if (Engine::updateFct!=nullptr)
            Engine::updateFct(this);
        if (Engine::iterativeDeepening) {
            double timePassed = (double(std::clock()) - double(Engine::startTime)) / CLOCKS_PER_SEC;
            if (timePassed > Engine::timeLimit) Engine::abortSearch = true;
        }
    }
}

/*Calibrates the frequency at which updateFct is called*/
void BoardGame::Engine::calculateUpdateThreshold() {
    int nodesPerSecond = (Engine::nodes + Engine::quiescenceNodes) / Engine::getTimePassed();
    //20 updates per Second
    Engine::updateAfterNodes = nodesPerSecond / 20;
}

/*Performs a search of all capture moves up to the depth prescribed by quiescenceLimit*/
int BoardGame::Engine::quiescenceSearch(ChessBoard* board, Color colour, char depth, int alpha, int beta) {
    Engine::updateSearchProgress(board);
    int value = Engine::evalHeuristic(board);
    if (depth == Engine::depthLimit + Engine::quiescenceLimit) return value;
    else {
        MoveData move;
        if (colour == Color::White) {
            if (value >= beta) return value;
            if (alpha < value) alpha = value;
            for (char x = 0; x <= 7; x++) {
                for (char y = 0; y <= 7; y++) {
                    if ((board->squares[x][y] != nullptr) && (board->squares[x][y]->getColor() == colour)) {
                        std::vector<std::tuple<char, char>> moveList;
                        moveList = board->squares[x][y]->getCaptureMoveList(board->squares, x, y); //Only capture-moves are investigated
                        for (unsigned int i = 0; i < moveList.size(); i++) {
                            Engine::quiescenceNodes++;
                            move = board->moveTo(std::tuple<char, char>(x, y), moveList[i]);
                            if (move.validMove) {
                                if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                                    board->undoMove(move);
                                    return Engine::BLACK_MAX;
                                }
                                value = Engine::quiescenceSearch(board, Color::Black, depth + 1, alpha, beta);
                                board->undoMove(move);
                                if (value >= beta) return value;
                                if (alpha < value) alpha = value;
                            }
                        }
                    }
                }
            }
            return value;
        }
        else {
            if (value <= alpha) return value;
            if (value < beta) beta = value;
            for (char x = 0; x <= 7; x++) {
                for (char y = 0; y <= 7; y++) {
                    if ((board->squares[x][y] != nullptr) && (board->squares[x][y]->getColor() == colour)) {
                        std::vector<std::tuple<char, char>> moveList;
                        moveList = board->squares[x][y]->getCaptureMoveList(board->squares, x, y);
                        for (unsigned int i = 0; i < moveList.size(); i++) {
                            Engine::quiescenceNodes++;
                            move = board->moveTo(std::tuple<char, char>(x, y), moveList[i]);
                            if (move.validMove) {
                                if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                                    board->undoMove(move);
                                    return Engine::WHITE_MIN;
                                }
                                value = Engine::quiescenceSearch(board, Color::White, depth + 1, alpha, beta);
                                board->undoMove(move);
                                if (value <= alpha) return value;
                                if (value < beta) beta = value;
                            }
                        }
                    }
                }
            }
        }
    }
    return value;
}

int BoardGame::Engine::alphaBeta(ChessBoard* board, Color colour, char depth, int alpha, int beta) {
    Engine::updateSearchProgress(board);
    if (depth == Engine::depthLimit) {
        return Engine::quiescenceSearch(board, colour, depth, alpha, beta);
    }
    else {
        MoveData move;
        if (colour == Color::White) {
            int value = Engine::WHITE_MIN;
            if (Engine::abortSearch) return value;
            for (char x = 0; x <= 7; x++) {
                for (char y = 0; y <= 7; y++) {
                    if ((board->squares[x][y] != nullptr) && (board->squares[x][y]->getColor() == colour)) {
                        std::vector<std::tuple<char, char>> moveList;
                        moveList = board->squares[x][y]->getMoveList(board->squares, x, y);
                        for (unsigned int i = 0; i < moveList.size(); i++) {
                            Engine::nodes++;
                            move = board->moveTo(std::tuple<char, char>(x, y), moveList[i]);
                            if (move.validMove) {
                                if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                                    board->undoMove(move);
                                    return Engine::BLACK_MAX;
                                }
                                value = std::max(value, Engine::alphaBeta(board, Color::Black, depth + 1, alpha, beta));
                                if (value > alpha) {
                                    alpha = value;
                                    Engine::optimalTurnSequence[depth] = std::tuple<char, char, char, char>(x, y, std::get<0>(moveList[i]), std::get<1>(moveList[i]));
                                }
                                board->undoMove(move);
                                if (alpha >= beta) return value;
                            }
                        }
                    }
                }
            }
            return value;
        }
        else {
            int value = Engine::BLACK_MAX;
            if (Engine::abortSearch) return value;
            for (char x = 0; x <= 7; x++) {
                for (char y = 0; y <= 7; y++) {
                    if ((board->squares[x][y] != nullptr) && (board->squares[x][y]->getColor() == colour)) {
                        std::vector<std::tuple<char, char>> moveList;
                        moveList = board->squares[x][y]->getMoveList(board->squares, x, y);
                        for (unsigned int i = 0; i < moveList.size(); i++) {
                            Engine::nodes++;
                            move = board->moveTo(std::tuple<char, char>(x, y), moveList[i]);
                            if (move.validMove) {
                                if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                                    board->undoMove(move);
                                    return Engine::WHITE_MIN;
                                }
                                value = std::min(value, Engine::alphaBeta(board, Color::White, depth + 1, alpha, beta));
                                if (value < beta) {
                                    Engine::optimalTurnSequence[depth] = std::tuple<char, char, char, char>(x, y, std::get<0>(moveList[i]), std::get<1>(moveList[i]));
                                    beta = value;
                                }
                                board->undoMove(move);
                                if (alpha >= beta) return value;
                            }
                        }
                    }
                }
            }
            return value;
        }
    }
}

/*The first level of alpha beta search takes a preferred firstMove to potentially improve pruning;
firstMove is a result of previous searches when using iterative deepening*/
int BoardGame::Engine::alphaBeta_depth0(ChessBoard* board, Color colour, int alpha, int beta, std::tuple<char, char, char, char> firstMove) {
    MoveData move;
    if (colour == Color::White) {
        int value = Engine::WHITE_MIN;
        Engine::nodes++;
        std::tuple<char, char> orig = std::tuple<char, char>(std::get<0>(firstMove), std::get<1>(firstMove));
        std::tuple<char, char> dest = std::tuple<char, char>(std::get<2>(firstMove), std::get<3>(firstMove));
        move = board->moveTo(orig, dest);
        if (move.validMove) {
            if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                board->undoMove(move);
                return Engine::BLACK_MAX;
            }
            value = std::max(value, Engine::alphaBeta(board, Color::Black, 1, alpha, beta));
            alpha = value;
            Engine::optimalTurnSequence[0] = std::tuple<char, char, char, char>(std::get<0>(firstMove), std::get<1>(firstMove), std::get<2>(firstMove), std::get<3>(firstMove));
            board->undoMove(move);
            if (Engine::abortSearch) return value;
        }
        for (char x = 0; x <= 7; x++) {
            for (char y = 0; y <= 7; y++) {
                if ((board->squares[x][y] != nullptr) && (board->squares[x][y]->getColor() == colour)) {
                    std::vector<std::tuple<char, char>> moveList;
                    moveList = board->squares[x][y]->getMoveList(board->squares, x, y);
                    for (unsigned int i = 0; i < moveList.size(); i++) {
                        if ((std::get<0>(moveList[i]) == std::get<2>(firstMove)) && (std::get<1>(moveList[i]) == std::get<3>(firstMove)) && (x == std::get<0>(firstMove)) && (y == std::get<1>(firstMove)))
                            continue;
                        Engine::nodes++;
                        move = board->moveTo(std::tuple<char, char>(x, y), moveList[i]);
                        if (move.validMove) {
                            if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                                board->undoMove(move);
                                return Engine::BLACK_MAX;
                            }
                            int newValue = std::max(value, Engine::alphaBeta(board, Color::Black, 1, alpha, beta));
                            board->undoMove(move);
                            if (Engine::abortSearch) return value; //since the search tree was not fully traversed, the result is discarded
                            else value = newValue;
                            if (value > alpha) {
                                alpha = value;
                                Engine::optimalTurnSequence[0] = std::tuple<char, char, char, char>(x, y, std::get<0>(moveList[i]), std::get<1>(moveList[i]));
                            }
                            if (alpha >= beta) return value;
                        }
                    }
                }
            }
        }
        return value;
    }
    else {
        int value = Engine::BLACK_MAX;
        Engine::nodes++;
        std::tuple<char, char> orig = std::tuple<char, char>(std::get<0>(firstMove), std::get<1>(firstMove));
        std::tuple<char, char> dest = std::tuple<char, char>(std::get<2>(firstMove), std::get<3>(firstMove));
        move = board->moveTo(orig, dest);
        if (move.validMove) {
            if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                board->undoMove(move);
                return Engine::WHITE_MIN;
            }
            value = std::min(value, Engine::alphaBeta(board, Color::White, 1, alpha, beta));
            if (value < beta) {
                Engine::optimalTurnSequence[0] = std::tuple<char, char, char, char>(std::get<0>(firstMove), std::get<1>(firstMove), std::get<2>(firstMove), std::get<3>(firstMove));
                beta = value;
            }
            board->undoMove(move);
            if (Engine::abortSearch) {
                return value;
            }
        }
        for (char x = 0; x <= 7; x++) {
            for (char y = 0; y <= 7; y++) {
                if ((board->squares[x][y] != nullptr) && (board->squares[x][y]->getColor() == colour)) {
                    std::vector<std::tuple<char, char>> moveList;
                    moveList = board->squares[x][y]->getMoveList(board->squares, x, y);
                    for (unsigned int i = 0; i < moveList.size(); i++) {
                        if ((std::get<0>(moveList[i]) == std::get<2>(firstMove)) && (std::get<1>(moveList[i]) == std::get<3>(firstMove)) && (x == std::get<0>(firstMove)) && (y == std::get<1>(firstMove)))
                            continue;
                        Engine::nodes++;
                        move = board->moveTo(std::tuple<char, char>(x, y), moveList[i]);
                        if (move.validMove) {
                            if ((move.pieceTaken != nullptr) && (move.pieceTaken->getPieceType() == PieceType::King)) {
                                board->undoMove(move);
                                return Engine::WHITE_MIN;
                            }
                            int newValue = std::min(value, Engine::alphaBeta(board, Color::White, 1, alpha, beta));
                            board->undoMove(move);
                            if (Engine::abortSearch) return value; //the move might have been better than a previous choice, but since the search tree was not fully traversed, the result is discarded
                            else value = newValue;
                            if (value < beta) {
                                Engine::optimalTurnSequence[0] = std::tuple<char, char, char, char>(x, y, std::get<0>(moveList[i]), std::get<1>(moveList[i]));
                                beta = value;
                            }
                            if (alpha >= beta) return value;
                        }
                    }
                }
            }
        }
        return value;
    }
}

/*The eval function currently accounts for piece values, positioning according to the scoreBoards, and castling*/
int BoardGame::Engine::evalHeuristic(ChessBoard* board) {
    int evaluation = 0;
    for (char x = 0; x <= 7; x++) {
        for (char y = 0; y <= 7; y++) {
            if (board->squares[x][y] != nullptr) evaluation = evaluation + board->squares[x][y]->getValue() + board->squares[x][y]->getPositionScore(x, y);
        }
    }
    if (board->whiteCastled) evaluation = evaluation + 50;
    if (board->blackCastled) evaluation = evaluation - 50;
    if (Engine::randomness) {
        evaluation = evaluation + (std::rand() % Engine::randDouble)-Engine::randLimit;
    }
    return evaluation;
}

int BoardGame::Engine::calculateMove_fixedDepth(ChessBoard* board, Color colour) {
    Engine::abortSearch = false;
    Engine::iterativeDeepening = false;
    Engine::nodes = 0;
    Engine::quiescenceNodes = 0;
    Engine::optimalTurnSequence = std::vector<std::tuple<char, char, char, char>>(Engine::depthLimit + Engine::quiescenceLimit + 1);
    Engine::startTime = std::clock();
    board->allowIllegalMoves = true;
    Engine::optimalValue = Engine::alphaBeta(board, colour, 0, Engine::WHITE_MIN, Engine::BLACK_MAX);
    board->allowIllegalMoves = false;
    if ((Engine::optimalValue == Engine::WHITE_MIN) && (colour == Color::White)) Engine::optimalTurnSequence[0] = board->getPossibleMoves(colour).at(0);
    if ((Engine::optimalValue == Engine::BLACK_MAX) && (colour == Color::Black)) Engine::optimalTurnSequence[0] = board->getPossibleMoves(colour).at(0);
    if (Engine::updateFct != nullptr)
        Engine::updateFct(this);
    Engine::calculateUpdateThreshold();
    return Engine::optimalValue;
}

int BoardGame::Engine::calculateMove_iterativeDeepening(ChessBoard* board, Color colour) {
    Engine::abortSearch = false;
    Engine::iterativeDeepening = true;
    Engine::nodes = 0;
    Engine::quiescenceNodes = 0;
    Engine::optimalTurnSequence = std::vector<std::tuple<char, char, char, char>>(Engine::depthLimit + Engine::quiescenceLimit + 1);
    board->allowIllegalMoves = true;
    Engine::startTime = std::clock();
    calculateMove_random(board, colour);
    std::tuple<char, char, char, char> firstMove = Engine::optimalTurnSequence.at(0);
    Engine::depthLimit = 0;
    //subsequent searches while time limit not reached
    while (!Engine::abortSearch) {
        Engine::depthLimit++;
        Engine::optimalTurnSequence.resize(Engine::depthLimit + Engine::quiescenceLimit + 1);
        int newValue = Engine::alphaBeta_depth0(board, colour, Engine::WHITE_MIN, Engine::BLACK_MAX,firstMove);
        if (!Engine::abortSearch) Engine::optimalValue = newValue;
        firstMove = Engine::optimalTurnSequence.at(0);
        double timePassed = (double(std::clock()) - double(Engine::startTime)) / CLOCKS_PER_SEC;
        if (timePassed > Engine::timeLimit) Engine::abortSearch = true;
    }
    board->allowIllegalMoves = false;
    if (Engine::updateFct!=nullptr)
        Engine::updateFct(this);
    Engine::calculateUpdateThreshold();
    return Engine::optimalValue;
}

void BoardGame::Engine::calculateMove_random(ChessBoard* board, Color colour) {
    srand(time(NULL));
    Engine::nodes = 0;
    Engine::quiescenceNodes = 0;
    Engine::startTime = std::clock();
    bool illegalMoves = board->allowIllegalMoves;
    board->allowIllegalMoves = false;
    std::vector<std::tuple<char, char, char, char>> moveList = board->getPossibleMoves(colour);
    Engine::nodes = moveList.size();
    board->allowIllegalMoves = illegalMoves;
    if (moveList.size() != 0) {
        int rnd = std::rand() % moveList.size();
        Engine::optimalTurnSequence = std::vector<std::tuple<char, char, char, char>>(1);
        Engine::optimalTurnSequence[0] = moveList.at(rnd);
        Engine::optimalValue = Engine::evalHeuristic(board);
    }
}

int BoardGame::Engine::getNodes() {
    return Engine::nodes;
}

int BoardGame::Engine::getQuiescenceNodes() {
    return Engine::quiescenceNodes;
}

double BoardGame::Engine::getTimePassed() {
    return (double(std::clock()) - double(Engine::startTime)) / CLOCKS_PER_SEC;
}

bool BoardGame::Engine::seachAborted() {
    return Engine::abortSearch;
}

BoardGame::Engine::Engine() {
    srand(time(NULL));
    Engine::randDouble = Engine::randLimit * 2;
}