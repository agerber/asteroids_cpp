#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>
#include <algorithm>
#include "PolarPoint.h"
#include <SFML/System/Vector2.hpp>

class Utils {
public:
    Utils() = default;

    static std::vector<PolarPoint> cartesianToPolar(const std::vector<sf::Vector2f>& pntCartesians);

    static float my_qDegreesToRadians(float degrees);

    static double my_getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);
};
/**
#include <QObject>
#include <QVector>
#include <QPointF>
#include "PolarPoint.h"

class Utils
{
public:
    Utils() {};

    static QVector<PolarPoint> cartesianToPolar(QVector<QPoint> pntCartesians);

    static  float my_qDegreesToRadians(float degrees);

    static  double my_getDistances(QPoint x, QPoint y);
};
**/



#endif // UTILS_H
