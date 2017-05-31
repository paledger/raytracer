#include "BoundingBox.h"
#include "Sphere.h"

using namespace std;


void BoundingBox::recursiveTreeBuild(vector<shared_ptr<Shape>> inObjects, const unsigned int axis, bool test)
{
	if (test) {
		cout << "inObjects: " << inObjects.size() << endl;
	}
	if (inObjects.size() <= 1) {
		if (test) {
			cout << "end of recursive building" << endl;
		}
		this->objects = inObjects;
		this->calculateBoundingBox(test);
		if (test) {
			for (unsigned int sh = 0; sh < this->objects.size(); sh++) {
				cout << "me shape:" << this->objects[sh]->getTypeString().c_str() << endl;
			}
		}
		return;
	}

	this->sortObjectsOnAxis(inObjects, axis, test);

	this->left = make_shared<BoundingBox>();
	this->right = make_shared<BoundingBox>();

	this->left->recursiveTreeBuild(leftHalfArray(inObjects, test), (axis + 1) % 3, test);
	this->right->recursiveTreeBuild(rightHalfArray(inObjects, test), (axis + 1) % 3, test);

	this->calculateBoundingBox(test);
}

void BoundingBox::calculateBoundingBox(bool test)
{
	glm::vec3 newMin = glm::vec3(INFINITY);
	glm::vec3 newMax = glm::vec3(-INFINITY);

	if (test) {
		cout << "calculating bounding box..." << endl;
	}
	if (this->left != nullptr && this->right != nullptr) {
		/* use left and right child bounding boxes to create new bounding box */
		this->makeParentBoundingBox(newMin, newMax, test);
	}
	else {
		/* if we are here, this means there should only be one object so this should always happen */
		if (this->objects.size() == 1) {
			this->objects[0]->createBounds(newMin, newMax);
			this->min = newMin;
			this->max = newMax;
			this->transformBoundingBox(this->objects[0]->transform, test);
		}
	}
	if (test) {
		cout << "min: " << this->min.x << " " << this->min.y << " " << this->min.z << endl;
		cout << "max: " << this->max.x << " " << this->max.y << " " << this->max.z << endl;
	}
}


void BoundingBox::sortObjectsOnAxis(vector<shared_ptr<Shape>> &inObjects, const unsigned int axis, bool test)
{
	if (test) {
		cout << "sorting objects" << endl;
	}
	if (axis == 0) {
		sort(inObjects.begin(), inObjects.end(), compareXAxis);
	}
	else if (axis == 1) {
		sort(inObjects.begin(), inObjects.end(), compareYAxis);
	}
	else if (axis == 2) {
		sort(inObjects.begin(), inObjects.end(), compareZAxis);
	}
}

void BoundingBox::recursePrint(int depth) 
{
	cout << depth << endl;
	cout << "min: " << this->min.x << " " << this->min.y << " " << this->min.z << endl;
	cout << "max: " << this->max.x << " " << this->max.y << " " << this->max.z << endl;

	for (unsigned int sh = 0; sh < this->objects.size(); sh++) {
		cout << "shape:" << this->objects[sh]->getTypeString().c_str() << endl;
	}
	if (this->left) {
		cout << "\nleft -->" << endl;
		this->left->recursePrint(depth + 1);
	}
	if (this->right) {
		cout << "\nright -->" << endl;
		this->right->recursePrint(depth + 1);
	}
}

/** PRIVATE **/

vector<shared_ptr<Shape>> BoundingBox::leftHalfArray(vector<shared_ptr<Shape>> objs, bool test)
{
	vector<shared_ptr<Shape>> newVec = vector<shared_ptr<Shape>>();
	unsigned int length = objs.size();

	newVec.assign(objs.begin(), objs.begin() + (unsigned int) ceil(length / 2.f));
	if (test) {
		cout << "left half length: " << newVec.size() << endl;
	}
	return newVec;
}

