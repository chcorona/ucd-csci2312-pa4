//
// Created by Christopher Corona on 4/1/2016.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming
{

//  class AggressiveAgentStrategy : public Strategy {
//  double __agentEnergy;
//
//  public:
//  static const double DEFAULT_AGGRESSION_THRESHOLD;
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {

    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
    {
        return STAY;
    }
}