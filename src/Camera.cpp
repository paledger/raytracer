#include "Camera.h"

using namespace std;

/* PUBLIC */

void Camera::printInfo() {
	cout << setprecision(4);
	cout << "Camera: \n";
	cout << "- Location: {" << location[0] << " " << location[1] << " " << location[2] << "}\n";
	cout << "- Up: {" << up[0] << " " << up[1] << " " << up[2] << "}\n";
	cout << "- Right: {" << right[0] << " " << right[1] << " " << right[2] << "}\n";
	cout << "- Look at: {" << look_at[0] << " " << look_at[1] << " " << look_at[2] << "}\n";
}
