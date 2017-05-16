#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include <memory.h>

#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transformation {
public:
	float rotateAng = 0.0f;
	glm::vec3 rotateDir = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	glm::mat4x4 transformMatrix = glm::mat4x4(1.0f);
	bool transformReady = false;
	bool rotateReady = false;

	void printInfo();
	glm::mat4x4 getTransformMatrix();
	glm::vec3 getTransformNormal(glm::vec3 normal);
	glm::vec3 transformPoint(glm::vec3 point);
	glm::vec3 transformVector(glm::vec3 vec);
	float getTransformedT(glm::vec3 origin, glm::vec3 dir, float t);
	void setRotation();
};