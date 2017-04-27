#pragma once

#include <vector>
#include <memory>
#include <math.h>

#include "glm/glm.hpp"


class Helper {
public:
	static std::vector<float> quadratic(float a, float b, float c);
	static int convertToRgb(float flt);
	static glm::vec3 convertToRgb(glm::vec3 vec);
	static glm::vec3 getPointOnRay(glm::vec3 origin, glm::vec3 direction, float t);
	static glm::vec3 getReverseVec(glm::vec3 vec);
};