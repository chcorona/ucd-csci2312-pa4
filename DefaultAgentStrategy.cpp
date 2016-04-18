//
// Created by Christopher Corona on 4/1/2016.
//

#include "DefaultAgentStrategy.h"

namespace Gaming
{

//    class DefaultAgentStrategy : public Strategy {
//    public:

    DefaultAgentStrategy::DefaultAgentStrategy()
    {

    }

    DefaultAgentStrategy::~DefaultAgentStrategy()
    {

    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        return STAY;
    }
}