#pragma once

#include "Shape.h"

#include <vector>
#include <memory>
#include <memory.h>
#include "glm/glm.hpp"

class Intersection {
public: 
	Intersection() {}

	Intersection(std::shared_ptr<Shape> inShape, float t) {
		this->shape = inShape;
		this->t = t;
	}

	void setTransformedInfo(glm::vec3 origin, glm::vec3 viewRay);

	/* basic information */
	std::shared_ptr<Shape> shape;
	float t;

	/* other transformable info */
	glm::vec3 oRay, tRay;
	glm::vec3 oOrigin, tOrigin;
	glm::vec3 oPt, wPt;
	glm::vec3 n;
};