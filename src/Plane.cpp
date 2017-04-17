#include "Plane.h"
#ifndef SHAPE_CPP
#define SHAPE_CPP
#include "Shape.cpp"
#endif

#ifndef  HELPER_CPP
#define HELPER_CPP
#include "Helper.cpp"
#endif

using namespace std;

class Plane: public Shape
{
public:
	glm::vec3 normal = glm::vec3(0.0, 0.0, 0.0);
	float distance = 0;

	void printInfo() {
		cout << std::setprecision(4);
		cout << "- Type: Plane\n";
		cout << "- Normal: {" << normal[0] << " " << normal[1] << " " << normal[2] << "}\n";
		cout << "- Distance: " << distance << "\n";
		Shape::printInfo();
	}

	vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& camLoc) {
		vector<float> vec;
		float t, denom;
		if ((denom = glm::dot(glm::normalize(dir), glm::normalize(normal))) <= 0) {
			t = (distance - glm::dot(camLoc, glm::normalize(normal))) / denom;
			vec.push_back(t);
		}
		return vec;
	}

	string getTypeString() {
		return string("Plane");
	}
};