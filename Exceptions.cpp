//
// Created by Christopher Corona on 4/1/2016.
//

#include "Exceptions.h"

namespace Gaming
{

//    class GamingException {
//    protected:
//        std::string __name;

    void GamingException::setName(std::string name)
    {
        __name = name;
    }
    //public:

    std::ostream &operator<<(std::ostream &os, const GamingException &ex)
    {
        ex.__print_args(os);
        return os;
    }

//    class DimensionEx : public GamingException {
//    protected:
//        unsigned __exp_width, __exp_height, __width, __height;
//    public:
    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {
        setName("DimensionEx");
    }

    unsigned DimensionEx::getExpWidth() const {return __exp_width; }
    unsigned DimensionEx::getExpHeight() const {return __exp_height;}
    unsigned DimensionEx::getWidth() const {return __width;}
    unsigned DimensionEx::getHeight() const { return __height;}


    //class InsufficientDimensionsEx : public DimensionEx {
    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {

    }

    //public:
    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) : DimensionEx(minWidth, minHeight, width, height)
    {
        setName("InsufficientDimensionsEx");
    }

    //class OutOfBoundsEx : public DimensionEx {
    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {

    }

    //public:
    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height)
    {
        setName("OutofBoundsEx");
    }

    //class PositionEx : public GamingException {
    //private:
    //unsigned int __x, __y;

    //protected:
    void PositionEx::__print_args(std::ostream &os) const
    {

    }

    //public:
    PositionEx::PositionEx(unsigned x, unsigned y)
    {
        setName("PositionEx");
    }

    // to use in population methods
    //class PositionNonemptyEx : public PositionEx {
    //public:
    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y): PositionEx(x,y)
    {
        setName("PositionNonemptyEx");
    }

    // to use in Game Piece getter
    //class PositionEmptyEx : public PositionEx {
    //public:
    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y):PositionEx(x,y)
    {
        setName("PositionEmptyEx");
    }

    // to use with position randomizer
    //class PosVectorEmptyEx : public GamingException {
    //protected:
    void PosVectorEmptyEx::__print_args(std::ostream &os) const
    {

    }

    //public:
    PosVectorEmptyEx::PosVectorEmptyEx()
    {
        setName("PosVectorEmptyEx");
    }
}
