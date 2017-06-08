#include "Ambient.h"
#include "Render.h"

using namespace std;

/*** PUBLIC ***/

glm::vec3 Ambient::getAmbient(shared_ptr<Scene> scene, shared_ptr<Intersection> intersect, int depth, Flags flags) {
	if (!flags.gi) {
		return Ambient::getNormalAmbient(intersect->shape);
	}
	else {
		return Ambient::getMonteCarloAmbient(scene, intersect, depth, flags);
	}
}

glm::vec3 Ambient::getNormalAmbient(shared_ptr<Shape> shape) {
	return shape->finish->pigment * shape->finish->ambient;
}

glm::vec3 Ambient::getMonteCarloAmbient(shared_ptr<Scene> scene, shared_ptr<Intersection> intersect, int depth, Flags flags)
{
	glm::vec3 ambient, gi, intersectPt, viewRay, normal, currPt, currGI;
	glm::vec2 randUV;
	int initialN = 128, ratio = 8;
	int N = (ratio * initialN) / (int) glm::pow(ratio, depth + 1);
	if (intersect && intersect->shape && N >= 0 && depth <= 2) {
		shared_ptr<Shape> shape = intersect->shape;

		glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
		intersectPt = intersect->wPt;
		normal = intersect->n;

		if (flags.gitest && depth == 0) {
			cout << "GETTING MONTE CARLO " << depth << endl;
			cout << "shape: " << shape->getTypeString() << endl;
			cout << "intersection point " << intersectPt.x << " " << intersectPt.y << " " << intersectPt.z << endl;
			cout << "N: " << N << endl;
			cout << "normal " << normal.x << " " << normal.y << " " << normal.z << endl;
		}
		for (int pt = 0; pt < N; pt++) {
			viewRay = Ambient::generateHemisphereSamplePoint(up, normal, flags);
			if (flags.gitest && depth == 0) {
				cout << "randRay: " << viewRay.x << " " << viewRay.y << " " << viewRay.z << endl;
			}
			currGI = Render::getPixelColor(scene, intersectPt + viewRay * 0.001f, viewRay, depth + 1, flags) * glm::dot(viewRay, normal);
			gi += currGI;
		}
		ambient = shape->finish->pigment  *  2.f * gi / (float)N;
		if (flags.gitest && depth == 0) {
			cout << N << " - ambient: " << Helper::convertToRgb(ambient.r) << " " << Helper::convertToRgb(ambient.g) << " " << Helper::convertToRgb(ambient.b) << endl;
		}
	}

	return ambient;
}

/*** PRIVATE ***/

glm::vec3 Ambient::generateHemisphereSamplePoint(glm::vec3 up, glm::vec3 normal, Flags flags) {

	glm::vec2 randUV = Ambient::generateRandomUV();
	glm::vec3 currPt = generateCosineWeightedPoint(randUV[0], randUV[1], flags);
	glm::vec3 viewRay = Ambient::alignSampleVector(currPt, up, normal);
	return viewRay;
}

glm::vec3 Ambient::generateCosineWeightedPoint(float u, float v, Flags flags) {
	float radial = glm::sqrt(u);
	float theta = 2.0f * glm::pi<float>() * v;

	float x = radial * glm::cos(theta);
	float y = radial * glm::sin(theta);
	if (flags.gitest) {
		//cout << "x " << x << "y " << y << "z " << glm::sqrt(1 - u) << endl;
	}

	return glm::vec3(x, y, glm::sqrt(1 - u));

}

glm::vec3 Ambient::alignSampleVector(glm::vec3 sample, glm::vec3 up, glm::vec3 normal) {
	float angle = glm::acos(glm::dot(up, normal));
	glm::vec3 axis = glm::cross(up, normal);

	glm::mat4x4 matrix = glm::rotate(glm::mat4x4(1.0f), angle, axis);
	glm::vec4 ret = matrix * glm::vec4(sample.x, sample.y, sample.z, 1.0f);

	return glm::vec3(ret.x, ret.y, ret.z);
}

glm::vec2 Ambient::generateRandomUV() {
	float u, v;
	u = glm::clamp((float) rand() / (float) RAND_MAX, 0.f, 1.f);
	v = glm::clamp((float) rand() / (float) RAND_MAX, 0.f, 1.f);
	return glm::vec2(u, v);
}