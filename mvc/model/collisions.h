#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <cmath>

#include "Movable.h"
template <class A, class B>
class Collisions {
  A &obj1;
  B &obj2;

 public:
  Collisions(A &obj1, B &obj2);
  bool intersect();
};

bool approximatelyEqual(float a, float b, float epsilon);
bool essentiallyEqual(float a, float b, float epsilon);
bool definitelyGreaterThan(float a, float b, float epsilon);
bool definitelyLessThan(float a, float b, float epsilon);
float CalculateDistance(const sf::Vector2f &p1, const sf::Vector2f &p2);

template <class A, class B>
Collisions<A, B>::Collisions(A &obj1, B &obj2) : obj1{obj1}, obj2{obj2} {}

template <class A, class B>
bool Collisions<A, B>::intersect() {
  bool aprox = approximatelyEqual(
      CalculateDistance(obj1->getCenter(), obj2->getCenter()),
      std::abs(obj1->getRadius() + obj2->getRadius()),
      std::numeric_limits<float>::epsilon());
  bool less = definitelyLessThan(
      CalculateDistance(obj1->getCenter(), obj2->getCenter()),
      std::abs(obj1->getRadius() + obj2->getRadius()),
      std::numeric_limits<float>::epsilon());
  if (aprox || less) return true;

  return false;
}

#endif