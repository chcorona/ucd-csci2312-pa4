//
// Created by Christopher Corona on 4/1/2016.
//

#include "Resource.h"
#include "Agent.h"

namespace Gaming
{
//    public:
//        static const double RESOURCE_SPOIL_FACTOR;
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g,p), __capacity(capacity)
    {

    }

    Resource::~Resource()
    {

    }

    double Resource::consume()
    {
        finish();
        return __capacity;
    }

    void Resource::age()
    {
        __capacity -= RESOURCE_SPOIL_FACTOR;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
    }

    // note: these won't be called while resources don't move
    Piece &Resource::operator*(Piece &other)
    {
        return *this;
    }

    Piece &Resource::interact(Agent *ia)
    {
        return *this;
    }

    Piece &Resource::interact(Resource *ir)
    {
        return *this;
    }
    // note: no interaction between resources
}