#include "Intersect.h"
#include "Helper.h"

using namespace std;


std::vector<float> Intersect::getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags) 
{
	if (flags.csgtest) {
		float minA, maxA;
		float minB, maxB;
		minA = Helper::calculateFirstHit(origin, dir, this->objects[0], flags);
		maxA = Helper::calculateLastHit(origin, dir, this->objects[0], flags);
		minB = Helper::calculateFirstHit(origin, dir, this->objects[1], flags);
		maxB = Helper::calculateLastHit(origin, dir, this->objects[1], flags);

		cout << this->objects[0]->getTypeString().c_str() << " " << minA << " " << maxA << endl;
		cout << this->objects[1]->getTypeString().c_str() << " " << minB << " " << maxB << endl;


		if (minA < minB && maxA > minB) {
			this->mostRecentIntersection = this->objects[1];
			cout << this->mostRecentIntersection->getTypeString().c_str() << " minB: " << minB << endl;
		}
		else if (minB < minA && maxB > minA) {
			this->mostRecentIntersection = this->objects[0];
			cout << this->mostRecentIntersection->getTypeString().c_str() << " minA: " << minA << endl;
		}
		else {
			cout << "NO INTERSECTION" << endl;
		}
	}
	return this->getIntersection(dir, origin);
}

std::vector<float> Intersect::getIntersection(const glm::vec3& dir, const glm::vec3& origin) {
	vector<float> ret;
	float minA, maxA;
	float minOfMax = INFINITY, maxOfMin = -INFINITY;
	Flags flags = Flags();
	shared_ptr<Shape> currObject, minObj, maxObj;
	shared_ptr<Transformation> transform = this->getTransformation();
	glm::vec3 tRay, tOrigin;

	for (unsigned int o = 0; o < this->objects.size(); o++) {
		currObject = this->objects[o];
		tRay = currObject->transform->transformVector(dir);
		tOrigin = currObject->transform->transformPoint(origin);

		minA = Helper::calculateFirstHit(tOrigin, tRay, currObject, flags);
		maxA = Helper::calculateLastHit(tOrigin, tRay, currObject, flags);
		if (minA > maxOfMin) {
			maxOfMin = minA;
			maxObj = currObject;
		}
		if (maxA < minOfMax) {
			minOfMax = maxA;
			minObj = currObject;
		}
	}

	if (minOfMax < maxOfMin && minOfMax != INFINITY) {
		this->mostRecentIntersection = minObj;
		ret.push_back(minOfMax);
	}
	else if (maxOfMin < minOfMax && maxOfMin != -INFINITY) {
		this->mostRecentIntersection = maxObj;
		ret.push_back(maxOfMin);
	}
	else {
		this->mostRecentIntersection = nullptr;
	}
	return ret;
}

std::string Intersect::getTypeString()
{
	return string("Intersection");
}

glm::vec3 Intersect::getNormal(glm::vec3 point)
{
	return this->mostRecentIntersection->getNormal(point);
}

glm::vec3 Intersect::getCenter()
{
	glm::vec3 sum;
	for (unsigned int o = 0; o < this->objects.size(); o++) {
		sum += this->objects[o]->getCenter();
	}
	sum = sum / (float) this->objects.size();
	return sum;
}

void Intersect::createBounds(glm::vec3 &min, glm::vec3 &max)
{

}