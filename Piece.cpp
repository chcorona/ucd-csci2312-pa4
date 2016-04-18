//
// Created by Christopher Corona on 4/1/2016.
//

#include "Piece.h"

namespace Gaming
{
    unsigned int Piece::__idGen = 0;

    //public:
    Piece::Piece(const Game &g, const Position &p) :__game(g), __position(p)
    {
        __id = __idGen ++;
        __finished = false;
        __turned = false;
    }

    Piece:: ~Piece()
    {

    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece)
    {
        piece.print(os);
        return os;
    }
}
