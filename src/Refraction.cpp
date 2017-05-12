#include "Refraction.h"
#include "Render.h"
#include "Reflection.h"

using namespace std;

glm::vec3 Refraction::getRefraction(shared_ptr<Scene> scene, shared_ptr<Shape> shape,
	glm::vec3 intersectionPt, glm::vec3& d, unsigned int depth, bool test)
{
	if (depth >= 6 || !shape) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	glm::vec3 transmission_color, thisShapeLocal;
	float dir, snellRatio, newT;
	float transmission = shape->finish->filter;

	glm::vec3 n = glm::normalize(shape->getNormal(intersectionPt));

	if ((dir = glm::dot(d, n)) < 0) { // entering
		snellRatio = 1 / shape->finish->ior;
	}
	else if (dir > 0) { // exiting
		snellRatio = shape->finish->ior;
	}

	float d_dot_n = glm::dot(d, n);
	glm::vec3 d_dn_n = d + d_dot_n * n;
	glm::vec3 n_sqrt = n * glm::sqrt(1.f - glm::pow(snellRatio, 2) * (1.f - glm::pow(d_dot_n, 2)));
	glm::vec3 transmissionVec = snellRatio * d_dn_n - n_sqrt;

	shared_ptr<Shape> newShape = Render::getFirstHit(scene, intersectionPt + n * 0.001f,
		transmissionVec, &newT);
	glm::vec3 newPoint = Helper::getPointOnRay(intersectionPt, transmissionVec, newT);
	if (newShape) {
		if (test) {
			cout << newShape->getTypeString() << " " << depth << endl;
		}
		thisShapeLocal = Render::getPixelColor(scene, intersectionPt, transmissionVec, BLINNPHONG_MODE, test);
		if (test) {
			n = newShape->getNormal(newPoint);
			cout << "origin: " << intersectionPt.x << " " << intersectionPt.y << " " << intersectionPt.z << endl;
			cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
			cout << "refractVec: " << transmissionVec.x << " " << transmissionVec.y << " " << transmissionVec.z << endl;
			cout << "newPoint: " << newPoint.x << " " << newPoint.y << " " << newPoint.z << endl;
			glm::vec3 rgb = Helper::convertToRgb(thisShapeLocal);
			cout << transmission << " * next color: " << thisShapeLocal.r << " " << thisShapeLocal.g << " " << thisShapeLocal.b << endl;
			cout << transmission << " * next color: " << rgb.r << " " << rgb.g << " " << rgb.b << endl << endl;
		}
	}

	transmission_color = thisShapeLocal + Refraction::getRefraction(scene, newShape, newPoint + n * 0.001f, transmissionVec, depth + 1, test);

	return transmission * transmission_color;
}
