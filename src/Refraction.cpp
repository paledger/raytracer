#include "Refraction.h"
#include "Render.h"
#include "Reflection.h"
#include "Shading.h"

using namespace std;

glm::vec3 Refraction::getRefraction(shared_ptr<Scene> scene, shared_ptr<Shape> shape,
	glm::vec3 intersectionPt, glm::vec3& d, unsigned int depth, Flags flags)
{
	if (depth == 6 || !shape) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	glm::vec3 transmission_color, thisShapeLocal, attenuation = glm::vec3(1.0f);
	float dir, snellRatio, newT;
	float transmission = shape->finish->filter;
	d = glm::normalize(d);

	glm::vec3 n = glm::normalize(shape->getNormal(intersectionPt));

	if ((dir = glm::dot(d, n)) < 0) { // entering
		if (flags.test) {
			cout << "entering" << endl;
		}
		snellRatio = 1.0f / shape->finish->ior;
	}
	else if (dir > 0) { // exiting
		if (flags.test) {
			cout << "exiting" << endl;
		}
		n = -n;
		snellRatio = shape->finish->ior;
	}

	float d_dot_n = glm::dot(d, n);
	glm::vec3 d_dn_n = d - d_dot_n * n;
	glm::vec3 n_sqrt = n * (float) glm::sqrt(1.f - (float) glm::pow(snellRatio, 2.0f) * (1.f - (float) glm::pow(d_dot_n, 2.0f)));
	glm::vec3 transmissionVec = snellRatio * d_dn_n - n_sqrt;
	glm::vec3 epsilonVec = n * 0.001f;
	shared_ptr<Shape> newShape = Render::getFirstHit(scene, intersectionPt - epsilonVec,
		transmissionVec, &newT);
	glm::vec3 newPoint = Helper::getPointOnRay(intersectionPt, transmissionVec, newT);
	if (newShape) {
		n = newShape->getNormal(newPoint);
		if (flags.test) {
			cout << newShape->getTypeString() << " " << depth << endl;
		}
		// beer's law
		float d = newT;
		glm::vec3 absorbance = (glm::vec3(1.f, 1.f, 1.f) - shape->finish->pigment)*0.15f*-d;
		attenuation = glm::vec3(glm::pow(glm::e<float>(), absorbance.r),
			glm::pow(glm::e<float>(), absorbance.g),
			glm::pow(glm::e<float>(), absorbance.b));
		thisShapeLocal = Render::getPixelColor(scene, intersectionPt - epsilonVec,
			transmissionVec, depth + 1, flags);


		if (flags.test) {
			cout << "origin: " << intersectionPt.x << " " << intersectionPt.y << " " << intersectionPt.z << endl;
			cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
			cout << "transmVec: " << transmissionVec.x << " " << transmissionVec.y << " " << transmissionVec.z << endl;
			cout << "newPoint: " << newPoint.x << " " << newPoint.y << " " << newPoint.z << endl;
			glm::vec3 rgb = Helper::convertToRgb(thisShapeLocal);
			cout << transmission << " * next color: " << thisShapeLocal.r << " " << thisShapeLocal.g << " " << thisShapeLocal.b << endl;
			cout << transmission << " * next color: " << rgb.r << " " << rgb.g << " " << rgb.b << endl << endl;
		}
	}
	else {
		if (flags.test) {
			cout << "end of recursion\n" << endl;
		}
	}

	transmission_color = thisShapeLocal;

	return transmission * transmission_color;
}
