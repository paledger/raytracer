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

/*** PROJECT 5 COMMANDS ***/

shared_ptr<Shape> Render::getFirstHitBVH(shared_ptr<Scene>& scene,
	glm::vec3 origin, glm::vec3 rayDirection, float* intersectT, bool test)
{
	shared_ptr<Shape> closestShape;
	float closestT = (float)INT_MAX;
	vector<Intersection> allIntersects;

	if (test) {
		cout << "\nGETTING FIRST HITS" << endl;
	}
	getFirstHitBVHRecurse(scene->boundingBoxRoot, origin, rayDirection, allIntersects, test);

	if (test) {
		cout << "num intersections: " << allIntersects.size() << endl;
	}
	for (unsigned int i = 0; i < allIntersects.size(); i++) {
		Intersection curr = allIntersects[i];
		if (test) {
			cout << "Closest shape: " << curr.shape->getTypeString() << endl;
			cout << "Closest t: " << curr.t << endl;
		}
		if (curr.t < closestT) {
			closestT = curr.t;
			closestShape = curr.shape;
		}
	}

	if (intersectT != nullptr) {
		*intersectT = closestT;
	}
	if (test) {
		cout << "OUTTY" << endl;
	}
	return closestShape;
}

void Render::getFirstHitBVHRecurse(shared_ptr<BoundingBox> currBoundingBox,
	glm::vec3 origin, glm::vec3 rayDirection, vector<Intersection> &allIntersects, bool test)
{
	vector<float> currTs = currBoundingBox->getIntersection(rayDirection, origin);
	float t, closestT = INFINITY;
	shared_ptr<Shape> closestShape;
	if (!currTs.empty()) {
		if (test) {
			cout << "found a bounding box!" << endl;
			cout << "min: " << currBoundingBox->min.x << " " << currBoundingBox->min.y << " " << currBoundingBox->min.z << endl;
			cout << "max: " << currBoundingBox->max.x << " " << currBoundingBox->max.y << " " << currBoundingBox->max.z << endl << endl;
		}
		if (!currBoundingBox->left && !currBoundingBox->right) {
			if (test) {
				cout << "size of objects list " << currBoundingBox->objects.size() << endl;
			}
			for (unsigned int sh = 0; sh < currBoundingBox->objects.size(); sh++) {
				shared_ptr<Shape> currShape = currBoundingBox->objects[sh];
				if (test) {
					cout << "intersected shape: " << currShape->getTypeString() << endl;
				}
				shared_ptr<Transformation> currTransform = currBoundingBox->objects[sh]->transform;
				glm::vec3 tOrigin = currTransform->transformPoint(origin);
				glm::vec3 tRay = currTransform->transformVector(rayDirection);
				t = calculateFirstHit(tOrigin, tRay, currBoundingBox->objects[sh]);
				
				if (t > 0 && t < closestT) {
					closestT = t;
					closestShape = currBoundingBox->objects[sh];
				}
			}
			if (closestT != INFINITY) {
				if (test) {
					cout << "PUSHING!!" << endl;
				}
				Intersection intersect = Intersection(closestShape, closestT);
				allIntersects.push_back(intersect);
			}
		}
		else {
			if (currBoundingBox->left) {
				getFirstHitBVHRecurse(currBoundingBox->left, origin, rayDirection, allIntersects, test);
			}
			if (currBoundingBox->right) {
				getFirstHitBVHRecurse(currBoundingBox->right, origin, rayDirection, allIntersects, test);
			}
		}
	}
}

/*** PROJECT 2 COMMANDS ***/

