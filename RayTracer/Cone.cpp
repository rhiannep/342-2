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

	Ray inverseRay = transform.applyInverse(ray);
	Ray rayXY = inverseRay;

	RayIntersection hit;

	/* base of cone. */
	double distanceToCap = (1 - inverseRay.point(2)) / inverseRay.direction(2);
	if(distanceToCap > 0) {
	if((Point(inverseRay.point + distanceToCap * inverseRay.direction) - Point(0, 0, 1)).norm() < 1) {
		hit.material = material;
		hit.point = transform.apply(Point(inverseRay.point + distanceToCap * inverseRay.direction));
		hit.normal = transform.apply(Normal(0, 0, 1));
		if (hit.normal.dot(ray.direction) > 0) {
			hit.normal = -hit.normal;
		}
		  hit.distance = (hit.point - ray.point).norm() * sign(distanceToCap);
		  result.push_back(hit);
	  }
  }

	/* Cone surface. */
	double a = inverseRay.direction.squaredNorm()-2*inverseRay.direction(2)*inverseRay.direction(2);
	double b = 2*inverseRay.direction.dot(inverseRay.point)-4*inverseRay.point(2)*inverseRay.direction(2);
	double c = inverseRay.point.squaredNorm()-2*inverseRay.point(2)*inverseRay.point(2);

	hit.material = material;
	Point potentialPoint;

	double b2_4ac = b*b - 4*a*c;
	double d;
	switch (sign(b2_4ac)) {
	case -1:
		// No intersections
		break;
	case 0:
		// One intersection
		d = -b/(2*a);
		potentialPoint = Point(inverseRay.point + d*inverseRay.direction);
		if (d > 0 && potentialPoint(2) < 1 && potentialPoint(2) > 0) {
			hit.point = transform.apply(potentialPoint);
			Normal normal = 2 * Normal(potentialPoint);
			normal -= Normal(0, 0, 4 * potentialPoint(2));
			normal /= normal.norm();
			hit.normal = transform.apply(normal);
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
		potentialPoint = Point(inverseRay.point + d*inverseRay.direction);
		if (d > 0 && potentialPoint(2) < 1 && potentialPoint(2) > 0) {
			hit.point = transform.apply(potentialPoint);
			hit.point = transform.apply(potentialPoint);
			Normal normal = 2 * Normal(potentialPoint);
			normal -= Normal(0, 0, 4 * potentialPoint(2));
			normal /= normal.norm();
			hit.normal = transform.apply(normal);
			if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm() * sign(d);
			result.push_back(hit);
		}

		d = (-b - sqrt(b*b - 4*a*c))/(2*a);
		potentialPoint = Point(inverseRay.point + d*inverseRay.direction);
		if (d > 0 && potentialPoint(2) < 1 && potentialPoint(2) > 0) {
			hit.point = transform.apply(potentialPoint);
			hit.point = transform.apply(potentialPoint);
			Normal normal = 2 * Normal(potentialPoint);
			normal -= Normal(0, 0, 4 * potentialPoint(2));
			normal /= normal.norm();
			hit.normal = transform.apply(normal);
			if (hit.normal.dot(ray.direction) > 0) {
				hit.normal = -hit.normal;
			}
			hit.distance = (hit.point - ray.point).norm() * sign(d);
			result.push_back(hit);
		}
		break;
	default:
		std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
		exit(-1);
		break;
	}
	return result;
}
