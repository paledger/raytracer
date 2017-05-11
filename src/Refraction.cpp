#include "Refraction.h"
#include "Render.h"
#include "Reflection.h"

using namespace std;

glm::vec3 Refraction::getRefraction(shared_ptr<Scene> scene, shared_ptr<Shape> shape,
	glm::vec3 intersectionPt, glm::vec3& d, unsigned int depth, bool test)
{
	if (depth == 6 || !shape) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	glm::vec3 transmission_color;
	float dir, snellRatio, newT;
	float transmission = shape->finish->filter;

	glm::vec3 n = shape->getNormal(intersectionPt);

	if ((dir = glm::dot(d, n)) < 0) { // entering
		snellRatio = 1 / shape->finish->ior;
	}
	else if (dir > 0) { // exiting
		n = -n;
		snellRatio = shape->finish->ior;
	}

	float d_dot_n = glm::dot(d, -n);
	glm::vec3 d_dn_n = d + d_dot_n * n;
	glm::vec3 n_sqrt = n * glm::sqrt(1 - glm::pow(snellRatio, 2) * (1 - glm::pow(d_dot_n, 2)));
	glm::vec3 transmissionVec = snellRatio * d_dn_n - n_sqrt;

	shared_ptr<Shape> newShape = Render::getFirstHit(scene, intersectionPt + n * 0.001f,
		transmissionVec, &newT);
	glm::vec3 newPoint = Helper::getPointOnRay(intersectionPt, transmissionVec, newT);

	transmission_color = Render::getPixelColor(scene, newPoint - n * 0.001f, transmissionVec, BLINNPHONG_MODE);

	return transmission_color;
}
