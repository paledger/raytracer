#include "Shape.h"

using namespace std;

/* PUBLIC */

void Shape::printInfo() 
{
	cout << setprecision(4);
	cout << "- Color: {" << Shape::finish->pigment[0] << " " << Shape::finish->pigment[1] << " " << Shape::finish->pigment[2] << "}\n";
	cout << "- Material:\n";
	cout << "  - Ambient: " << Shape::finish->ambient << "\n";
	cout << "  - Diffuse: " << Shape::finish->diffuse << "\n";
	if (Shape::finish->filter) {
		cout << "  - Filter: " << Shape::finish->filter << "\n";
	}
	if (Shape::finish->specular) {
		cout << "  - Specular: " << Shape::finish->specular << "\n";
	}
	if (Shape::finish->shininess) {
		cout << "  - Roughness: " << Shape::finish->shininess << "\n";
	}
	if (Shape::finish->metallic) {
		cout << "  - Metallic: " << Shape::finish->metallic << "\n";
	}
	if (Shape::finish->ior) { 
		cout << "  - IOR: " << Shape::finish->ior << "\n"; 
	}
	if (Shape::finish->reflection) {
		cout << "  - Reflection: " << Shape::finish->reflection << "\n";
	}
	if (Shape::finish->refraction) {
		cout << "  - Refraction: " << Shape::finish->refraction << "\n";
	}
}