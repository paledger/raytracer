#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "glm/glm.hpp"
#include "Shape.h"
#include "Transformation.h"
#include "BooleanOperator.h"

class Union : public BooleanOperator
{
public:
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin) override;
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags) override;
	std::string getTypeString();
	glm::vec3 getNormal(glm::vec3 point);
	glm::vec3 getCenter();
	void createBounds(glm::vec3 &min, glm::vec3 &max);
};
