cmake_minimum_required(VERSION 3.19)
project(KriegspielChess)

set(CMAKE_CXX_STANDARD 20)

add_executable(KriegspielChess main.cpp  Figures/Bishop.h Figures/Bishop.cpp Figures/Figure.h Figures/Figure.cpp
        Figures/King.h Figures/King.cpp Figures/Knight.h Figures/Knight.cpp Figures/Pawn.h Figures/Pawn.cpp
        Figures/Queen.h Figures/Queen.cpp Figures/Rook.h Figures/Rook.cpp
        Board.cpp Board.h Engine.h Engine.cpp Figures.h Game.h Utility.h)