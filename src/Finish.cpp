#include "Finish.h" 

using namespace std;

void Finish::printInfo() {
	cout << setprecision(4);

	if (filter) {
		cout << "  - Filter: " << filter << "\n";
	}
	if (specular) {
		cout << "  - Specular: " << specular << "\n";
	}
	if (shininess) {
		cout << "  - Roughness: " << shininess << "\n";
	}
	if (metallic) {
		cout << "  - Metallic: " << metallic << "\n";
	}
	if (ior) {
		cout << "  - IOR: " << ior << "\n";
	}
	if (reflection) {
		cout << "  - Reflection: " << reflection << "\n";
	}
	if (refraction) {
		cout << "  - Refraction: " << refraction << "\n";
	}
}