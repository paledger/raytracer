#include "Reflection.h"
#include "Render.h"
#include "Shading.h"

using namespace std;

glm::vec3 Reflection::getReflection(shared_ptr<Scene> scene, shared_ptr<Shape> shape,
	const glm::vec3 intersectionPt, const glm::vec3 d, unsigned int depth, Flags flags)
{
	glm::vec3 thisShapeLocal, reflection_color;
	glm::vec3 incident = glm::normalize(d);
	float newT;

	if (depth >= 6 || !shape) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	shared_ptr<Transformation> transform = shape->transform;
	glm::vec3 n = glm::normalize(shape->getNormal(intersectionPt));
	glm::vec3 epsilonVec = n * 0.001f;

	// find new reflection information 
	float reflection = shape->finish->reflection;
	glm::vec3 reflectionVec = incident - 2 * glm::dot(incident, n) * n;
	shared_ptr<Shape> newShape = Render::getFirstHit(scene, intersectionPt + epsilonVec,
		reflectionVec, &newT);
	glm::vec3 newPoint = Helper::getPointOnRay(intersectionPt, reflectionVec, newT);

	// get reflection to multiply
	if (newShape) {
		if (flags.test) {
			cout << newShape->getTypeString() << " " << depth << endl;
		}
		thisShapeLocal = Shading::shadedPixels(scene, newShape, intersectionPt + epsilonVec, reflectionVec, newT, BLINNPHONG_MODE, flags.test);

		if (flags.test) {
			n = newShape->getNormal(newPoint);
			cout << "origin: " << intersectionPt.x << " " << intersectionPt.y << " " << intersectionPt.z << endl;
			cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
			cout << "reflectvec: " << reflectionVec.x << " " << reflectionVec.y << " " << reflectionVec.z << endl;
			glm::vec3 rgb = Helper::convertToRgb(thisShapeLocal);
			cout << "newPoint: " << newPoint.x << " " << newPoint.y << " " << newPoint.z << endl;
			cout << reflection << " * next color: " << thisShapeLocal.r << " " << thisShapeLocal.g << " " << thisShapeLocal.b << endl << endl;
			cout << reflection << " * next color: " << rgb.r << " " << rgb.g << " " << rgb.b << endl << endl;
		}
	}

	reflection_color = (thisShapeLocal + getReflection(scene, newShape, newPoint + epsilonVec, reflectionVec, depth + 1, flags));
	return reflection * reflection_color;
}
