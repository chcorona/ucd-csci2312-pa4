//
// Created by Christopher Corona on 4/1/2016.
//

#include "Advantage.h"

namespace Gaming
{
//  class Advantage : public
//  Resource{
//
//  private:
//  static const char ADVANTAGE_ID;
    const char Advantage::ADVANTAGE_ID = 'D';

//  public:
//  static const double ADVANTAGE_MULT_FACTOR;
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g,p,capacity)
    {

    }
    Advantage::~Advantage()
    {

    }

    void Advantage::print(std::ostream &os) const
    {
        os << ADVANTAGE_ID << __id;
    }

    double Advantage::getCapacity() const
    {
        return __capacity*ADVANTAGE_MULT_FACTOR;
    }

    double Advantage::consume()
    {
        return __capacity;
    }
}
