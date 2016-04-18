//
// Created by Christopher Corona on 4/1/2016.
//

#include "Strategic.h"

namespace Gaming
{

//    class Strategic : public Agent {
//    private:
//        static const char STRATEGIC_ID;
//
//        Strategy *__strategy;
    const char Strategic::STRATEGIC_ID = 'T';

//    public:
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g,p,energy)
    {
        __strategy = s;
    }

    Strategic::~Strategic()
    {

    }

    void Strategic::print(std::ostream &os) const
    {
        os << STRATEGIC_ID << __id;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }
}