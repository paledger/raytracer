#include "Helper.h"

using namespace std;

class Helper {
public: 
	static vector<float> quadratic(float a, float b, float c) {
		vector<float> t;
		float discriminant = b*b - 4 * a*c; 
		if (discriminant >= 0) {
			float pos = (-b + float(sqrt(discriminant))) / (2 * a);
			t.push_back(pos);
			if (discriminant > 0) {
				float neg = (-b - float(sqrt(discriminant))) / (2 * a);
				t.push_back(neg);
			}
		}
		return t;
	}

	static int convertToRgb(float flt) {
		return (unsigned int)std::round(flt * 255.f);
	}
};