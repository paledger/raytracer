#include "Helper.h"

using namespace std;

/* PUBLIC */

vector<float> Helper::quadratic(float a, float b, float c) {
	vector<float> t;
	float discriminant = b*b - 4.0f * a*c;
	if (discriminant >= 0) {
		float pos = (-b + float(sqrt(discriminant))) / (2 * a);
		t.push_back(pos);
		float neg = (-b - float(sqrt(discriminant))) / (2 * a);
		t.push_back(neg);
	}
	return t;
}

int Helper::convertToRgb(float flt) {
	return (unsigned int)std::round(glm::min(1.0f, flt) * 255.f);
}

glm::vec3 Helper::convertToRgb(glm::vec3 vec) {
	return glm::vec3(Helper::convertToRgb(vec[0]), 
		Helper::convertToRgb(vec[1]), 
		Helper::convertToRgb(vec[2]));
}

glm::vec3 Helper::getPointOnRay(glm::vec3 origin, glm::vec3 direction, float t) {
	return origin + t*direction;
}

glm::vec3 Helper::getPointOnRay(const shared_ptr<Transformation> transform, glm::vec3 origin, glm::vec3 direction, float t) {
	return transform->transformPoint(origin) + t*transform->transformVector(direction);
}

glm::vec3 Helper::getReverseVec(glm::vec3 vec) {
	return -1.0f * vec;
}

float Helper::calculateFirstHit(glm::vec3 origin,
	glm::vec3 rayDirection, const shared_ptr<Shape>& shapeToTest, Flags flags)
{
	vector<float> t;
	glm::vec3 tRay, tOrigin;
	if (flags.csgtest && 
		(shapeToTest->getTypeString() == "Difference" ||
		 shapeToTest->getTypeString() == "Intersection" ||
		 shapeToTest->getTypeString() == "Union"))
	{
		t = shapeToTest->getIntersection(rayDirection, origin, flags);
	}
	else {
		if (flags.transform && !(shapeToTest->getTypeString() == "Difference" ||
								 shapeToTest->getTypeString() == "Intersection" ||
								 shapeToTest->getTypeString() == "Union")) 
		{
			tRay = shapeToTest->transform->transformVector(rayDirection);
			tOrigin = shapeToTest->transform->transformPoint(origin);
		}
		else {
			tRay = rayDirection;
			tOrigin = origin;
		}
		t = shapeToTest->getIntersection(tRay, tOrigin);
	}
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[0];
	}
	return -1;
}

float Helper::calculateLastHit(glm::vec3 origin,
	glm::vec3 rayDirection, const shared_ptr<Shape>& shapeToTest, Flags flags)
{
	glm::vec3 tRay, tOrigin;
	if (flags.transform && !(shapeToTest->getTypeString() == "Difference" ||
		shapeToTest->getTypeString() == "Intersection"))
	{
		tRay = shapeToTest->transform->transformVector(rayDirection);
		tOrigin = shapeToTest->transform->transformPoint(origin);
	}
	else {
		tRay = rayDirection;
		tOrigin = origin;
	}
	vector<float> t = shapeToTest->getIntersection(tRay, tOrigin);
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[t.size() - 1];
	}
	return -1;
}