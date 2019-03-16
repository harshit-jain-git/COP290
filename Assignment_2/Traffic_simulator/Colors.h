#ifndef COLORS_H
#define COLORS_H

#include <cstdlib>
#include "Tuple.h"

class Colors
{
public:
    static Tuple getRandomColor();
    
    Tuple *colors;
    int amount;
    Colors();

    Tuple pickRandom();
};

#endif