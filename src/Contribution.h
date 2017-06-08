#pragma once


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "Shape.h"
#include "Intersection.h"
#include "Flags.h"
#include "Shading.h"

#include "glm/glm.hpp"


class Contribution {
public: 
	Contribution(std::shared_ptr<Intersection> intersect, Flags flags) {
		std::shared_ptr<Shape> shape = intersect->shape;
		float filter = shape->finish->filter;
		float reflection = shape->finish->reflection;
		float ior = shape->finish->ior;

		glm::vec3 n = intersect->n;
		glm::vec3 tRay = intersect->tRay;

		this->local = (1 - filter) * (1 - reflection);
		
		if (flags.fresnel) {
			float fresnel_reflectance = Shading::getSchlickApproximation(n, ior, tRay);
			this->reflection = (1 - filter) * reflection * fresnel_reflectance;
			this->refraction = filter * (1 - fresnel_reflectance);
			if (flags.test) {
				std::cout << "fresnel " << fresnel_reflectance << std::endl;
			}
		}
		else {
			reflection = (1 - filter) * reflection;
			refraction = filter;
		}
	}

	float local;
	float reflection;
	float refraction;
};