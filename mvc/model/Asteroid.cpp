#include "Asteroid.h"

#include "Game.h"

void Asteroid::setSize(int size) {
  // Size determines if the asteroid is large, medium, or small
  if (size == 0)
    setRadius(LARGE_RADIUS);  // Large asteroid
  else
    setRadius(LARGE_RADIUS / (size * 2));  // Medium or small asteroid
}

Asteroid::Asteroid(int size) {
  setSize(size);

  // Set as FOE
  setTeam(Team::FOE);
  setColor(sf::Color::White);

  // Set random spin and deltas
  setSpin(somePosNegValue(10));
  setDeltaX(somePosNegValue(10));
  setDeltaY(somePosNegValue(10));

  // Generate cartesian points representing vertices
  std::vector<sf::Vector2f> vertices = generateVertices();
  setCartesians(vertices);

  //setCenter(sf::Vector2f{150.0f, 150.0f});
                          
}

Asteroid::Asteroid(const Asteroid& astExploded)
    : Asteroid(astExploded.getSize() + 1) {
  
  setCenter(astExploded.getCenter());
  
  int newSmallerSize = astExploded.getSize() + 1;
  
  // Adjust speed based on the size of the new smaller asteroid
  double delta_x =
      astExploded.getDeltaX() / 1.5 + somePosNegValue(5 + newSmallerSize * 2);
  double delta_y =
      astExploded.getDeltaY() / 1.5 + somePosNegValue(5 + newSmallerSize * 2);
  setDeltaX(delta_x);
  setDeltaY(delta_y);
 
}

int Asteroid::getSize() const {
  if (getRadius() == LARGE_RADIUS) {
    return 0;
  } else if (getRadius() == LARGE_RADIUS / 2) {
    return 1;
  }
  return 2;
}

std::vector<sf::Vector2f> Asteroid::generateVertices() {
  const int MAX_RADIANS_X1000 = 6283;
  //const double PRECISION = 100.0

  // Lambda to generate random polar points
  auto polarPointSupplier = []() -> PolarPoint {
    double r = (800 + Game::nextInt(200)) /
               1000.0;  // Random value between 0.8 and 0.999
    double theta = Game::nextInt(MAX_RADIANS_X1000) /
                   1000.0;  // Random value between 0 and 6.283
    return PolarPoint(r, theta);
  };

  // Lambda to convert polar to cartesian
  auto polarToCartesian = [this](const PolarPoint& pp) -> sf::Vector2f {
    auto x = pp.getR() * getRadius() * std::sin(pp.getTheta());
    auto y = pp.getR() * getRadius() * std::cos(pp.getTheta());
    return sf::Vector2f(x, y);
  };

  // Generate a random number of vertices
  int VERTICES = Game::nextInt(7) + 25;

  // Generate, sort, and convert polar points to cartesian coordinates
  std::vector<PolarPoint> polarPoints;
  for (int i = 0; i < VERTICES; ++i) {
    polarPoints.push_back(polarPointSupplier());
  }

  // Sort by ascending theta values
  std::sort(polarPoints.begin(), polarPoints.end(),
            [](const PolarPoint& pp1, const PolarPoint& pp2) {
              return pp1.getTheta() < pp2.getTheta();
            });

  // Convert to cartesian points
  std::vector<sf::Vector2f> cartesianPoints;
  std::transform(polarPoints.begin(), polarPoints.end(),
                 std::back_inserter(cartesianPoints), polarToCartesian);

  return cartesianPoints;
}

void Asteroid::draw(sf::RenderWindow& window) { renderVector(window); }
