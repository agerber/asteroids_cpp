#ifndef UTILS_H
#define UTILS_H

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
#endif // UTILS_H