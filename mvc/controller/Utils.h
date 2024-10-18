
#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

class Utils {
public:
    static int randomInt(int min, int max);
    static float distance(float x1, float y1, float x2, float y2);
};

#endif
