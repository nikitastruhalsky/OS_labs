#include "NumberStaticLibrary.h"


namespace NumberStaticLibrary
{
    Number operator+(Number a, Number b)
    {
        return a.number + b.number;
    }
    Number Number::Add(Number a, Number b)
    {
        return a + b;
    }


    Number operator-(Number a, Number b)
    {
        return a.number - b.number;
    }
    Number Number::Subtract(Number a, Number b)
    {
        return a - b;
    }


    Number operator*(Number a, Number b)
    {
        return a.number * b.number;
    }
    Number Number::Multiply(Number a, Number b)
    {
        return a * b;
    }


    Number operator/(Number a, Number b)
    {
        return a.number / b.number;
    }
    Number Number::Divide(Number a, Number b)
    {
        return a / b;
    }
}
