#include "utils.h"
#include "qmath.h"

#include <QtAlgorithms>
#define M_PI       3.14159265358979323846   // pi
/*
PolarPoint::PolarPoint(double r_in, double theta_in)
{
    r = r_in;
    theta = theta_in;
}

*/


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
        double theta = atan2(pnt.y(), pnt.x())/* * 180 / M_PI*/;
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
