#include "Render.h"
#include "Helper.h"
#include "Shading.h"
#include "Reflection.h"
#include "Refraction.h"

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
	glm::vec3 color;
	glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
	shared_ptr<Shape> shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
	if (shape) {
		Render::pixelRay(scene, width, height, x, y);
		cout << setprecision(4);
		cout << "T = " << t << endl;
		cout << "Object Type: " << shape->getTypeString() << endl;

		color = Render::getPixelColor(scene, scene->camera->location, rayDirection, mode, true);

		red = Helper::convertToRgb(color[0]);
		green = Helper::convertToRgb(color[1]);
		blue = Helper::convertToRgb(color[2]);
		cout << "Color: (" << (int)red << ", " << (int)green << ", " << (int)blue << ")" << endl;
	}
	else {
		cout << "No Hit" << endl;
	}
}


/*** PROJECT 1 COMMANDS ***/
void Render::createOutput(shared_ptr<Scene>& scene, int width, int height, unsigned int mode) {
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);
	shared_ptr<Shape> shape;
	glm::vec3 rayDirection, color;
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	glm::vec3 reflectionColor;
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			unsigned char red, green, blue;

			glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
			color = Render::getPixelColor(scene, scene->camera->location, rayDirection, mode);

			red = Helper::convertToRgb(color[0]);
			green = Helper::convertToRgb(color[1]);
			blue = Helper::convertToRgb(color[2]);

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}
	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}


glm::vec3 Render::getPixelColor(shared_ptr<Scene>& scene, const glm::vec3 origin, glm::vec3& viewRay, unsigned int mode, 
	bool test)
{
	glm::vec3 total_color, reflect_color, transmit_color, local_color;
	float t, transmission_contrib, local_contrib, reflect_contrib;
	shared_ptr<Shape> shape = Render::getFirstHit(scene, origin, viewRay, &t);

	//cout << "OKAY" << endl;
	if (!shape) {
		local_color = glm::vec3(0.0f, 0.0f, 0.0f); // set to all black
		total_color = local_color;
		//cout << "FUN" << endl;
	}
	else {
		//cout << "MAYBE" << endl;
		// beer's law values
		float ior = shape->finish->ior;
		glm::vec3 intersectionPt = Helper::getPointOnRay(origin, viewRay, t);
		float fresnel_reflectance = Shading::getSchlickApproximation(shape->getNormal(intersectionPt), ior, viewRay);

		// get contribution amounts
		float filter = shape->finish->filter;
		float reflection = shape->finish->reflection;

		local_contrib = (1 - filter) * (1 - reflection);
		reflect_contrib = (1 - filter) * reflection + filter * fresnel_reflectance;
		transmission_contrib = filter * (1 - fresnel_reflectance);

		// get local color
		if (mode == RAYCAST_MODE) {
			local_color = Render::raycastPixels(shape);
		}
		else if (mode == BLINNPHONG_MODE || mode == COOKTORRANCE_MODE) {
			local_color = Shading::shadedPixels(scene, shape, origin, viewRay, t, mode, test);
		}
		else {
			local_color = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		// get reflection amount
		if (test) {
			cout << "local: " << local_color.x << " " << local_color.y << " " << local_color.z << endl;
			cout << "\nGETTING REFLECTION" << endl;
		}
		reflect_color = Reflection::getReflection(scene, shape, intersectionPt, viewRay, 0, test);

		// get refraction amount
		if (test) {
			//cout << "GETTING REFRACTION" << endl;
		}
		transmit_color = Refraction::getRefraction(scene, shape, intersectionPt, viewRay, 0, test);

		total_color = local_contrib * local_color + \
			reflect_contrib * reflect_color + \
			transmission_contrib * transmit_color;
	}

	return total_color;
}


glm::vec3 Render::raycastPixels(std::shared_ptr<Shape>& shape) 
{
	return shape->finish->pigment;
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
	shared_ptr<Finish> finish = firstHit->finish;
	cout << setprecision(4);
	if (t == INT_MAX) {
		cout << "No Hit\n";
	}
	else {
		cout << "T = " << t << "\n";
		cout << "Object Type: " << firstHit->getTypeString().c_str() << "\n";
		cout << "Color: " << finish->pigment[0] << " " << \
			finish->pigment[1] << " " << \
			finish->pigment[2] << "\n";
	}
}

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

shared_ptr<Shape> Render::getFirstHit(shared_ptr<Scene>& scene, 
	glm::vec3 origin, glm::vec3 rayDirection, float* intersectT)
{
	shared_ptr<Shape> closestShape;
	float closestT = (float)INT_MAX, t = -1;
	for (unsigned int sh = 0; sh < scene->shapes.size(); sh++) {
		t = calculateFirstHit(scene, origin, rayDirection, scene->shapes[sh]);
		if (t > 0 && t < closestT) {
			closestT = t;
			closestShape = scene->shapes[sh];
		}
	}
	if (intersectT != nullptr) {
		*intersectT = closestT;
	}
	return closestShape;
}

float Render::calculateFirstHit(shared_ptr<Scene>& scene,  glm::vec3 origin, 
	glm::vec3 rayDirection, const shared_ptr<Shape>& shapeToTest) 
{
	vector<float> t = shapeToTest->getIntersection(rayDirection, origin);
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[0];
	}
	return -1;
}