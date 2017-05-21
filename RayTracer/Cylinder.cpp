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

	Ray rayXY = inverseRay; // Ray in the X Y plane, z component is 0.
	rayXY.direction(2) = 0;
	rayXY.point(2) = 0;

	RayIntersection hit;

	/* Cap 1. */
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

	/* Cap 2. */
  distanceToCap = (-1 - inverseRay.point(2)) / inverseRay.direction(2);
	if(distanceToCap > 0) {
    if((Point(inverseRay.point + distanceToCap * inverseRay.direction) - Point(0, 0, -1)).norm() < 1) {
	    hit.material = material;
	    hit.point = transform.apply(Point(inverseRay.point + distanceToCap * inverseRay.direction));
	    hit.normal = transform.apply(Normal(0, 0, -1));
	    if(hit.normal.dot(ray.direction) > 0) {
		    hit.normal = -hit.normal;
	    }
	  hit.distance = (hit.point - ray.point).norm() * sign(distanceToCap);
	  result.push_back(hit);
    }
  }

	/* Barrel part. */
	double a = rayXY.direction.squaredNorm();
	double b = 2*rayXY.direction.dot(rayXY.point);
	double c = rayXY.point.squaredNorm() - 1;

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
		if (d > 0 && potentialPoint(2) < 1 && potentialPoint(2) > -1) {
			// Check the potential hit is in the range we want
			hit.point = transform.apply(potentialPoint);

			Normal normal = Normal(potentialPoint - Point(0, 0, potentialPoint(2)));
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
		if (d > 0 && potentialPoint(2) < 1 && potentialPoint(2) > -1) {
			// Check the potential hit is in the range we want
			hit.point = transform.apply(potentialPoint);

			Normal normal = Normal(potentialPoint - Point(0, 0, potentialPoint(2)));
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
		if (d > 0 && potentialPoint(2) < 1 && potentialPoint(2) > -1) {
			// Intersection is in front of the ray's start point
			hit.point = transform.apply(potentialPoint);

			Normal normal = Normal(potentialPoint - Point(0, 0, potentialPoint(2)));
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
		// Shouldn't be possible, but just in case
		std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
		exit(-1);
		break;
	}
	return result;
}
