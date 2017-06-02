#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "glm/glm.hpp"
#include "Shape.h"
#include "Transformation.h"


class Box : public Shape
{
public:
	void printInfo() override;
	std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin) override;
	std::string getTypeString() override;
	glm::vec3 getNormal(glm::vec3 point) override;
	glm::vec3 getCenter() override;
	void createBounds(glm::vec3 &min, glm::vec3 &max) override;

	glm::vec3 min = glm::vec3(0.0f);
	glm::vec3 max = glm::vec3(0.0f);

private: 
	bool isParallelAndNoIntersect(const glm::vec3 origin, const glm::vec3 dir, const int dim);
	void changeTgminForDimension(int dim,
		const glm::vec3 origin, const glm::vec3 dir,
		float &tgmin, float &tgmax);
	int matchDimensionMax(glm::vec3 point);
	int matchDimensionMin(glm::vec3 point);

};

