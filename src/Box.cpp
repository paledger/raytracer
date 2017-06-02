#include "Box.h"
#include "Helper.h"

using namespace std;

/* PUBLIC */

void Box::printInfo() 
{
	cout << std::setprecision(4);
	cout << "- Type: Box\n";
	cout << "- min: " << Box::min.x << " " << Box::min.y << " " << Box::min.z << endl;
	cout << "- max: " << Box::max.x << " " << Box::max.y << " " << Box::max.z << endl;
	Shape::printInfo();
}

vector<float> Box::getIntersection(const glm::vec3& dir, const glm::vec3& origin) 
{
	vector<float> ret;
	float tgmin = -INFINITY; // max of mins
	float tgmax = INFINITY;  // min of maxes

	if (Box::parallelAndNoIntersections(origin, dir)) {
		return ret;
	}

	changeTgminForDimension(0, origin, dir, tgmin, tgmax); // x
	changeTgminForDimension(1, origin, dir, tgmin, tgmax); // y
	changeTgminForDimension(2, origin, dir, tgmin, tgmax); // z

	if (tgmin > tgmax || tgmax < 0) {
		return ret;
	}
	if (tgmin > 0) {
		ret.push_back(tgmin);
	}
	else {
		ret.push_back(tgmax);
	}
	return ret;
}

string Box::getTypeString() {
	string boxStr("Box");
	return boxStr;
}

glm::vec3 Box::getNormal(glm::vec3 point) 
{
	glm::vec3 normal = glm::vec3(0.0f);
	int dimMatched;
	if ((dimMatched = Box::matchDimensionMin(point)) >= 0) {
		normal[dimMatched] = -1;
	}
	if ((dimMatched = Box::matchDimensionMax(point)) >= 0) {
		normal[dimMatched] = 1;
	}

	return glm::normalize(this->transform->transformNormal(normal));
}

glm::vec3 Box::getCenter() {
	glm::vec3 center;
	center.x = (min.x + max.x) / 2.f;
	center.y = (min.y + max.y) / 2.f;
	center.z = (min.z + max.z) / 2.f;
	return center;
}

/** PRIVATE **/

bool Box::parallelAndNoIntersections(const glm::vec3 origin, const glm::vec3 dir) 
{
	if (dir.x == 0) {
		if (origin.x >= Box::min.x || origin.x <= Box::max.x) {
			return true;
		}
	}
	if (dir.y == 0) {
		if (origin.y >= Box::min.y || origin.y <= Box::max.y) {
			return true;
		}
	}
	if (dir.z == 0) {
		if (origin.z >= Box::min.z || origin.z <= Box::max.z) {
			return true;
		}
	}
	return false;
}

/* Takes in dimension, tgmin, tgmax, min, and max of curr dimension*/
void Box::changeTgminForDimension(int dim, 
	const glm::vec3 origin, const glm::vec3 dir, 
	float &tgmin, float &tgmax) 
{
	float t1 = (Box::min[dim] - origin[dim]) / dir[dim];
	float t2 = (Box::max[dim] - origin[dim]) / dir[dim];

	if (t1 > t2) {
		swap(t1, t2);
	}

	if (t1 > tgmin) {
		tgmin = t1;
	}
	
	if (t2 < tgmax) {
		tgmax = t2;
	}
}

int Box::matchDimensionMax(glm::vec3 point) {
	float ep = 0.001f;
	if (glm::abs(point.x - max.x) < ep) {
		return 0;
	}
	if (glm::abs(point.y - max.y) < ep) {
		return 1;
	}
	if (glm::abs(point.z - max.z) < ep) {
		return 2;
	}
	return -1;
}


int Box::matchDimensionMin(glm::vec3 point) {
	float ep = 0.001f;
	if (glm::abs(point.x - min.x) < ep) {
		return 0;
	}
	if (glm::abs(point.y - min.y) < ep) {
		return 1;
	}
	if (glm::abs(point.z - min.z) < ep) {
		return 2;
	}
	return -1;
}


void Box::createBounds(glm::vec3 &min, glm::vec3 &max)
{
	min = this->min;
	max = this->max;
}