#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include <memory.h>

#include "glm/glm.hpp"
#include "Finish.h"


class Shape
{
public:
	virtual void printInfo();
	virtual std::vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& origin) = 0;
	virtual std::string getTypeString()  = 0;
	virtual glm::vec3 getNormal(glm::vec3 point) = 0;

	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	std::shared_ptr<Finish> finish = std::make_shared<Finish>();
};

