#include "collisions.h"

#include <cmath>

float CalculateDistance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
  float diffY = p1.y - p2.y;
  float diffX = p1.x - p2.x;
  return std::sqrt((diffY * diffY) + (diffX * diffX));
}

Collisions::Collisions(std::shared_ptr<Movable>& obj1,
                       std::shared_ptr<Movable>& obj2)
    : obj1{obj1}, obj2{obj2} {}

bool Collisions::intersect() {
  if (CalculateDistance(obj1->getCenter(), obj2->getCenter()) <=
      std::abs(obj1->getRadius() + obj2->getRadius()))
    return true;

  return false;
}
