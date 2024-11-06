#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <cmath>
#include "Movable.h" 
template <class A, class B>
class Collisions{
	A &obj1;
	B &obj2;
public:
	Collisions(A &obj1, B &obj2);
	bool intersect();
};

float CalculateDistance(const sf::Vector2f& p1, const sf::Vector2f& p2);
template <class A, class B>
Collisions<A,B>::Collisions(A &obj1, B& obj2) : obj1{obj1}, obj2{obj2} {}

template <class A, class B>
bool Collisions<A,B>::intersect() {
  if (CalculateDistance(obj1->getCenter(), obj2->getCenter()) <=
      std::abs(obj1->getRadius() + obj2->getRadius()))
    return true;

  return false;
}

#endif