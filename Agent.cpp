//
// Created by Christopher Corona on 4/1/2016.
//

#include "Agent.h"
#include "Resource.h"

namespace Gaming
{

//  class Agent : public Piece {
//
//  protected:
//      double __energy;
//
//  public:
//  static const double AGENT_FATIGUE_RATE;
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p), __energy(energy)
    {

    }

    Agent::~Agent()
    {

    }

    void Agent::age()
    {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other)
    {
        Piece *a = &other;
        Resource *res = dynamic_cast <Resource *> (a);

        if (res)
            interact(res);
        Agent *agent = dynamic_cast <Agent *> (a);

        if (agent)
            interact(agent);

        if (!isFinished())
        {
            Position OLD;
            Position NEW;
            OLD = getPosition();
            NEW = other.getPosition();
            other.setPosition(OLD);
            setPosition(NEW);
        }

        return *this;
    }

    Piece &Agent::interact(Agent *ia)
    {
        if (__energy == ia->getEnergy())
        {
            this->finish();
            ia->finish();
        }
        else if (__energy > ia->getEnergy())
        {
            __energy -= ia->getEnergy();
            ia->finish();
        }
        else
        {
            ia->addEnergy(__energy * -1);
            this->finish();
        }
        return *this;
    }

    Piece &Agent::interact(Resource *ir)
    {
        if (ir->getType() == FOOD)
            __energy += ir->consume();
        if (ir->getType() == ADVANTAGE)
            __energy *= ir->consume();
        return *this;
    }
}