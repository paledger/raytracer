#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "Shape.h"
#include "Transformation.h"
#include "Helper.h"
#include "glm/glm.hpp"

class Triangle: public Shape
{
public:
	void printInfo() override;
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin) override;
	std::string getTypeString() override;
	glm::vec3 getNormal(glm::vec3 point) override;

	glm::vec3 a;
	glm::vec3 b; 
	glm::vec3 c;
};