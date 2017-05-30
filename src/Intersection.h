#pragma once

#include "Shape.h"

#include <vector>
#include <memory>
#include <memory.h>

class Intersection {
public: 
	Intersection() {}

	Intersection(std::shared_ptr<Shape> inShape, float t) {
		this->shape = inShape;
		this->t = t;
	}

	std::shared_ptr<Shape> shape;
	float t;
};