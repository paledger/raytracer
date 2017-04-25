#pragma once

#include <vector>
#include <memory>
#include <math.h>

#include "glm/glm.hpp"


class Helper {
public:
	static std::vector<float> quadratic(float a, float b, float c);
	static int convertToRgb(float flt);
};