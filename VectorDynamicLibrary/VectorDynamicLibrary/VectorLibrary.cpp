#include "pch.h"
#include "VectorLibrary.h"
#include <cmath>

Vector::Vector(NumberStaticLibrary::Number x_, NumberStaticLibrary::Number y_)
{
	this->x = x_;
	this->y = y_;
}

NumberStaticLibrary::Number Vector::getRagius()
{
	double r = sqrt(x.number * x.number + y.number * y.number);
	NumberStaticLibrary::Number radius(r);
	return radius;
}

NumberStaticLibrary::Number Vector::getAngle()
{
	double value = atan(y.number / x.number);
	NumberStaticLibrary::Number angle(value);
	return angle;
}

Vector Vector::operator+(Vector vector)
{
	double x_value = this->x.number + vector.x.number;
	NumberStaticLibrary::Number x(x_value);
	double y_value = this->y.number + vector.y.number;
	NumberStaticLibrary::Number y(y_value);
	return Vector(x_value, y_value);
}