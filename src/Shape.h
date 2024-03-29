#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include <memory.h>

#include "glm/glm.hpp"
#include "Finish.h"
#include "Transformation.h"
#include "Flags.h"


class Shape
{
public:
	virtual void printInfo();
	virtual std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin) = 0;
	virtual std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags) = 0;
	virtual std::string getTypeString()  = 0;
	virtual glm::vec3 getNormal(glm::vec3 point) = 0;
	virtual glm::vec3 getCenter() = 0;
	virtual void createBounds(glm::vec3 &min, glm::vec3 &max) = 0;
	virtual std::shared_ptr<Finish> getFinish() = 0;
	std::shared_ptr<Transformation> getTransformation();

	std::shared_ptr<Finish> finish = std::make_shared<Finish>();
	std::shared_ptr<Transformation> transform = std::make_shared<Transformation>();
};

