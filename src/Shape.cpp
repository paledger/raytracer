#include "Shape.h"

using namespace std;

/* PUBLIC */

void Shape::printInfo() {
	cout << setprecision(4);
	cout << "- Color: {" << Shape::pigment[0] << " " << Shape::pigment[1] << " " << Shape::pigment[2] << "}\n";
	cout << "- Material:\n";
	cout << "  - Ambient: " << ambient << "\n";
	cout << "  - Diffuse: " << diffuse << "\n";
}