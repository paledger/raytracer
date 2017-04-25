#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "glm/glm.hpp"

class LightSource
{
public:
	void printInfo();

	glm::vec3 location = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);
};