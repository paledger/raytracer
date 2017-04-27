#include "Helper.h"

using namespace std;

/* PUBLIC */

vector<float> Helper::quadratic(float a, float b, float c) {
	vector<float> t;
	float discriminant = b*b - 4 * a*c;
	if (discriminant >= 0) {
		float pos = (-b + float(sqrt(discriminant))) / (2 * a);
		t.push_back(pos);
		if (discriminant > 0) {
			float neg = (-b - float(sqrt(discriminant))) / (2 * a);
			t.push_back(neg);
		}
	}
	return t;
}

int Helper::convertToRgb(float flt) {
	return (unsigned int)std::round(glm::min(flt, 1.0f) * 255.f);
}

glm::vec3 Helper::convertToRgb(glm::vec3 vec) {
	return glm::vec3(Helper::convertToRgb(vec[0]), 
		Helper::convertToRgb(vec[1]), 
		Helper::convertToRgb(vec[2]));
}

glm::vec3 Helper::getPointOnRay(glm::vec3 origin, glm::vec3 direction, float t) {
	return origin + t*direction;
}

glm::vec3 Helper::getReverseVec(glm::vec3 vec) {
	return -1.0f * vec;
}
