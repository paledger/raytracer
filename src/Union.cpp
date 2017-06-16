#include "Union.h"
#include "BoundingBox.h"
#include "Helper.h"

using namespace std;


std::vector<float> Union::getIntersection(const glm::vec3& dir, const glm::vec3& origin, Flags flags)
{
	float minA, maxA;
	float minB, maxB;
	minA = Helper::calculateFirstHit(origin, dir, this->objects[0], flags);
	maxA = Helper::calculateLastHit(origin, dir, this->objects[0], flags);
	minB = Helper::calculateFirstHit(origin, dir, this->objects[1], flags);
	maxB = Helper::calculateLastHit(origin, dir, this->objects[1], flags);

	cout << this->objects[0]->getTypeString().c_str() << " " << minA << " " << maxA << endl;
	cout << this->objects[1]->getTypeString().c_str() << " " << minB << " " << maxB << endl;

	return this->getIntersection(dir, origin);
}

std::vector<float> Union::getIntersection(const glm::vec3& dir, const glm::vec3& origin) {
	vector<float> ret;
	float minT = INFINITY, currT;
	shared_ptr<Shape> currObject;
	glm::vec3 tRay, tOrigin;
	Flags flags = Flags();
	shared_ptr<Transformation> transform = this->getTransformation();
	for (unsigned int o = 0; o < this->objects.size(); o++) {
		currObject = this->objects[o];
		tRay = currObject->transform->transformVector(dir);
		tOrigin = currObject->transform->transformPoint(origin);
		currT = Helper::calculateFirstHit(tOrigin, tRay, currObject, flags);
		if (currT > 0 && currT < minT) {
			minT = currT;
			this->mostRecentIntersection = currObject;
		}
	}
	ret.push_back(minT);
	return ret;
}

std::string Union::getTypeString()
{
	return string("Union");
}

/* assumes intersections and mostRecentIntersection exists */
glm::vec3 Union::getNormal(glm::vec3 point)
{
	return this->mostRecentIntersection->getNormal(point);
}

glm::vec3 Union::getCenter()
{
	glm::vec3 sum;
	for (unsigned int o = 0; o < this->objects.size(); o++) {
		sum += this->objects[o]->getCenter();
	}
	sum = sum / (float) this->objects.size();
	return sum;
}

void Union::createBounds(glm::vec3 &min, glm::vec3 &max)
{
	
}