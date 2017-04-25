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

vector<float> Sphere::getIntersection(const glm::vec3& dir, const glm::vec3& camLoc) {
	float a = glm::dot(dir, dir);
	float b = glm::dot(2.0f*dir, camLoc - center);
	float c = glm::dot(camLoc - center, camLoc - center) - radius*radius;
	return Helper::quadratic(a, b, c);
}

string Sphere::getTypeString() {
	string sphereStr("Sphere");
	return sphereStr;
}