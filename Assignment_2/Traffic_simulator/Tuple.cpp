#include "Tuple.h"
using namespace std;

Tuple::Tuple()
{
    x = y = z = 0;
}

Tuple::Tuple(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}

Tuple& Tuple::operator + (Tuple& right)
{
    x += right.x;
    y += right.y;
    z += right.z;

    return *this;
}