void Render::pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y,
	Flags flags)
{
	if (flags.bvh && flags.bvhtest) {
		cout << "BUILD TREE " << endl;
		scene->boundingBoxRoot->recursiveTreeBuild(scene->shapes, 0, flags.bvhtest);

		cout << "\nRECURSE PRINT " << endl;
		scene->boundingBoxRoot->recursePrint(0);

		glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
		glm::vec3 color = Render::getPixelColor(scene, scene->camera->location, rayDirection, 0, flags);
		if (flags.bvhtest) {
			cout << "\nFinal Color: (" << color.r << ", " << color.g << ", " << color.b << ")" << endl;
		}
	}
	else {
		float t;
		glm::vec3 color;
		shared_ptr<Shape> shape;
		glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);

		shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
		if (shape) {
			cout << setprecision(4);
			shared_ptr<Transformation> transform = shape->transform;
			glm::vec3 transformedOrigin = transform->transformPoint(scene->camera->location);
			glm::vec3 transformedRay = transform->transformVector(rayDirection);

			Render::pixelRay(scene, width, height, x, y);

			if (flags.test) {
				cout << "Transformed Ray: {" << transformedOrigin.x << \
					" " << transformedOrigin.y << " " << transformedOrigin.z << "} ";
				cout << "-> {" << transformedRay[0] << " " << transformedRay[1] << " " << transformedRay[2] << "}\n";
				cout << "Object Type: " << shape->getTypeString() << endl << endl;

			}

			color = Render::getPixelColor(scene, scene->camera->location, rayDirection, 0, flags);
			if (flags.test) {
				cout << "Final Color: (" << color.r << ", " << color.g << ", " << color.b << ")" << endl;
			}
		}
		else {
			if (flags.test) {
				cout << "No Hit" << endl;
			}
		}
	}
}


/*** PROJECT 1 COMMANDS ***/

void Render::createOutput(shared_ptr<Scene>& scene, int width, int height, Flags flags) 
{
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);
	shared_ptr<Shape> shape;
	glm::vec3 rayDirection, color;
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	unsigned int ss = flags.ss;
	unsigned int supersamples = ss*ss;

	if (flags.bvh) {
		scene->boundingBoxRoot->recursiveTreeBuild(scene->shapes, 0, flags.bvhtest);
	}
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			unsigned char red, green, blue;
			if (ss == 1) {
				glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
				color = Render::getPixelColor(scene, scene->camera->location, rayDirection, 0, flags);
			}
			else {
				color = glm::vec3(0.0f);
				for (unsigned int m = 0; m < ss; m++) {
					for (unsigned int n = 0; n < ss; n++) {
						glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y, ss, m, n);
						color += Render::getPixelColor(scene, scene->camera->location, rayDirection, 0, flags);
					}
				}
				color = color / (float)(supersamples);
			}

			red = Helper::convertToRgb(color.r);
			green = Helper::convertToRgb(color.g);
			blue = Helper::convertToRgb(color.b);

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}
	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}


