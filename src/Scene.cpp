#include "Scene.h"

using namespace std;

/* PUBLIC */

vector<shared_ptr<Shape>> Scene::pushShape(shared_ptr<Shape> shape) {
	this->shapes.push_back(shape);
	return this->shapes;
}

shared_ptr<Camera> Scene::createCamera() {
	this->camera = make_shared<Camera>();
	return this->camera;
}

shared_ptr<LightSource> Scene::createLightSource() {
	auto light = make_shared<LightSource>();
	this->lightSources.push_back(light);
	return light;
}

shared_ptr<Sphere> Scene::createSphere() {
	auto sphere = make_shared<Sphere>();
	this->shapes.push_back(sphere);
	return sphere;
}

shared_ptr<Plane> Scene::createPlane() {
	auto plane = make_shared<Plane>();
	this->shapes.push_back(plane);
	return plane;
}

shared_ptr<Triangle> Scene::createTriangle() {
	auto tri = make_shared<Triangle>();
	this->shapes.push_back(tri);
	return tri;
}

shared_ptr<Box> Scene::createBox() {
	auto box = make_shared<Box>();
	this->shapes.push_back(box);
	return box;
}

shared_ptr<Union> Scene::createUnion() {
	auto un = make_shared<Union>();
	this->shapes.push_back(un);
	return un;
}

shared_ptr<Intersect> Scene::createIntersect() {
	auto op = make_shared<Intersect>();
	this->shapes.push_back(op);
	return op;
}

shared_ptr<Difference> Scene::createDiff() {
	auto op = make_shared<Difference>();
	this->shapes.push_back(op);
	return op;
}

void Scene::printInfo() {
	this->camera->printInfo();
	this->printSeparators();
	printf("\n%lu light(s)\n", this->lightSources.size());
	for (size_t i = 0; i < this->lightSources.size(); i++) {
		printf("\nLight[%lu]:\n", i);
		this->lightSources[i]->printInfo();
	}
	this->printSeparators();
	printf("\n%lu object(s)\n", this->shapes.size());
	for (size_t i = 0; i < this->shapes.size(); i++) {
		printf("\nObject[%lu]:\n", i);
		this->shapes[i]->printInfo();
	}
}

/* PRIVATE */

void Scene::printSeparators() {
	fputs("\n---\n", stdout);
}