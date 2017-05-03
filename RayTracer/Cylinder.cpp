#include "Cylinder.h"

#include "utility.h"

Cylinder::Cylinder() : Object() {

}

Cylinder::Cylinder(const Cylinder& cylinder) : Object(cylinder) {

}

Cylinder::~Cylinder() {

}

const Cylinder& Cylinder::operator=(const Cylinder& cylinder) {
	if (this != &cylinder) {
		Object::operator=(cylinder);
	}
	return *this;
}

std::vector<RayIntersection> Cylinder::intersect(const Ray& ray) const {
	std::vector<RayIntersection> result;

	Ray inverseRay = transform.applyInverse(ray);
	Point inverseRayPXY = Point(inverseRay.point(0), inverseRay.point(0), 0);
	Direction inverseRayDXY = Direction(inverseRay.direction(0), inverseRay.direction(0), 0);

	double a = inverseRayDXY.squaredNorm();
	double b = 2*inverseRayDXY.dot(inverseRayPXY);
	double c = inverseRayPXY.squaredNorm() - 1;

	RayIntersection hit;
	hit.material = material;

	double b2_4ac = b*b - 4*a*c;
	double d;
	switch (sign(b2_4ac)) {
	case -1:
		// No intersections
		break;
	case 0:
		// One intersection
		d = -b/(2*a);
		if (d > 0) {
			// Intersection is in front of the ray's start point
			hit.point = transform.apply(Point(inverseRay.point + d*inverseRay.direction));
			hit.normal = transform.apply(Normal(inverseRay.point + d*inverseRay.direction));
			if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm() * sign(d);
			result.push_back(hit);
		}
		break;
	case 1:
		// Two intersections
		d = (-b + sqrt(b*b - 4*a*c))/(2*a);
		if (d > 0) {
			// Intersection is in front of the ray's start point
			hit.point = transform.apply(Point(inverseRay.point + d*inverseRay.direction));
			hit.normal = transform.apply(Normal(inverseRay.point + d*inverseRay.direction));
			if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm() * sign(d);
			result.push_back(hit);
		}
		break;
	default:
		// Shouldn't be possible, but just in case
		std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
		exit(-1);
		break;
	}
	
	return result;
}
