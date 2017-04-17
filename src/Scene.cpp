#include "Scene.h"
#include "Sphere.cpp"
#include "Plane.cpp"
#include "Camera.cpp"
#include "LightSource.cpp"

using namespace std;

class Scene
{
public: 
	vector<shared_ptr<Shape>> shapes;
	shared_ptr<Camera> camera;
	vector<shared_ptr<LightSource>> lightSources;
	
	vector<shared_ptr<Shape>> pushShape(shared_ptr<Shape> shape) {
		shapes.push_back(shape);
		return shapes;
	}

	shared_ptr<Camera> createCamera() {
		camera = make_shared<Camera>();
		return camera;
	}

	shared_ptr<LightSource> createLightSource() {
		auto light = make_shared<LightSource>();
		lightSources.push_back(light);
		return light;
	}

	shared_ptr<Sphere> createSphere() {
		auto sphere = make_shared<Sphere>();
		shapes.push_back(sphere);
		return sphere;
	}

	shared_ptr<Plane> createPlane() {
		auto plane = make_shared<Plane>();
		shapes.push_back(plane);
		return plane;
	}

	void printInfo() {
		camera->printInfo();
		printSeparators();
		printf("\n%d light(s)\n", lightSources.size());
		for (size_t i = 0; i < lightSources.size(); i++) {
			printf("\nLight[%d]\n", i);
			lightSources[i]->printInfo();
		}
		printSeparators();
		printf("\n%d object(s)\n", shapes.size());
		for (size_t i = 0; i < shapes.size(); i++) {
			printf("\nObject[%d]\n", i);
			shapes[i]->printInfo();
		}
	}

	glm::vec3 calculatePixelRay(int width, int height, int x, int y) {
		float right = abs(camera->right[0]) / 2.0;
		float top = abs(camera->up[1]) / 2.0;
		float left = -right;
		float bottom = -top;
		float u = (left + (right - left)*(x + 0.5) / width);
		float v = (bottom + (top - bottom)*(y + 0.5) / height);
		return glm::normalize(glm::vec3(u, v, -1));
	}

	shared_ptr<Shape> getFirstHit(const glm::vec3& rayDirection, float* intersectT = nullptr) {
		shared_ptr<Shape> closestShape;
		float closestT = INT_MAX, t;
		for (size_t sh = 0; sh < shapes.size(); sh++) {
			t = calculateFirstHit(rayDirection, shapes[sh]);
			if (t && t < closestT) {
				closestT = t;
				closestShape = shapes[sh];
			}
		}
		if (intersectT != nullptr) {
			*intersectT = closestT;
		}
		return closestShape;
	}

	float calculateFirstHit(const glm::vec3& rayDirection, const shared_ptr<Shape>& shapeToTest) {
		vector<float> t = shapeToTest->getIntersection(rayDirection, camera->location);
		if (!t.empty()) {
			sort(t.begin(), t.end());
			return t[0];
		}
		return NULL;
	}

	/*shared_ptr<Shape> findIntersections(int width, int height) {
		glm::vec3 currVec = glm::vec3(0.0, 0.0, 0.0);
		vector<shared_ptr<Shape>> intersections;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				calculateFirstHit(width, height, i, j);
			}
		}
	}*/
private:
	void printSeparators() {
		fputs("\n---\n", stdout);
	}
};