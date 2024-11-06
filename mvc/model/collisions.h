#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "Movable.h" 
class Collisions{
	std::shared_ptr<Movable> &obj1;
	std::shared_ptr<Movable> &obj2;
public:
	Collisions(std::shared_ptr<Movable> &obj1, std::shared_ptr<Movable> &obj2);
	bool intersect();
};
#endif