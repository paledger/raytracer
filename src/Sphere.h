#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "glm/glm.hpp"
#include "Shape.h"


class Sphere : public Shape
{
public:
	void printInfo() override;
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& camLoc) override;
	std::string getTypeString() override;

	glm::vec3 center = glm::vec3(0.0, 0.0, 0.0);
	float radius = 1;

};

