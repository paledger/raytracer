#pragma once
#include "glm/glm.hpp"

class Finish
{
public:
	glm::vec3 pigment = glm::vec3(0.0, 0.0, 0.0);
	float ambient = 0.0f;
	float diffuse = 0.0f;
	float specular = 0.0f;
	float shininess = 0.1f;
	float metallic = 0.1f;
	float ior = 1.6f;
	float reflection = 0.0f;
};
