#include "Render.h"
#include "Helper.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

using namespace std;

/* PUBLIC */

/*** PROJECT 2 COMMANDS ***/
void Render::pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y, unsigned int mode) {
	unsigned char red, green, blue;
	float t;
	glm::vec3 rayDirection = Render::pixelRay(scene, width, height, x, y);
	shared_ptr<Shape> shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
	cout << setprecision(4);
	cout << "T = " << t << endl;
	cout << "Object Type: " << shape->getTypeString() << endl;
	if (shape) {
		if (mode == RAYCAST_MODE) {
			Render::raycastPixels(shape, red, green, blue);
		}
		else if (mode == BLINNPHONG_MODE) {
			Render::shadedPixels(scene, shape, rayDirection, t, mode, red, green, blue);
			cout << "BRDF: Blinn-Phong" << endl;
		}
		else if (mode == COOKTORRANCE_MODE) {
			Render::shadedPixels(scene, shape, rayDirection, t, mode, red, green, blue);
			cout << "BRDF: Cook-Torrance" << endl;
		}
	}
	cout << "Color: (" << Helper::convertToRgb(red) << ", " << Helper::convertToRgb(green) << ", " << Helper::convertToRgb(blue) << ")" << endl;
}


/*** PROJECT 1 COMMANDS ***/
void Render::createOutput(shared_ptr<Scene>& scene, int width, int height, unsigned int mode) {
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
			shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
			if (shape) {
				if (mode == RAYCAST_MODE) {
					Render::raycastPixels(shape, red, green, blue);
				}
				else if (mode == BLINNPHONG_MODE || mode == COOKTORRANCE_MODE) {
					Render::shadedPixels(scene, shape, rayDirection, t, mode, red, green, blue);
				} 
			}
			else {
				red = green = blue = BLACK;
			}

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}

void Render::raycastPixels(std::shared_ptr<Shape>& shape, unsigned char& retRed, unsigned char& retGreen, unsigned char& retBlue) {
	retRed = Helper::convertToRgb(shape->pigment[0]);
	retGreen = Helper::convertToRgb(shape->pigment[1]);
	retBlue = Helper::convertToRgb(shape->pigment[2]);
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
	shared_ptr<Shape> firstHit = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
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

/*** PROJECT 1 COMMANDS ***/
/* Blinn-Phong Shading Model */
void Render::shadedPixels(std::shared_ptr<Scene>& scene,
	std::shared_ptr<Shape>& shape, glm::vec3& viewRay, float t,
	unsigned int mode, 
	unsigned char& retRed, unsigned char& retGreen, unsigned char& retBlue)
{
	glm::vec3 point = Helper::getPointOnRay(scene->camera->location, viewRay, t);
	glm::vec3 view = glm::normalize(-viewRay);
	glm::vec3 halfVec, lightVec;
	glm::vec3 lightColor;
	shared_ptr<LightSource> currLight;

	glm::vec3 color = shape->pigment * shape->ambient;
	for (unsigned int l = 0; l < scene->lightSources.size(); l++) {
		if (mode == BLINNPHONG_MODE) {
			color += Render::blinnPhong(scene, scene->lightSources[l], shape, view, point);
		}
		else {
			color += Render::cookTorrance(scene, scene->lightSources[l], shape, view, point);
		}
	}
	retRed = Helper::convertToRgb(color[0]);
	retGreen = Helper::convertToRgb(color[1]);
	retBlue = Helper::convertToRgb(color[2]);
}

glm::vec3 Render::blinnPhong(shared_ptr<Scene>& scene, shared_ptr<LightSource>& currLight, 
						shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point) {
	float t2, epsilon = .0001f;
	float power = (2 / (shape->shininess*shape->shininess) - 2);
	glm::vec3 color;	
	glm::vec3 normal = shape->getNormal(point);
	glm::vec3 lightVec = glm::normalize(currLight->location - point);
	float s = Render::calculateFirstHit(scene, currLight->location, -lightVec, shape);
	Render::getFirstHit(scene, point + lightVec*epsilon, point + lightVec*s, &t2);
	if (Render::notShaded(s, t2)) {
		glm::vec3 halfVec = glm::normalize(view + lightVec);
		glm::vec3 lightColor = currLight->color;
		color += shape->pigment * shape->diffuse * lightColor * glm::max(glm::dot(normal, lightVec), 0.0f);
		color += shape->pigment * shape->specular * lightColor * glm::pow(glm::max(glm::dot(halfVec, normal), 0.0f), power);
	}
	return color;
}

glm::vec3 Render::cookTorrance(shared_ptr<Scene>& scene, shared_ptr<LightSource>& currLight,
	shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point) {
	float t2, epsilon = .0001f;
	float power = (2 / (shape->shininess*shape->shininess) - 2);
	glm::vec3 color;
	glm::vec3 normal = shape->getNormal(point);
	glm::vec3 lightVec = glm::normalize(currLight->location - point);
	float s = Render::calculateFirstHit(scene, currLight->location, -lightVec, shape);
	Render::getFirstHit(scene, point + lightVec*epsilon, point + lightVec*s, &t2);
	if (Render::notShaded(s, t2)) {
		glm::vec3 halfVec = glm::normalize(view + lightVec);
		glm::vec3 lightColor = currLight->color;
		color += shape->pigment * shape->diffuse * lightColor * glm::max(glm::dot(normal, lightVec), 0.0f);
		color += shape->pigment * shape->specular * lightColor * glm::pow(glm::max(glm::dot(halfVec, normal), 0.0f), power);
	}
	return color;
}

bool Render::notShaded(float s, float t2) {
	return true; // t2 > 0 && (t2 == INT_MAX || t2 >= s);
}

/*** PROJECT 1 COMMANDS ***/
glm::vec3 Render::calculatePixelRay(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	float right = glm::length(glm::normalize(scene->camera->right)) / 2.0f;
	float top = glm::length(scene->camera->up) / 2.0f;
	float left = -right;
	float bottom = -top;
	float u = (left + (right - left)*(x + 0.5f) / width);
	float v = (bottom + (top - bottom)*(y + 0.5f) / height);
	glm::vec3 l = glm::normalize(scene->camera->look_at - scene->camera->location);
	return glm::normalize(u*scene->camera->right + \
						  v*scene->camera->up +	\
						  l);
}

shared_ptr<Shape> Render::getFirstHit(shared_ptr<Scene>& scene, const glm::vec3& origin, glm::vec3& rayDirection, float* intersectT) {
	shared_ptr<Shape> closestShape;
	float closestT = (float)INT_MAX, t = 0;
	for (unsigned int sh = 0; sh < scene->shapes.size(); sh++) {
		t = calculateFirstHit(scene, origin, rayDirection, scene->shapes[sh]);
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

float Render::calculateFirstHit(shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, const shared_ptr<Shape>& shapeToTest) {
	vector<float> t = shapeToTest->getIntersection(rayDirection, origin);
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[0];
	}
	return 0;
}