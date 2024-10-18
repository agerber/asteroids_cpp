#include "Asteroid.h"
#include "Game.h"

Asteroid::Asteroid(const Asteroid &astExploded)
{
    int newSize = astExploded.getSize() + 1;
    *this = Asteroid(newSize);
    setCenter(astExploded.getCenter());

    // Adjust speed based on the size of the new smaller asteroid
    setDeltaX(astExploded.getDeltaX() / 1.5 + somePosNegValue(5 + newSize * 2));
    setDeltaY(astExploded.getDeltaY() / 1.5 + somePosNegValue(5 + newSize * 2));
}

std::vector<sf::Vector2f> Asteroid::generateVertices()
{
    const int MAX_RADIANS_X1000 = 6283;
    const double PRECISION = 100.0;

    // Lambda to generate random polar points
    auto polarPointSupplier = []() -> PolarPoint {
        double r = (800 + Game::R.nextInt(200)) / 1000.0;
        double theta = Game::R.nextInt(MAX_RADIANS_X1000) / 1000.0;
        return PolarPoint(r, theta);
    };

    // Lambda to convert polar to cartesian
    auto polarToCartesian = [](const PolarPoint& pp) -> sf::Vector2f {
        return sf::Vector2f(
            static_cast<float>(pp.getR() * 100.0 * std::sin(pp.getTheta())),
            static_cast<float>(pp.getR() * 100.0 * std::cos(pp.getTheta()))
            );
    };

    // Generate a random number of vertices
    int VERTICES = Game::R.nextInt(7) + 25;

    // Generate, sort, and convert polar points to cartesian coordinates
    std::vector<PolarPoint> polarPoints;
    for (int i = 0; i < VERTICES; ++i) {
        polarPoints.push_back(polarPointSupplier());
    }

    std::sort(polarPoints.begin(), polarPoints.end(), [](const PolarPoint& pp1, const PolarPoint& pp2) {
        return pp1.getTheta() < pp2.getTheta();
    });

    // Convert to cartesian and return
    std::vector<sf::Vector2f> cartesianPoints;
    std::transform(polarPoints.begin(), polarPoints.end(), std::back_inserter(cartesianPoints), polarToCartesian);

    return cartesianPoints;
}
