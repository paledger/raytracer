#include "Difference.h"
#include "Helper.h"

using namespace std;

std::vector<float> Difference::getIntersection(const glm::vec3& dir, const glm::vec3& origin) {
	vector<float> ret;
	float minA, maxA;
	float mainMin, mainMax, newMin = INFINITY, newMax = -INFINITY;
	Flags flags = Flags();
	shared_ptr<Shape> mainObject, currObject, minObject, maxObject;
	glm::vec3 tRay, tOrigin;
	shared_ptr<Transformation> transform = this->getTransformation();

	for (unsigned int o = 0; o < this->objects.size(); o++) {
		currObject = this->objects[o];
		tRay = transform->transformVector(currObject->transform->transformVector(dir));
		tOrigin = transform->transformPoint(currObject->transform->transformPoint(origin));
		minA = Helper::calculateFirstHit(tOrigin, tRay, currObject, flags);
		maxA = Helper::calculateLastHit(tOrigin, tRay, currObject, flags);
		if (o == 0) {
			mainObject = currObject;
			mainMin = minA;
			mainMax = maxA;
		}
		else {
			if (minA < newMin) {
				newMin = minA;
				minObject = currObject;
			}
			if (maxA > newMax) {
				newMax = maxA;
				maxObject = currObject;
			}
		}
	}

	if (newMin < 0 && newMax < 0 && mainMin > 0.002) {
		this->mostRecentIntersection = mainObject;
		ret.push_back(mainMin);
	}
	else {
		if (mainMin < newMin) {
			this->mostRecentIntersection = mainObject;
			ret.push_back(mainMin);
		}
		else if (mainMax > newMax) {
			this->mostRecentIntersection = maxObject;
			ret.push_back(newMax);
		}
		else {
			this->mostRecentIntersection = nullptr;
		}
	}
	return ret;
}

std::vector<float> Difference::getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags) {
	if (flags.csgtest) {
		float minA, maxA;
		float minB, maxB;
		cout << "--GETTING INTERSECTION" << endl;
		minA = Helper::calculateFirstHit(origin, dir, this->objects[0], flags);
		maxA = Helper::calculateLastHit(origin, dir, this->objects[0], flags);
		minB = Helper::calculateFirstHit(origin, dir, this->objects[1], flags);
		maxB = Helper::calculateLastHit(origin, dir, this->objects[1], flags);
		cout << this->objects[0]->getTypeString().c_str() << " minA " << minA << " maxA " << maxA << endl;
		cout << this->objects[1]->getTypeString().c_str() << " minB " << minB << " maxB " << maxB << endl;


		if (minB < 0 && maxB < 0 && minA > 0.002) {
			this->mostRecentIntersection = this->objects[0];
			cout << this->mostRecentIntersection->getTypeString().c_str() << "minA:" << minA << endl;
		}
		else {
			if (minA < minB && minA > 0) {
				this->mostRecentIntersection = this->objects[0];
				cout << this->mostRecentIntersection->getTypeString().c_str() << "minA:" << minA << endl;
			}
			else if (maxB < maxA && maxB > 0) {
				this->mostRecentIntersection = this->objects[1];
				cout << this->mostRecentIntersection->getTypeString().c_str() << "maxB:" << maxB << endl;
			}
			else {
				cout << "no intersection " << endl;
			}
		}
		cout << "---" << endl;
	}
	return this->getIntersection(dir, origin);
}

std::string Difference::getTypeString()
{
	return string("Difference");
}

glm::vec3 Difference::getNormal(glm::vec3 point)
{
	return this->mostRecentIntersection->getNormal(point);
}

glm::vec3 Difference::getCenter()
{
	return glm::vec3(0.0f);
}

void Difference::createBounds(glm::vec3 &min, glm::vec3 &max)
{

}