glm::vec3 Render::getPixelColor(shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3& viewRay, int depth, Flags flags)
{
	glm::vec3 total_color, reflect_color, transmit_color, local_color;
	float t, transmission_contrib, local_contrib, reflect_contrib;
	shared_ptr<Shape> shape;
	if (flags.bvh) {
		shape = Render::getFirstHitBVH(scene, origin, viewRay, &t, flags.bvhtest);
	}
	else {
		shape = Render::getFirstHit(scene, origin, viewRay, &t, true);
	}
	viewRay = glm::normalize(viewRay);

	if (!shape) {
		local_color = glm::vec3(0.0f, 0.0f, 0.0f); // set to all black
		total_color = local_color;
	}
	else {
		float ior = shape->finish->ior;

		glm::vec3 tRay = shape->transform->transformVector(viewRay);
		glm::vec3 tOrigin = shape->transform->transformPoint(origin);
		glm::vec3 wPt = Helper::getPointOnRay(origin, viewRay, t);
		glm::vec3 oPt = Helper::getPointOnRay(tOrigin, tRay, t);

		// get contribution amounts
		float filter = shape->finish->filter;
		float reflection = shape->finish->reflection;

		local_contrib = (1 - filter) * (1 - reflection);
		if (flags.fresnel) {
			float fresnel_reflectance = Shading::getSchlickApproximation(shape->getNormal(oPt), ior, tRay);
			reflect_contrib = (1 - filter) * reflection * fresnel_reflectance;
			transmission_contrib = filter * (1 - fresnel_reflectance);
		} 
		else {
			reflect_contrib = (1 - filter) * reflection;
			transmission_contrib = filter;
		}

		// get local color
		if (flags.mode == RAYCAST_MODE) {
			local_color = Render::raycastPixels(shape);
		}
		else if (flags.mode == BLINNPHONG_MODE || flags.mode == COOKTORRANCE_MODE) {
			if (flags.test) {
				cout << "T: " << t << endl;
			}
			local_color = Shading::shadedPixels(scene, shape, origin, viewRay, t, flags);
		}
		else {
			local_color = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		if (shape->finish->reflection) {
			// get reflection amount
			if (flags.test) {
				cout << "local: " << local_color.x << " " << local_color.y << " " << local_color.z << endl;
				cout << "\nGETTING REFLECTION" << endl;
			}
			reflect_color = Reflection::getReflection(scene, shape, oPt, viewRay, depth, flags);
		}
		if (shape->finish->filter) {
			// get refraction amount
			if (flags.test) {
				cout << "\nGETTING REFRACTION" << endl;
			}
			// beer's law
			float d = t;
			glm::vec3 absorbance = (glm::vec3(1.f, 1.f, 1.f) - shape->finish->pigment)*0.15f*-d;
			glm::vec3 attenuation = glm::vec3(glm::pow(glm::e<float>(), absorbance.r),
				glm::pow(glm::e<float>(), absorbance.g),
				glm::pow(glm::e<float>(), absorbance.b));
			transmit_color = attenuation * Refraction::getRefraction(scene, shape, oPt, viewRay, depth, flags);

		}
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

glm::vec3 Render::calculatePixelRay(shared_ptr<Scene>& scene, 
	int width, int height, int x, int y) 
{
	glm::vec3 pixelRay;
	float right = glm::length(glm::normalize(scene->camera->right)) / 2.0f;
	float top = glm::length(scene->camera->up) / 2.0f;
	float left = -right;
	float bottom = -top;
	float u = (left + (right - left)*(x + 0.5f) / width);
	float v = (bottom + (top - bottom)*(y + 0.5f) / height);
	glm::vec3 l = glm::normalize(scene->camera->look_at - scene->camera->location);
	pixelRay = glm::normalize(u*scene->camera->right + \
						  v*scene->camera->up +	\
						  l);
	return pixelRay;
}

glm::vec3 Render::calculatePixelRay(shared_ptr<Scene>& scene, int width, int height, 
	int x, int y, int s, int m, int n) 
{
	float right = glm::length(glm::normalize(scene->camera->right)) / 2.0f;
	float top = glm::length(scene->camera->up) / 2.0f;
	float left = -right;
	float bottom = -top;
	float u = -0.5f + (x + ((m + 0.5f) / s)) / width;
	float v = -0.5f + (y + ((n + 0.5f) / s)) / height;
	glm::vec3 l = glm::normalize(scene->camera->look_at - scene->camera->location);
	return glm::normalize(u*scene->camera->right + \
		v*scene->camera->up + \
		l);
}

shared_ptr<Shape> Render::getFirstHit(shared_ptr<Scene>& scene, 
	glm::vec3 origin, glm::vec3 rayDirection, float* intersectT, bool transform)
{
	shared_ptr<Shape> closestShape;
	shared_ptr<Transformation> currTransform;
	float closestT = (float)INT_MAX, t = -1;
	for (unsigned int sh = 0; sh < scene->shapes.size(); sh++) {
		if (transform) {
			currTransform = scene->shapes[sh]->transform;
			glm::vec3 tOrigin = currTransform->transformPoint(origin);
			glm::vec3 tRay = currTransform->transformVector(rayDirection);
			t = calculateFirstHit(tOrigin, tRay, scene->shapes[sh]);
		}
		else {
			t = calculateFirstHit(origin, rayDirection, scene->shapes[sh]);
		}
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

float Render::calculateFirstHit(glm::vec3 origin, 
	glm::vec3 rayDirection, const shared_ptr<Shape>& shapeToTest) 
{
	vector<float> t = shapeToTest->getIntersection(rayDirection, origin);
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[0];
	}
	return -1;
}