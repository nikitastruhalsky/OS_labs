#include <iostream>
#include "vect_library.h"
#include "numb_library.h"


int main()
{
    NumberStaticLibrary::Number one = NumberStaticLibrary::one;
    NumberStaticLibrary::Number zero = NumberStaticLibrary::zero;
    NumberStaticLibrary::Number a(5.6);
    NumberStaticLibrary::Number b(2);
    NumberStaticLibrary::Number c = NumberStaticLibrary::Number::Add(a, b);
    NumberStaticLibrary::Number d = NumberStaticLibrary::Number::Multiply(a, b);
    NumberStaticLibrary::Number e = NumberStaticLibrary::Number::Subtract(a, b);
    NumberStaticLibrary::Number f = NumberStaticLibrary::Number::Divide(a, b);
    std::cout << c.number << " " << d.number << " " << e.number << " " << f.number << " " << one.number << " " << zero.number << std::endl;


    Vector vector1(a, b);
    Vector vector2(c, e);
    std::cout << vector1.getAngle().number << " " << vector2.getRagius().number << " " << (vector1 + vector2).getRagius().number << std::endl;
    return 0;
}
