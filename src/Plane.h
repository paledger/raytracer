#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "glm/glm.hpp"
#include "Shape.h"
#include "Transformation.h"


class Plane : public Shape
{
public:
	void printInfo() override;
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin) override;
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags) override;
	std::string getTypeString() override;
	glm::vec3 getNormal(glm::vec3 point) override;
	glm::vec3 getCenter() override;
	void createBounds(glm::vec3 &min, glm::vec3 &max) override;
	std::shared_ptr<Finish> getFinish() override;

	glm::vec3 normal = glm::vec3(0.0, 0.0, 0.0);
	float distance = 0;
};
