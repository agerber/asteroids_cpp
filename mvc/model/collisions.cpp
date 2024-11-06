#include "collisions.h"

float CalculateDistance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
  float diffY = p1.y - p2.y;
  float diffX = p1.x - p2.x;
  return std::sqrt((diffY * diffY) + (diffX * diffX));
}


