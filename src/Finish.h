#pragma once

#include <vector>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "glm/glm.hpp"

class Finish
{
public:
	glm::vec3 pigment = glm::vec3(0.0f, 0.0f, 0.0f);
	float finish = 0.0f;
	float ambient = 0.0f;
	float diffuse = 0.0f;
	float specular = 0.0f;
	float shininess = 0.7f;
	float metallic = 0.1f;
	float ior = 1.6f;
	float reflection = 0.0f;
	float refraction = 0.0f;
	float filter = 0.0f;

	void printInfo();
};
