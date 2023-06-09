#include "Asteroid.h"
#include "Game.h"  //include necessary header files
#include <cmath>
#include "Global.h"
#include <PolarPoint.h>


//constructor
Asteroid::Asteroid(int size) {
    //a size of zero is a big asteroid
    //a size of 1 or 2 is med or small asteroid respectively. See getSize() method.
    if (size == 0) setRadius(LARGE_RADIUS);
    else setRadius(LARGE_RADIUS/(size * 2));

    //Asteroid is FOE
    setTeam(Movable::FOE);
    setColor(MY_WHITE_COLOR);

    //the spin will be either plus or minus 0-9
    setSpin(somePosNegValue(10));
    //random delta-x
    setDeltaX(somePosNegValue(10));
    //random delta-y
    setDeltaY(somePosNegValue(10));

    setCartesians(generateVertices());

}

//overloaded constructor, so we can spawn smaller asteroids from an exploding one
Asteroid::Asteroid(Asteroid & astExploded)
    :Asteroid(astExploded.getSize() + 1)
{
    //calls the other constructor: Asteroid(int size)
    setCenter(astExploded.getCenter());
    int newSmallerSize = astExploded.getSize() + 1;
    //random delta-x : inertia + the smaller the asteroid, the faster its possible speed
    setDeltaX(astExploded.getDeltaX() / 1.5 + somePosNegValue( 5 + newSmallerSize * 2));
    //random delta-y : inertia + the smaller the asteroid, the faster its possible speed
    setDeltaY(astExploded.getDeltaY() / 1.5 + somePosNegValue( 5 + newSmallerSize * 2));

}

//converts the radius to integer representing the size of the Asteroid:
    //0 = large, 1 = medium, 2 = small

int Asteroid::getSize(){

    if (getRadius() == LARGE_RADIUS) {
            return 0;
    }
    else if (getRadius() == LARGE_RADIUS / 2) {
            return 1;
    }
    else if (getRadius() == LARGE_RADIUS / 4) {
        return 2;
    }
    return 0;
}



QVector<QPoint> Asteroid::generateVertices(){

    //6.283 is the max radians
    auto const MAX_RADIANS_X1000 =6283;

    constexpr double PRECISION = 100.0;

    auto polarPointSupplier = []() {
        double r = (800 + QRandomGenerator::global()->bounded(200)) / 1000.0; //number between 0.8 and 0.999
        double theta = QRandomGenerator::global()->bounded(MAX_RADIANS_X1000) / 1000.0; // number between 0 and 6.282
        return PolarPoint(r, theta);
    };

    auto polarToCartesian = [](auto & pp) {
            int x = static_cast<int>(pp.getR() * PRECISION * sin(pp.getTheta()));
            int y = static_cast<int>(pp.getR() * PRECISION * cos(pp.getTheta()));
            return QPoint(x, y);
    };

   //random number of vertices
   auto const VERTICES = QRandomGenerator::global()->bounded(7) + 25;
   std::vector<PolarPoint> polarPoints(VERTICES);

   std::generate(begin(polarPoints), end(polarPoints), polarPointSupplier);

   //sort by ascending theta value
   std::sort(begin(polarPoints), end(polarPoints),
            [](PolarPoint & p1, PolarPoint & p2){
                return p1.getTheta() < p2.getTheta();
    });

    //conversion from polar to Cartesian points.
    QVector<QPoint> cartesianPoints(VERTICES);
    std::transform(begin(polarPoints), end(polarPoints),
                    cartesianPoints.begin(), polarToCartesian);

    //todo: this method should use streams similar to the reference Java app
    return cartesianPoints;
}

void Asteroid::draw(QPainter &painter) {
    renderVector(painter);
}
