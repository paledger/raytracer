#include "LightSource.h"

using namespace std;

class LightSource
{
public: 
	glm::vec3 location = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);

	void printInfo() {
		cout << setprecision(4);
		cout << "- Location: {" << location[0] << " " << location[1] << " " << location[2] << "}\n";
		cout << "- Color: {" << color[0] << " " << color[1] << " " << color[2] << "}\n";
	}
};