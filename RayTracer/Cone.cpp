/* $Rev: 250 $ */
#include "Cone.h"

#include "utility.h"

Cone::Cone() : Object() {

}

Cone::Cone(const Cone& cone) : Object(cone) {

}

Cone::~Cone() {

}

const Cone& Cone::operator=(const Cone& cone) {
	if (this != &cone) {
		Object::operator=(cone);
	}
	return *this;
}

std::vector<RayIntersection> Cone::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	// Code to compute ray-cone intersections goes here.

	return result;
}
