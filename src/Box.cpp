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


vector<float> Box::getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags) 
{
	float tgmin = -INFINITY; // max of mins
	float tgmax = INFINITY;  // min of maxes

							 // for x, y, z
	if (flags.csgtest) {
		cout << "IN BOX INTERSECT" << endl;
 		for (int i = 0; i < 3; i++) {
			if (dir[i] == 0) {
				if (this->isParallelAndNoIntersect(origin, dir, i)) {
					cout << "NO INTERSECTION " << endl;
				}
			}
			else {
				this->changeTgminForDimension(i, origin, dir, tgmin, tgmax);
			}
		}

		if (tgmin > tgmax || tgmax < 0) {
			cout << "NO INTERSECTION " << endl;
		}
		if (tgmin > 0 && tgmin != INFINITY) {
			cout << "TGMIN: " << tgmin << endl;
		}
		if (tgmax > 0 && tgmax != -INFINITY) {
			cout << "TGMAX: " << tgmax << endl;
		}
		cout << endl;
	}

	return this->getIntersection(dir, origin);
}

vector<float> Box::getIntersection(const glm::vec3& dir, const glm::vec3& origin) 
{
	vector<float> ret;
	float tgmin = -INFINITY; // max of mins
	float tgmax = INFINITY;  // min of maxes
	
	// for x, y, z
	for (int i = 0; i < 3; i++) {
		if (dir[i] == 0) {
			if (this->isParallelAndNoIntersect(origin, dir, i)) {
				return ret;
			}
		}
		else {
			this->changeTgminForDimension(i, origin, dir, tgmin, tgmax);
		}
	}

	if (tgmin > tgmax || tgmax < 0) {
		return ret;
	}
	if (tgmin > 0 && tgmin != INFINITY) {
		ret.push_back(tgmin);
	}
	if (tgmax > 0 && tgmax != -INFINITY) {
		ret.push_back(tgmax);
	}
	/*if (tgmin > 0) {
		ret.push_back(tgmin);
	}
	else {
		ret.push_back(tgmax);
	}*/
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

	return glm::normalize(this->getTransformation()->transformNormal(normal));
}

glm::vec3 Box::getCenter() {
	glm::vec3 center;
	center.x = (min.x + max.x) / 2.f;
	center.y = (min.y + max.y) / 2.f;
	center.z = (min.z + max.z) / 2.f;
	return center;
}

/** PRIVATE **/

bool Box::isParallelAndNoIntersect(const glm::vec3 origin, const glm::vec3 dir, const int dim) 
{
	if (origin[dim] >= this->min[dim] || origin[dim] <= this->max[dim]) {
		return true;
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

shared_ptr<Finish> Box::getFinish()
{
	return this->finish;
}