#pragma once

#include <vector>
#include <memory>
#include <math.h>
#include <algorithm>

#include "glm/glm.hpp"

#include "Transformation.h"
#include "Shape.h"
#include "Flags.h"

class Helper {
public:
	static std::vector<float> quadratic(float a, float b, float c);
	static int convertToRgb(float flt);
	static glm::vec3 convertToRgb(glm::vec3 vec);
	static glm::vec3 getPointOnRay(glm::vec3 origin, glm::vec3 direction, float t);
	static glm::vec3 getPointOnRay(const std::shared_ptr<Transformation> transform, glm::vec3 origin, glm::vec3 direction, float t);
	static glm::vec3 getReverseVec(glm::vec3 vec);
	static float calculateFirstHit(glm::vec3 origin, glm::vec3 rayDirection, const std::shared_ptr<Shape>& shapeToTest, Flags flags);
	static float calculateLastHit(glm::vec3 origin, glm::vec3 rayDirection, const std::shared_ptr<Shape>& shapeToTest, Flags flags);

};