#include "Reflection.h"
#include "Render.h"

using namespace std;

glm::vec3 Reflection::getReflection(shared_ptr<Scene> scene, shared_ptr<Shape> shape,
	glm::vec3 intersectionPt, glm::vec3& d, unsigned int depth, bool test)
{
	glm::vec3 thisShapeLocal, reflection_color;
	glm::vec3 incident = d;
	float newT;

	if (depth >= 6 || !shape) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	glm::vec3 n = shape->getNormal(intersectionPt);

	// find new reflection information 
	float reflection = shape->finish->reflection;
	glm::vec3 reflectionVec = incident - 2 * glm::dot(incident, n) * n;
	shared_ptr<Shape> newShape = Render::getFirstHit(scene, intersectionPt + n * 0.001f,
		reflectionVec, &newT);
	glm::vec3 newPoint = Helper::getPointOnRay(intersectionPt, reflectionVec, newT);

	// get reflection to multiply
	thisShapeLocal = Render::getPixelColor(scene, intersectionPt + reflectionVec * 0.001f, reflectionVec, BLINNPHONG_MODE, newT);
	if (test) {
		cout << shape->getTypeString() << endl;
		cout << "intersectionPt: " << intersectionPt.x << " " << intersectionPt.y << " " << intersectionPt.z << endl;
		cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
		cout << "reflectvec: " << reflectionVec.x << " " << reflectionVec.y << " " << reflectionVec.z << endl;
		glm::vec3 rgb = Helper::convertToRgb(thisShapeLocal);
		cout << "intersectionPt: " << newPoint.x << " " << newPoint.y << " " << newPoint.z << endl;
		cout << "next color: " << rgb.r << " " << rgb.g << " " << rgb.b << endl;
	}

	reflection_color = (thisShapeLocal + getReflection(scene, newShape, newPoint, reflectionVec, depth + 1, test));
	return reflection * reflection_color;
}
