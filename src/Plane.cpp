#include "Plane.h"
#include "Helper.h"

using namespace std;

/* PUBLIC */

void Plane::printInfo() {
	cout << std::setprecision(4);
	cout << "- Type: Plane\n";
	cout << "- Normal: {" << normal[0] << " " << normal[1] << " " << normal[2] << "}\n";
	cout << "- Distance: " << distance << "\n";
	Shape::printInfo();
}

vector<float> Plane::getIntersection(const glm::vec3& dir, const glm::vec3& origin) {
	vector<float> vec;
	float t, denom;
	denom = glm::dot(glm::normalize(dir), glm::normalize(normal));
	if (denom < 0) {
		t = (distance - glm::dot(origin, glm::normalize(normal))) / denom;
		vec.push_back(t);
	}
	return vec;
}

string Plane::getTypeString() {
	string planeStr("Plane");
	return planeStr;
}

glm::vec3 Plane::getNormal(glm::vec3 point) {
	return transform->transformNormal(normal);
}