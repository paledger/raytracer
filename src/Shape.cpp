#include "Shape.h"

using namespace std;

class Shape
{
public:
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 rotate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 pigment = glm::vec3(0.0, 0.0, 0.0);
	float ambient;
	float diffuse;

	virtual void printInfo() { 
		cout << setprecision(4);
		cout << "- Color: {" << Shape::pigment[0] << " " << Shape::pigment[1]  << " " << Shape::pigment[2] << "}\n";
		cout << "- Material:\n";
		cout << "  - Ambient: " << ambient << "\n";
		cout << "  - Diffuse: " << diffuse << "\n";
	}

	virtual vector<float> getIntersection(const glm::vec3& dir, const glm::vec3& camLoc) = 0;

	virtual string getTypeString() = 0;
};