vector<shared_ptr<Shape>> BoundingBox::rightHalfArray(vector<shared_ptr<Shape>> objs, bool test)
{
	vector<shared_ptr<Shape>> newVec = vector<shared_ptr<Shape>>();
	unsigned int length = objs.size();

	newVec.assign(objs.begin() + (unsigned int)ceil(length / 2.f), objs.end());
	if (test) {
		cout << "right half length: " << newVec.size() << endl;
	}
	return newVec;
}

void BoundingBox::makeParentBoundingBox(glm::vec3 &min, glm::vec3 &max, bool test)
{
	if (test) {
		cout << "----" << endl;
		cout << "MAKING PARENT BOX" << endl;
	}
	glm::vec3 newMin = glm::vec3(INFINITY);
	glm::vec3 newMax = glm::vec3(-INFINITY);
	glm::vec3 leftMin = this->left->min;
	glm::vec3 leftMax = this->left->max;
	glm::vec3 rightMin = this->right->min;
	glm::vec3 rightMax = this->right->max;

	for (int i = 0; i < 3; i++) {
		if (leftMin[i] < newMin[i]) {
			newMin[i] = leftMin[i];
		}
		if (leftMax[i] > newMax[i]) {
			newMax[i] = leftMax[i];
		}
		if (rightMin[i] < newMin[i]) {
			newMin[i] = rightMin[i];
		}
		if (rightMax[i] > newMax[i]) {
			newMax[i] = rightMax[i];
		}
	}

	min = newMin;
	max = newMax;
	this->min = newMin;
	this->max = newMax;
	if (test) {
		cout << "post min: " << min.x << " " << min.y << " " << min.z << endl;
		cout << "post max: " << max.x << " " << max.y << " " << max.z << endl;
		cout << "----" << endl;
	}
}

void BoundingBox::transformBoundingBox(shared_ptr<Transformation> transform, bool test)
{
	if (test) {
		cout << "TRANSFORMING BB" << endl;
		cout << "----" << endl;
	}
	glm::vec3 tMin = this->min;
	glm::vec3 tMax = this->max;

	if (test) {
		cout << transform->getTransformMatrix()[3][0] << endl;
		cout << "pre min: " << min.x << " " << min.y << " " << min.z << endl;
		cout << "pre max: " << max.x << " " << max.y << " " << max.z << endl;
	}
	vector<glm::vec3> points = vector<glm::vec3>();
	points.push_back(glm::vec3(tMin.x, tMin.y, tMin.z));
	points.push_back(glm::vec3(tMin.x, tMax.y, tMin.z));
	points.push_back(glm::vec3(tMin.x, tMin.y, tMax.z));
	points.push_back(glm::vec3(tMin.x, tMax.y, tMax.z));
	points.push_back(glm::vec3(tMax.x, tMin.y, tMin.z));
	points.push_back(glm::vec3(tMax.x, tMax.y, tMin.z));
	points.push_back(glm::vec3(tMax.x, tMin.y, tMax.z));
	points.push_back(glm::vec3(tMax.x, tMax.y, tMax.z));

	for (unsigned int p = 0; p < points.size(); p++) {
		points[p] = transform->transformPointbyModel(points[p]);
	}
	tMin = glm::vec3(INFINITY);
	tMax = glm::vec3(-INFINITY);
	for (int p = 0; p < 8; p++) {
		for (int d = 0; d < 3; d++) {
			if (points[p][d] < tMin[d]) {
				tMin[d] = points[p][d];
			}
			if (points[p][d] > tMax[d]) {
				tMax[d] = points[p][d];
			}
		}
	}

	this->min = tMin;
	this->max = tMax;

	if (test) {
		cout << "post min: " << min.x << " " << min.y << " " << min.z << endl;
		cout << "post max: " << max.x << " " << max.y << " " << max.z << endl;
		cout << "----" << endl;
	}
}

bool compareXAxis(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) {
	return s1->getCenter()[0] < s2->getCenter()[0];
}
bool compareYAxis(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) {
	return s1->getCenter()[1] < s2->getCenter()[1];
}
bool compareZAxis(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) {
	return s1->getCenter()[2] < s2->getCenter()[2];
}

