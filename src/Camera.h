#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "glm/glm.hpp"

class Camera
{
public:
	void printInfo();

	glm::vec3 location;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 look_at;
};