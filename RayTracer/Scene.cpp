#include "Scene.h"

#include "Colour.h"
#include "Display.h"
#include "utility.h"

Scene::Scene() : backgroundColour(0,0,0), ambientLight(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	Display display("Render", renderWidth, renderHeight, Colour(128,128,128));

	std::cout << "Rendering a scene with " << objects_.size() << " objects" << std::endl;

	double halfPixel = 2.0/(2*renderWidth);

	for (unsigned int y = 0; y < renderHeight; ++y) {
		for (unsigned int x = 0; x < renderWidth; ++x) {
			double cx = (x - 0.5*renderWidth)*2.0/renderWidth + halfPixel;
			double cy = (y - 0.5*renderHeight)*2.0/renderWidth + halfPixel;
			Ray ray = camera_->castRay(cx,cy);
			display.set(x, y, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}
	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;
	for (auto& obj : objects_) {
		std::vector<RayIntersection> hits = obj->intersect(ray);
		for (auto& hit : hits) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}
	for (auto& obj: objects_) {
		auto hits = obj->intersect(ray);
	}
	return firstHit;
}

Colour Scene::computeColour(const Ray& viewRay, unsigned int rayDepth) const {
	/* Base case for reflection. */
	if(rayDepth == 0) return Colour(0, 0, 0);

	RayIntersection hitPoint = intersect(viewRay);
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}

	Vector n = hitPoint.normal / hitPoint.normal.norm();
	Vector v = -viewRay.direction;
	v /= v.norm();

	Colour materialColour = Colour(0, 0, 0);

	/* For each light, find it's contribution to the hit point's colour and
	add it to material colour. */
	for (auto light: lights_) {
		double intensity = light->getIntensityAt(hitPoint.point);

		/* Check if there is something in between the hitpoint and the light source. */
		Ray shadowRay;
		shadowRay.point = hitPoint.point;
		shadowRay.direction = light->location - hitPoint.point;
		shadowRay.direction /= shadowRay.direction.norm();
		if(intersect(shadowRay).distance > 0 && intersect(shadowRay).distance < 1) {
			intensity = 0;
		}

		/* Calculate diffuse component. */
		Vector l = light->location - hitPoint.point;
		l /= l.norm();
		double nl = n.dot(l);
		Colour diffuseColour = hitPoint.material.diffuseColour * nl;

		/* Calculate specular component. */
		Vector r = (2 * n * l.dot(n)) - l;
		r /= r.norm();
		double rDotVToTheN = pow(r.dot(v), hitPoint.material.specularExponent);
		Colour specularColour = hitPoint.material.specularColour * rDotVToTheN;

		/* Sum specular and diffuse, assume same intensity for each. */
		materialColour += intensity * light->colour * (diffuseColour + specularColour);
	}

	materialColour.clip();
	materialColour += ambientLight * hitPoint.material.ambientColour;

	/* Reflection */
	Colour white = Colour(1, 1, 1);
	Ray reflectedRay;
	reflectedRay.point = hitPoint.point;
	reflectedRay.direction = (2 * n * v.dot(n)) - v;
	reflectedRay.direction /= reflectedRay.direction.norm();
	Colour reflectedColour = computeColour(reflectedRay, rayDepth - 1);

	/* Final hit colour is the ambient light level plus part of the material
	   colour and part of the reflected colour. */
	Colour hitColour = hitPoint.material.mirrorColour * reflectedColour
	                   + (white - hitPoint.material.mirrorColour) * materialColour;

	hitColour.clip();
	return hitColour;
}

bool Scene::hasCamera() const {
	return bool(camera_);
}
