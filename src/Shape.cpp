#include "Shape.h"

using namespace std;

/* PUBLIC */

void Shape::printInfo() 
{
	cout << setprecision(4);
	cout << "- Color: {" << Shape::finish->pigment[0] << " " << Shape::finish->pigment[1] << " " << Shape::finish->pigment[2] << "}\n";
	Shape::transform->printInfo();
	cout << "- Material:\n";
	cout << "  - Ambient: " << Shape::finish->ambient << "\n";
	cout << "  - Diffuse: " << Shape::finish->diffuse << "\n";
	Shape::finish->printInfo();
}