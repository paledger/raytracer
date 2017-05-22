#include "Transformation.h"
#include "Helper.h"

using namespace std;

void Transformation::printInfo() {
	cout << setprecision(4);
	cout << "Transformations:" << endl;
}

glm::mat4x4 Transformation::getTransformMatrix() {
	return transformMatrix;
}

void Transformation::applyRotation(glm::vec3 vec) {
	float rotateAng; 
	glm::vec3 rotateDir;
	setRotation(vec, rotateAng, rotateDir);
	transformMatrix = glm::rotate(glm::mat4x4(1.0f), rotateAng, rotateDir) * transformMatrix;
}

void Transformation::applyScale(glm::vec3 vec) {
	transformMatrix = glm::scale(glm::mat4x4(1.0f), vec) * transformMatrix;
}

void Transformation::applyTranslation(glm::vec3 vec) {
	transformMatrix = glm::translate(glm::mat4x4(1.0f), vec) * transformMatrix;
}

glm::vec3 Transformation::getTransformNormal(glm::vec3 normal) {
	glm::mat4x4 trans = getTransformMatrix();
	trans = glm::transpose(glm::inverse(trans));
	glm::vec4 transformed = trans * glm::vec4(normal.x, normal.y, normal.z, 0.0f);
	return glm::vec3(transformed.x, transformed.y, transformed.z);
}

glm::vec3 Transformation::transformPoint(glm::vec3 point) {
	glm::mat4x4 trans = getTransformMatrix();
	glm::vec4 transformed = glm::inverse(trans) * glm::vec4(point.x, point.y, point.z, 1.0f);
	return glm::vec3(transformed.x, transformed.y, transformed.z);
}

glm::vec3 Transformation::transformVector(glm::vec3 vec) {
	glm::mat4x4 trans = getTransformMatrix();
	glm::vec4 transformed = glm::inverse(trans) * glm::vec4(vec.x, vec.y, vec.z, 0.0f);
	return glm::vec3(transformed.x, transformed.y, transformed.z);
}


float Transformation::getTransformedT(glm::vec3 origin, glm::vec3 dir, float t) {
	glm::vec3 intersectPt = Helper::getPointOnRay(origin, dir, t);
	glm::vec3 newPoint = transformPoint(intersectPt);
	return glm::length(newPoint - origin);
}

void Transformation::setRotation(glm::vec3 rotationVec, float& angle, glm::vec3& dir) {
	bool rotateReady = false;
	for (int i = 0; i < 3; i++) {
		if (rotationVec[i]) {
			angle = glm::pi<float>() * rotationVec[i] / 180.0f;
			dir[i] = 1.0f;
			rotateReady = true;
		} 
		else if (!rotateReady && i == 2) {
			rotationVec[i] = 1.0f;
			rotateReady = true;
		}
	}
}