#ifndef NUMBER1_LIBRARY_H
#define NUMBER1_LIBRARY_H

#pragma once


namespace NumberStaticLibrary
{
    class Number
    {
    public:

        double number;

        Number(double value)
        {
            this->number = value;
        }

        Number() = default;

        static Number Add(Number a, Number b);

        static Number Subtract(Number a, Number b);

        static Number Multiply(Number a, Number b);

        static Number Divide(Number a, Number b);
    };

    const Number one(1);
    const Number zero(0);
}

#endif //NUMBER1_LIBRARY_H
