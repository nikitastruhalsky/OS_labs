#pragma once
#include "NumberStaticLibrary.h"
#include <cmath>


#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif // VECTOR_EXPORTS


class VECTOR_API Vector
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