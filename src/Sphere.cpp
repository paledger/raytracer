#include "Sphere.h"
#include "Helper.h"

using namespace std;

/* PUBLIC */

void Sphere::printInfo() {
	cout << std::setprecision(4);
	cout << "- Type: Sphere\n";
	cout << "- Center: {" << center[0] << " " << center[1] << " " << center[2] << "}\n";
	cout << "- Radius: " << radius << "\n";
	Shape::printInfo();
}

vector<float> Sphere::getIntersection(const glm::vec3& dir, const glm::vec3& origin) {
	vector<float> ret;
	glm::vec3 normalDir = glm::normalize(origin - center);
	glm::vec3 d = dir;
	float a = glm::dot(d, d);
	float b = glm::dot(2.0f * d, origin - center);
	float c = glm::dot(origin - center, origin - center) - glm::pow(radius, 2.0f);
	vector<float> tVals = Helper::quadratic(a, b, c);
	if (tVals.empty()) {
		return ret;
	}
	if (tVals.size() == 1) {
		if (tVals[0] >= 0) {
			ret.push_back(tVals[0]);
		}
	}
	if (tVals.size() == 2) {
		if (tVals[0] >= 0) {
			ret.push_back(tVals[0]);
		}
		if (tVals[1] >= 0) {
			ret.push_back(tVals[1]);
		}
	}
	return ret;
}

string Sphere::getTypeString() {
	string sphereStr("Sphere");
	return sphereStr;
}

glm::vec3 Sphere::getNormal(glm::vec3 point) {
	glm::vec3 normal = glm::normalize(point - center);
	return transform->getTransformNormal(normal);
}