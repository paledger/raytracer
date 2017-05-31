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
#include "glm/gtc/constants.hpp"

class Transformation {
public:
	glm::mat4x4 transformMatrix = glm::mat4x4(1.0f);

	void printInfo();
	glm::mat4x4 getTransformMatrix();
	void applyRotation(glm::vec3 vec);
	void applyScale(glm::vec3 vec);
	void applyTranslation(glm::vec3 vec);
	glm::vec3 transformNormal(glm::vec3 normal);
	glm::vec3 transformPoint(glm::vec3 point);
	glm::vec3 transformPointbyModel(glm::vec3 point);
	glm::vec3 transformVector(glm::vec3 vec);
	float getTransformedT(glm::vec3 origin, glm::vec3 dir, float t);
	void setRotation(glm::vec3 rotationVec, float& angle, glm::vec3& dir);
};