#ifndef POLARPOINT_H
#define POLARPOINT_H

class PolarPoint {
public:
    // corresponds to the hypotenuse in Cartesian coordinates, number between 0 and 1
    float r;
    // degrees in radians, number between 0 and 6.283
    float theta;

    PolarPoint(float _r = 0.0f, float _theta = 0.0f);

    float getTheta() const { return theta; }
    float getR() const { return r; }
};

/**
#include <QPoint>

class PolarPoint {
public:
    // We use the wrapper-class Double as members to get the Comparable interface
    // because Asteroid needs to sort by theta when generating random-shapes.

    // corresponds to the hypotenuse in cartesean, number between 0 and 1
    qreal r;
    // degrees in radians, number between 0 and 6.283
    qreal theta;

    PolarPoint(qreal _r = 0, qreal _theta = 0);

    qreal getTheta() { return theta; }

    qreal getR() { return r; }

};
**/

#endif // POLARPOINT_H
