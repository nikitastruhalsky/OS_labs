#ifndef VECTOR_LIBRARY_H
#define VECTOR_LIBRARY_H

#pragma once
#include "numb_library.h"
#include <cmath>


class Vector
{
private:
    NumberStaticLibrary::Number x, y;

public:
    Vector(NumberStaticLibrary::Number, NumberStaticLibrary::Number);

    NumberStaticLibrary::Number getRagius();
    NumberStaticLibrary::Number getAngle();

    Vector operator+(Vector);
};

const Vector ZERO(NumberStaticLibrary::zero, NumberStaticLibrary::zero);
const Vector ONE(NumberStaticLibrary::one, NumberStaticLibrary::one);

#endif //VECTOR_LIBRARY_H
