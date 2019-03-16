#include "Colors.h"

Tuple Colors::getRandomColor()
{
    static Colors *instance;
    if (instance == nullptr)
    {
        instance = new Colors();
    }
    return instance->pickRandom();
}

Colors::Colors()
{
    amount = 6;
    colors = new Tuple[amount];

    colors[0] = Tuple(1, 0, 0);
    colors[1] = Tuple(0, 1, 0);
    colors[2] = Tuple(0, 0, 1);
    colors[3] = Tuple(1, 0, 1);
    colors[4] = Tuple(1, 1, 0);
    colors[5] = Tuple(0, 1, 1);
}

Tuple Colors::pickRandom()
{
    return colors[rand() % amount];
}