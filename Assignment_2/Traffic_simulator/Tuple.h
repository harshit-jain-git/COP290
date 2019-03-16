#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include <iostream>

class Tuple
{
public:
    Tuple();
    Tuple(float a, float b, float c);

    float x, y, z;

    Tuple& operator + (Tuple& right); 
    Tuple& operator = (Tuple& right);
}

