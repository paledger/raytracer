#include "LightSource.h"

using namespace std;

/* PUBLIC */

void LightSource::printInfo() {
	cout << setprecision(4);
	cout << "- Location: {" << location[0] << " " << location[1] << " " << location[2] << "}\n";
	cout << "- Color: {" << color[0] << " " << color[1] << " " << color[2] << "}\n";
}