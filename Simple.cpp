//
// Created by Christopher Corona on 4/1/2016.
//

#include "Simple.h"

namespace Gaming
{

//    class Simple : public Agent {
//    private:
//        static const char SIMPLE_ID;
    const char Simple::SIMPLE_ID = 'S';

//    public:
    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g,p,energy)
    {

    }

    Simple::~Simple()
    {

    }

    void Simple::print(std::ostream &os) const
    {
        os << SIMPLE_ID << __id;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        std::vector<int> f, e;

        Position newP;
        Position newP1(1,1);

        for(int i = 0; i < s.array.size(); ++i)
        {
            if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
                f.push_back(i);

            else if(s.array[i]==EMPTY)
                e.push_back(i);
        }

        if(f.size()>0)
        {
            newP = Game::randomPosition(f);
                return __game.reachSurroundings(newP1,newP);
        }
        else if(e.size()>0)
        {
            newP= Game::randomPosition(e);
                return __game.reachSurroundings(newP1, newP);
        }
        else
            return STAY;
    }
}