//
// Created by Christopher Corona on 4/1/2016.
//

#include "Food.h"

namespace Gaming
{

//  class Food : public Resource {
//  private:
//  static const char FOOD_ID;
    const char Food::FOOD_ID = 'F';

//  public:
    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g,p,capacity)
    {

    }
    Food::~Food()
    {

    }

    void Food::print(std::ostream &os) const
    {
        os << FOOD_ID << __id;
    }
}