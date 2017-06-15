#include "Difference.h"
#include "Helper.h"

using namespace std;

std::vector<float> Difference::getIntersection(const glm::vec3& dir, const glm::vec3& origin) {
	vector<float> ret;
	float minA, maxA;
	float minB, maxB;
	Flags flags = Flags();
	shared_ptr<Shape> currObject;
	glm::vec3 tRay, tOrigin;
	currObject = this->objects[0];
	tRay = currObject->transform->transformVector(dir);
	tOrigin = currObject->transform->transformPoint(origin);
	minA = Helper::calculateFirstHit(tOrigin, tRay, currObject, flags);
	maxA = Helper::calculateLastHit(tOrigin, tRay, currObject, flags);
	currObject = this->objects[1];
	tRay = currObject->transform->transformVector(dir);
	tOrigin = currObject->transform->transformPoint(origin);
	minB = Helper::calculateFirstHit(tOrigin, tRay, currObject, flags);
	maxB = Helper::calculateLastHit(tOrigin, tRay, currObject, flags);

	if (minB < 0 && maxB < 0 && minA > 0.002) {
		this->mostRecentIntersection = this->objects[0];
		ret.push_back(minA);
	}
	else {
		if (minA < minB && minA > 0) {
			this->mostRecentIntersection = this->objects[0];
			ret.push_back(minA);
		}
		else if (maxB < maxA && maxB > 0) {
			this->mostRecentIntersection = this->objects[1];
			ret.push_back(maxB);
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