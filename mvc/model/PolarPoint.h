#ifndef POLARPOINT_H
#define POLARPOINT_H

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

#endif // POLARPOINT_H