#include "Sphere.h"
#ifndef SHAPE_CPP
#define SHAPE_CPP
#include "Shape.cpp"
#endif

#ifndef  HELPER_CPP
#define HELPER_CPP
#include "Helper.cpp"
#endif

using namespace std;

class Sphere : public Shape
{
public:
	glm::vec3 center = glm::vec3(0.0, 0.0, 0.0);
	float radius = 1;

	void printInfo() {
		cout << std::setprecision(4);
		cout << "- Type: Sphere\n";
		cout << "- Center: {" << center[0] << " " << center[1] << " " << center[2] << "}\n";
		cout << "- Radius: " << radius << "\n";
		Shape::printInfo();
	}

	vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& camLoc) {
		float a = glm::dot(dir, dir);
		float b = glm::dot(2.0f*dir, camLoc - center);
		float c = glm::dot(camLoc - center, camLoc - center) - radius*radius;
		return Helper::quadratic(a, b, c);
	}

	string getTypeString() {
		string sphereStr("Sphere");
		return sphereStr;
	}
};