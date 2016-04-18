//
// Created by Christopher Corona on 4/1/2016.
//

#include <iomanip>
#include <set>
#include <sstream>
#include "Game.h"
#include "Piece.h"
#include "Simple.h"
#include "Strategic.h"
#include "Resource.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming
{

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();
//        static const unsigned int NUM_INIT_AGENT_FACTOR;
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
//        static const unsigned int NUM_INIT_RESOURCE_FACTOR;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

//        static const unsigned MIN_WIDTH, MIN_HEIGHT;
//        static const double STARTING_AGENT_ENERGY;
//        static const double STARTING_RESOURCE_CAPACITY;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    void Game::populate()// populate the grid (used in automatic random initialization of a Game)
    {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        while (numStrategic > 0)
        {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        while (numSimple > 0)
        {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        while (numAdvantages > 0)
        {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        while (numFoods > 0)
        {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    Game::Game() : Game (3,3)
    {

    }

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height)// note: manual population by default
    {
        if (width < MIN_WIDTH || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);

        for (int i = 0; i < (__width * __height); ++i)
        {
            __grid.push_back(nullptr);
        }

        if (!manual){populate();}
    }

    Game::Game(const Game &another)
    {

    }

    Game::~Game()
    {

    }

    // getters
    unsigned int Game::getNumPieces() const
    {
        unsigned int numPiece = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Piece *piece = dynamic_cast<Piece *>(*it);
            if (piece) numPiece++;
        }
        return numPiece;
    }

    unsigned int Game::getNumAgents() const
    {
        unsigned int numAgent = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Agent *agent = dynamic_cast<Agent *>(*it);
            if (agent) numAgent++;
        }
        return numAgent;
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int numSimple = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Simple *simple = dynamic_cast<Simple *>(*it);
            if (simple) numSimple++;
        }
        return numSimple;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned int numStrategic = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Strategic *strategic = dynamic_cast<Strategic *>(*it);
            if (strategic) numStrategic++;
        }
        return numStrategic;
    }

    unsigned int Game::getNumResources() const
    {
        unsigned int numResources = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Resource *resources = dynamic_cast<Resource *>(*it);
            if (resources) numResources++;
        }
        return numResources;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[y + (x * __width)] == nullptr)
            throw PositionEmptyEx(x, y);

        return __grid[y + (x * __width)];
    }

    // grid population methods
    void Game::addSimple(const Position &position)
    {
        int as = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[as] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy) // used for testing only
    {
        int as = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[as] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned x, unsigned y)
    {
        int as = y + (x * __width);

        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        __grid[as] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        int as = y + (x * __width);

        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        __grid[as] = new Simple(*this, Position(x, y), energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s)
    {
        int as = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[as] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        int as = y + (x * __width);

        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[as])
            throw PositionNonemptyEx(x, y);

        __grid[as] = new Strategic(*this, Position(x, y), STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &position)
    {
        int af = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[af] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y)
    {

        int af = y + x * __width;

        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[af])
            throw PositionNonemptyEx(x, y);

        __grid[af] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position &position)
    {
        int aa = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[aa] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        int aa = y + (x * __width);

        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        __grid[aa] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings gs;

        for (int i = 0; i < 9; ++i)
             gs.array[i] = EMPTY;

        for (int j = -1; j <= 1; ++j)
        {
            for (int k = -1; k <= 1; ++k)
            {
                if (pos.x + j >= 0 && pos.x + j < __height && pos.y + k >= 0 && pos.y + k < __width)
                {
                    unsigned int index = pos.y + k + ((pos.x + j) * __width);

                    if (__grid[index])
                        gs.array[k + 1 + ((j + 1) * 3)] = __grid[index]->getType();
                }
                else
                    gs.array[k + 1 + ((j + 1) * 3)] = INACCESSIBLE;
            }
        }
        gs.array[4] = SELF;

        return gs;
    }

    // gameplay methods
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) // note: STAY by default
    {
        int x, y;

        x = to.x - from.x;
        y = to.y - from.y;
        x++;
        y++;

        unsigned int index = (y + (x * 3));

        switch (index)
        {
            case 0:
                return NW;
            case 1:
                return N;
            case 2:
                return NE;
            case 3:
                return W;
            case 4:
                return STAY;
            case 5:
                return E;
            case 6:
                return SW;
            case 7:
                return S;
            case 8:
                return SE;
            default:
                return STAY;
        }
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x, y;

        x = pos.x;
        y = pos.y;

        switch (ac)
        {
            case E:
                y++;
                break;
            case NE:
                y++;
                x--;
                break;
            case N:
                x--;
                break;
            case NW:
                y--;
                x--;
                break;
            case W:
                y--;
                break;
            case SW:
                y--;
                x++;
                break;
            case S:
                x++;
                break;
            case SE:
                x++;
                y++;
                break;
            default:
                break;
        }

        Position p((unsigned )x, (unsigned)y);

        if (p.x < __height && p.y < __width)
            return true;
        return false;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const // note: assumes legal, use with isLegal()
    {
        if (isLegal(ac, pos))
        {
            int x, y;
            x = pos.x;
            y = pos.y;

            switch (ac)
            {
                case E:
                    y++;
                    break;
                case NE:
                    y++;
                    x--;
                    break;
                case N:
                    x--;
                    break;
                case NW:
                    y--;
                    x--;
                    break;
                case W:
                    y--;
                    break;
                case SW:
                    y--;
                    x++;
                    break;
                case S:
                    x++;
                    break;
                case SE:
                    x++;
                    y++;
                    break;
                default:
                    break;
            }

            Position p((unsigned )x, (unsigned)y);

            return p;
        }
        return pos;
    }

    void Game::round()   // play a single round
    {
        std::set<Piece*> round;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            if (*it)
            {
                round.insert(round.end(), *it);
                (*it)->setTurned(false);
            }
        }

        for (auto item = round.begin(); item != round.end(); ++item)
        {
            if (!(*item)->getTurned())
            {
                (*item)->setTurned(true);
                (*item)->age();
                ActionType r = (*item)->takeTurn(getSurroundings((*item)->getPosition()));
                Position p1 = (*item)->getPosition();
                Position p2 = move(p1, r);
                if (p1.x != p2.x || p1.y != p2.y)
                {
                    Piece *r = __grid[p2.y + (p2.x * __width)];
                    if (r)
                    {
                        if ((*item)->getPosition().x != p1.x || (*item)->getPosition().y != p1.y)
                        {
                            __grid[p2.y + (p2.x * __width)] = (*item);
                            __grid[p1.y + (p1.x * __width)] = r;
                        }
                    }
                    else
                    {
                        (*item)->setPosition(p2);
                        __grid[p2.y + (p2.x * __width)] = (*item);
                        __grid[p1.y + (p1.x * __width)] = nullptr;
                    }
                }
            }
        }

        for (unsigned int i = 0; i < __grid.size(); ++i)
        {
            if (__grid[i] && !(__grid[i]->isViable()))
            {
                delete __grid[i];
                __grid[i] = nullptr;
            }
        }

        if (getNumResources() <= 0)
            __status = Status::OVER;
        ++__round;
    }

    void Game::play(bool verbose)    // play game until over
    {
        __verbose = verbose;
        __status = PLAYING;

        while (__status != OVER)
        {
            round();
            if (verbose) operator<<(std::cout, *this);
        }

    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.getRound() << std::endl;

        int i = 0;


        for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it)
        {
            if (*it == nullptr)
                os << "[     ]";

            else
                os << "[     ]";

            if (++i == game.__width)
            {
                i = 0;
                os << std::endl;
            }
        }
            os << "Status: " << game.getStatus() << std::endl;

            switch(game.__status) {
                case (0):
                    os << "Not Started";
                    break;
                case (1):
                    os << "Playing";
                    break;
                case (2):
                    os << "Over";
                    break;
        }
        return os;
    }

}