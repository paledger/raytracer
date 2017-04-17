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
		printf("\n%lu light(s)\n", lightSources.size());
		for (size_t i = 0; i < lightSources.size(); i++) {
			printf("\nLight[%lu]\n", i);
			lightSources[i]->printInfo();
		}
		printSeparators();
		printf("\n%lu object(s)\n", shapes.size());
		for (size_t i = 0; i < shapes.size(); i++) {
			printf("\nObject[%lu]\n", i);
			shapes[i]->printInfo();
		}
	}

	glm::vec3 pixelRay(int width, int height, int x, int y) {
		glm::vec3 rayDirection = this->calculatePixelRay(width, height, x, y);
		cout << setprecision(4);
		cout << "Pixel: [" << x << " " << y << "] ";
		cout << "Ray: {" << this->camera->location[0] << \
			" " << this->camera->location[1] << " " << this->camera->location[2] << "} ";
		cout << "-> {" << rayDirection[0] << " " << rayDirection[1] << " " << rayDirection[2] << "}\n";
		return rayDirection;
	}

	void firstHit(int width, int height, int x, int y) {
		float t;
		glm::vec3 rayDirection = this->pixelRay(width, height, x, y);
		shared_ptr<Shape> firstHit = this->getFirstHit(rayDirection, &t);
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

	glm::vec3 calculatePixelRay(int width, int height, int x, int y) {
		float right = abs(camera->right[0]) / 2.0f;
		float top = abs(camera->up[1]) / 2.0f;
		float left = -right;
		float bottom = -top;
		float u = (left + (right - left)*(x + 0.5f) / width);
		float v = (bottom + (top - bottom)*(y + 0.5f) / height);
		return glm::normalize(glm::vec3(u, v, -1));
	}

	shared_ptr<Shape> getFirstHit(const glm::vec3& rayDirection, float* intersectT = nullptr) {
		shared_ptr<Shape> closestShape;
		float closestT = (float)INT_MAX, t = 0;
		for (unsigned int sh = 0; sh < shapes.size(); sh++) {
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
		return 0;
	}

private:
	void printSeparators() {
		fputs("\n---\n", stdout);
	}
};