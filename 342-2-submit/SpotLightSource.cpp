#include "SpotLightSource.h"

#include "utility.h"
#include <math.h>

SpotLightSource::SpotLightSource() :
LightSource(), direction(0,0,1), angle(45) {

}

SpotLightSource::SpotLightSource(const SpotLightSource& lightSource) :
LightSource(lightSource),  direction(lightSource.direction), angle(lightSource.angle) {

}

SpotLightSource::SpotLightSource(Direction d, double a) :
LightSource(), direction(d), angle(a) {

}


SpotLightSource::~SpotLightSource() {

}

const SpotLightSource& SpotLightSource::operator=(const SpotLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
	}
	return *this;
}

double SpotLightSource::getIntensityAt(const Point& point) const {
	Vector l = point - location;
	Vector d = direction / direction.norm();
	double distance = l.norm();

	if (distance < epsilon) distance = epsilon;
	double intensity = 1 / (distance*distance);

	l /= l.norm();
	return acos(l.dot(direction)) < angle * (M_PI / 180.0) ? intensity : 0;
}
