#include "Utils.h"

// Convert cartesian points to polar points
std::vector<PolarPoint> Utils::cartesianToPolar(const std::vector<sf::Vector2f>& pntCartesians) {
    auto hypotenuseOfPoint = [](const sf::Vector2f& pnt) -> double {
        return std::sqrt((pnt.x * pnt.x) + (pnt.y * pnt.y));
    };

    const double LARGEST_HYP = std::max_element(
                                   pntCartesians.begin(), pntCartesians.end(),
                                   [&](const sf::Vector2f& left, const sf::Vector2f& right) {
                                       return hypotenuseOfPoint(left) < hypotenuseOfPoint(right);
                                   }
                                   )->x;

    auto cartToPolarTransform = [&hypotenuseOfPoint, LARGEST_HYP](const sf::Vector2f& pnt) -> PolarPoint {
        float r = static_cast<float>(hypotenuseOfPoint(pnt) / LARGEST_HYP);
        float theta = static_cast<float>(std::atan2(pnt.y, pnt.x));
        return {r, theta};
    };

    std::vector<PolarPoint> polarPoints;
    polarPoints.reserve(pntCartesians.size());

    for (const auto& point : pntCartesians) {
        polarPoints.push_back(cartToPolarTransform(point));
    }

    return polarPoints;
}

// Convert degrees to radians
float Utils::my_qDegreesToRadians(float degrees) {
    return degrees * static_cast<float>(M_PI / 180.0);
}

// Calculate the Euclidean distance between two points
double Utils::my_getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    sf::Vector2f delta = point2 - point1;
    return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}



/**
#include "utils.h"
#include "qmath.h"

#include <QtAlgorithms>
#define M_PI       3.14159265358979323846   // pi



QVector<PolarPoint> Utils::cartesianToPolar(QVector<QPoint>  pntCartesians){
    auto hypotenuseOfPoint = [](QPoint const& pnt) -> double {
        return sqrt((pnt.x() * pnt.x()) + (pnt.y() * pnt.y()));
    };

    const double LARGEST_HYP = std::max_element(pntCartesians.constBegin(), pntCartesians.constEnd(),
                                                [&, hypotenuseOfPoint](const QPoint& left, const QPoint& right) {
           return hypotenuseOfPoint(left) < hypotenuseOfPoint(right);
       })->manhattanLength();

       
    auto cartToPolarTransform = [&hypotenuseOfPoint, &LARGEST_HYP](QPoint const& pnt) -> PolarPoint{
        double r = hypotenuseOfPoint(pnt) / LARGEST_HYP;
        double theta = atan2(pnt.y(), pnt.x());
        return {r, theta};
    };

    QVector<PolarPoint> polarPoints;
    for(auto& point : pntCartesians)
    {
        polarPoints.append(cartToPolarTransform(point));
    }

    return polarPoints;
}


float Utils::my_qDegreesToRadians(float degrees)
{
    return degrees * float(M_PI/180);
}

double Utils::my_getDistances(QPoint x, QPoint y)
{
    QPoint deltax = y - x;
     double trueLength = qSqrt(qPow(deltax.x(), 2) + qPow(deltax.y(), 2));
    return trueLength;
}
**/
