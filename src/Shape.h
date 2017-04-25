#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "glm/glm.hpp"


class Shape
{
public:
	virtual void Shape::printInfo();
	virtual std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& camLoc) = 0;
	virtual std::string getTypeString()  = 0;

	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 pigment = glm::vec3(0.0, 0.0, 0.0);
	float ambient;
	float diffuse;
};

