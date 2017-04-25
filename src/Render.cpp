#include "Render.h"
#include "Helper.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

using namespace std;

/* PUBLIC */
void Render::render(shared_ptr<Scene>& scene, int width, int height) {
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);
	shared_ptr<Shape> shape;
	glm::vec3 rayDirection;
	float t;
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{

			unsigned char red, green, blue;
			rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
			shape = Render::getFirstHit(scene, rayDirection, &t);
			if (shape) {
				red = Helper::convertToRgb(shape->pigment[0]);
				green = Helper::convertToRgb(shape->pigment[1]);
				blue = Helper::convertToRgb(shape->pigment[2]);
			}
			else {
				red = green = blue = 0;
			}

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}

glm::vec3 Render::pixelRay(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
	cout << setprecision(4);
	cout << "Pixel: [" << x << ", " << y << "] ";
	cout << "Ray: {" << scene->camera->location[0] << \
		" " << scene->camera->location[1] << " " << scene->camera->location[2] << "} ";
	cout << "-> {" << rayDirection[0] << " " << rayDirection[1] << " " << rayDirection[2] << "}\n";
	return rayDirection;
}

void Render::firstHit(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	float t;
	glm::vec3 rayDirection = Render::pixelRay(scene, width, height, x, y);
	shared_ptr<Shape> firstHit = Render::getFirstHit(scene, rayDirection, &t);
	cout << setprecision(4);
	if (t == INT_MAX) {
		cout << "No Hit\n";
	}
	else {
		cout << "T = " << t << "\n";
		cout << "Object Type: " << firstHit->getTypeString().c_str() << "\n";
		cout << "Color: " << firstHit->pigment[0] << " " << \
			firstHit->pigment[1] << " " << \
			firstHit->pigment[2] << "\n";
	}
}

/* PRIVATE */

glm::vec3 Render::calculatePixelRay(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	float right = abs(scene->camera->right[0]) / 2.0f;
	float top = abs(scene->camera->up[1]) / 2.0f;
	float left = -right;
	float bottom = -top;
	float u = (left + (right - left)*(x + 0.5f) / width);
	float v = (bottom + (top - bottom)*(y + 0.5f) / height);
	return glm::normalize(glm::vec3(u, v, -1));
}

shared_ptr<Shape> Render::getFirstHit(shared_ptr<Scene>& scene, const glm::vec3& rayDirection, float* intersectT) {
	shared_ptr<Shape> closestShape;
	float closestT = (float)INT_MAX, t = 0;
	for (unsigned int sh = 0; sh < scene->shapes.size(); sh++) {
		t = calculateFirstHit(scene, rayDirection, scene->shapes[sh]);
		if (t && t < closestT) {
			closestT = t;
			closestShape = scene->shapes[sh];
		}
	}
	if (intersectT != nullptr) {
		*intersectT = closestT;
	}
	return closestShape;
}

float Render::calculateFirstHit(shared_ptr<Scene>& scene, const glm::vec3& rayDirection, const shared_ptr<Shape>& shapeToTest) {
	vector<float> t = shapeToTest->getIntersection(rayDirection, scene->camera->location);
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[0];
	}
	return 0;
}