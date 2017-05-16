#include "Transformation.h"
#include "Helper.h"

using namespace std;

void Transformation::printInfo() {
	cout << setprecision(4);
	cout << "Transformations:" << endl;
	cout << "- rotate: " << rotateAng << " in the " << rotateDir.x << " " << rotateDir.y << " " << rotateDir.z << endl;
	cout << "- translate: " << translate.x << " " << translate.y << " " << translate.z << endl;
	cout << "- scale: " << scale.x << " " << scale.y << " " << scale.z << endl;
}

glm::mat4x4 Transformation::getTransformMatrix() {
	if (!transformReady) {
		if (!rotateReady) {
			setRotation();
		}
		transformMatrix = glm::translate(transformMatrix, Transformation::translate);
		transformMatrix = glm::rotate(transformMatrix, Transformation::rotateAng, Transformation::rotateDir);
		transformMatrix = glm::scale(transformMatrix, Transformation::scale);
		transformReady = true;
	}
	return transformMatrix;
}
glm::vec3 Transformation::getTransformNormal(glm::vec3 normal) {
	glm::mat4x4 trans = getTransformMatrix();
	trans = glm::transpose(glm::inverse(trans));
	glm::vec4 transformed = (trans) * glm::vec4(normal.x, normal.y, normal.z, 0.0f);
	return glm::vec3(transformed.x, transformed.y, transformed.z);
}

glm::vec3 Transformation::transformPoint(glm::vec3 point) {
	glm::mat4x4 trans = getTransformMatrix();
	glm::vec4 transformed = glm::inverse(trans) * glm::vec4(point.x, point.y, point.z, 1.0f);
	return glm::vec3(transformed.x, transformed.y, transformed.z);
}

glm::vec3 Transformation::transformVector(glm::vec3 vec) {
	glm::mat4x4 trans = getTransformMatrix();
	glm::vec4 transformed = glm::inverse(trans) * glm::vec4(vec.x, vec.y, vec.z, 1.0f);
	return glm::vec3(transformed.x, transformed.y, transformed.z);
}


float Transformation::getTransformedT(glm::vec3 origin, glm::vec3 dir, float t) {
	glm::vec3 intersectPt = Helper::getPointOnRay(origin, dir, t);
	glm::vec3 newPoint = transformPoint(intersectPt);
	return glm::length(newPoint - origin);
}

void Transformation::setRotation() {
	if (!rotateReady) {
		for (int i = 0; i < 3; i++) {
			if (rotateDir[i]) {
				rotateAng = rotateDir[i];
				rotateDir[i] = 1.0f;
				rotateReady = true;
			} 
			else if (!rotateReady && i == 2) {
				rotateDir[i] = 1.0f;
			}
		}
		rotateReady = true;
	}
}