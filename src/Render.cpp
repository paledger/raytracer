#include "Render.h"
#include "Helper.h"
#include "Shading.h"
#include "Reflection.h"
#include "Refraction.h"
#include "Contribution.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

using namespace std;

/* PUBLIC */

/*** PROJECT 6 COMMANDS ***/
shared_ptr<Intersection> Render::getFirstHitAsIntersectionObject(shared_ptr<Scene>& scene,
	glm::vec3 origin, glm::vec3 rayDirection, float* intersectT, Flags flags) 
{
	shared_ptr<Shape> shape;
	shared_ptr<Intersection> intersect = nullptr;

	if (flags.bvh) {
		shape = getFirstHitBVH(scene, origin, rayDirection, intersectT, flags.bvhtest);
	}
	else {
		shape = getFirstHit(scene, origin, rayDirection, flags, intersectT);
	}

	if (shape) {
		intersect = make_shared<Intersection>(shape, *intersectT);
		intersect->setTransformedInfo(origin, rayDirection);
	}
	return intersect;
}


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
	Flags flags = Flags();
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
				shared_ptr<Transformation> currTransform = currBoundingBox->objects[sh]->getTransformation();
				glm::vec3 tOrigin = currTransform->transformPoint(origin);
				glm::vec3 tRay = currTransform->transformVector(rayDirection);
				t = Helper::calculateFirstHit(tOrigin, tRay, currBoundingBox->objects[sh], flags);
				
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

		shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, flags, &t);
		if (shape) {
			cout << setprecision(4);
			shared_ptr<Transformation> transform = shape->getTransformation();
			glm::vec3 transformedOrigin = transform->transformPoint(scene->camera->location);
			glm::vec3 transformedRay = transform->transformVector(rayDirection);

			if (flags.test) {
				Render::pixelRay(scene, width, height, x, y);

				cout << "Transformed Ray: {" << transformedOrigin.x << \
					" " << transformedOrigin.y << " " << transformedOrigin.z << "} ";
				cout << "-> {" << transformedRay[0] << " " << transformedRay[1] << " " << transformedRay[2] << "}\n";
				cout << "Object Type: " << shape->getTypeString() << endl << endl;

			}
			if (flags.csgtest) {
				cout << "Object Type: " << shape->getTypeString() << endl << endl;
			}
			color = Render::getPixelColor(scene, scene->camera->location, rayDirection, 0, flags);
			if (flags.test || flags.csgtest) {
				color = Helper::convertToRgb(color);
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
	float t;

	if (flags.test) {
		cout << "TESTING GET PIXEL COLOR " << endl;
	}

	shared_ptr<Intersection> intersect = Render::getFirstHitAsIntersectionObject(scene, origin, viewRay, &t, flags);
	viewRay = glm::normalize(viewRay);

	if (!intersect) {
		local_color = glm::vec3(0.0f, 0.0f, 0.0f); // set to all black
		total_color = local_color;
	}
	else {
		shared_ptr<Shape> shape = intersect->shape;
		glm::vec3 tRay = intersect->tRay;
		glm::vec3 tOrigin = intersect->tOrigin;
		glm::vec3 wPt = intersect->wPt;
		glm::vec3 oPt = intersect->oPt;
		glm::vec3 n = intersect->n;

		// get contribution amounts
		Contribution contrib = Contribution(intersect, flags);

		// get local color
		if (flags.test) {
			cout << "GETTING LOCAL" << endl;
		}
		if (flags.mode == RAYCAST_MODE) {
			local_color = Render::raycastPixels(shape);
		}
		else if (flags.mode == BLINNPHONG_MODE || flags.mode == COOKTORRANCE_MODE) {
			if (flags.test) {
				cout << "T: " << t << endl;
			}
			local_color = Shading::shadedPixels(scene, intersect, depth, flags);
		}

		// reflection
		if (shape->getFinish()->reflection && depth <= 6) {
			glm::vec3 reflectionVec = viewRay - 2 * glm::dot(viewRay, n) * n;
			if (flags.test) {
				cout << "\nGETTING REFLECTION" << endl;
				cout << "reflectionVec: " << reflectionVec.x << " " << reflectionVec.y << " " << reflectionVec.z << endl;
			}
			reflect_color = getPixelColor(scene, wPt + n * 0.001f, reflectionVec, depth + 1, flags);  //Reflection::getReflection(scene, shape, oPt, viewRay, depth, flags);
		}

		// refraction
		if (shape->getFinish()->filter && depth <= 6) {
			// get refraction amount
			if (flags.test) {
				cout << "\nGETTING REFRACTION " << depth << endl;
			}

			glm::vec3 attenuation = Refraction::getBeersAttenuation(shape->getFinish()->pigment, t);

			float dir, snellRatio;
			float transmission = shape->getFinish()->filter;

			if ((dir = glm::dot(viewRay, n)) <= 0) { // entering
				if (flags.test) {
					cout << "entering" << endl;
				}
				snellRatio = 1.0f / shape->getFinish()->ior;
			}
			else if (dir > 0) { // exiting
				if (flags.test) {
					cout << "exiting" << endl;
				}
				n = -n;
				snellRatio = shape->getFinish()->ior;
			}

			float d_dot_n = glm::dot(viewRay, n);
			glm::vec3 d_dn_n = viewRay - d_dot_n * n;
			float insideSqrt = (float)glm::pow(snellRatio, 2.0f) * (1.f - (float)glm::pow(d_dot_n, 2.0f));
			glm::vec3 n_sqrt = n * (float)glm::sqrt(1 - insideSqrt);
			glm::vec3 transmissionVec = snellRatio * d_dn_n - n_sqrt;
			glm::vec3 epsilonVec = n * 0.001f;
			glm::vec3 intersectionPt = wPt - epsilonVec;

			if (flags.test) {
				cout << "intersectionPt: " << intersectionPt.x << " " << intersectionPt.y << " " << intersectionPt.z << endl;
				cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
				cout << "d_dot_n: " << d_dot_n << endl;
				cout << "d_dn_n: " << d_dn_n.x << " " << d_dn_n.y << " " << d_dn_n.z << endl;
				cout << "insideSqrt" << insideSqrt << endl;
				cout << "n_sqrt: " << n_sqrt.x << " " << n_sqrt.y << " " << n_sqrt.z << endl;
				cout << "refractionVec: " << transmissionVec.x << " " << transmissionVec.y << " " << transmissionVec.z << endl;
			}

			transmit_color = Render::getPixelColor(scene, intersectionPt, transmissionVec, depth + 1, flags); 
			transmit_color = attenuation * transmit_color;
		}

		total_color = contrib.local * local_color + \
			contrib.reflection * reflect_color + \
			contrib.refraction * transmit_color;

		if (flags.test || (flags.gitest && depth == 0) || flags.csgtest) {
			cout << endl;
			cout << "local: " << contrib.local << " * " <<
				Helper::convertToRgb(local_color.x) << " " << Helper::convertToRgb(local_color.y) << " " << Helper::convertToRgb(local_color.z) << endl;
			cout << "reflect: " << contrib.reflection << " * " <<
				reflect_color.x << " " << reflect_color.y << " " << reflect_color.z << endl;
			cout << "refract: " << contrib.refraction << " * " <<
				transmit_color.x << " " << transmit_color.y << " " << transmit_color.z << endl;
			cout << endl;
		}
	}

	return total_color;
}


glm::vec3 Render::raycastPixels(std::shared_ptr<Shape>& shape) 
{
	return shape->getFinish()->pigment;
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

void Render::firstHit(shared_ptr<Scene>& scene, int width, int height, int x, int y, Flags flags) {
	float t;
	glm::vec3 rayDirection = Render::pixelRay(scene, width, height, x, y);
	shared_ptr<Shape> firstHit = Render::getFirstHit(scene, scene->camera->location, rayDirection, flags, &t);
	shared_ptr<Finish> finish = firstHit->getFinish();
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
	glm::vec3 origin, glm::vec3 rayDirection, Flags flags, float* intersectT)
{
	shared_ptr<Shape> closestShape;
	shared_ptr<Transformation> currTransform;
	float closestT = (float)INT_MAX, t = -1;
	for (unsigned int sh = 0; sh < scene->shapes.size(); sh++) {
		if (flags.transform) {
			currTransform = scene->shapes[sh]->getTransformation();
			glm::vec3 tOrigin = currTransform->transformPoint(origin);
			glm::vec3 tRay = currTransform->transformVector(rayDirection);
			t = Helper::calculateFirstHit(tOrigin, tRay, scene->shapes[sh], flags);
		}
		else {
			t = Helper::calculateFirstHit(origin, rayDirection, scene->shapes[sh], flags);
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

