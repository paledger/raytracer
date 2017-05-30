#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "glm/glm.hpp"
#include "Shape.h"
#include "Camera.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Box.h"
#include "BoundingBox.h"

class Scene
{
private:
	void printSeparators();

public:
	std::vector<std::shared_ptr<Shape>> pushShape(std::shared_ptr<Shape> shape);
	std::shared_ptr<Camera> createCamera();
	std::shared_ptr<LightSource> createLightSource();
	std::shared_ptr<Sphere> createSphere();
	std::shared_ptr<Plane> createPlane();
	std::shared_ptr<Triangle> createTriangle();
	std::shared_ptr<Box> createBox();
	void printInfo();

	std::vector<std::shared_ptr<Shape>> shapes;
	std::shared_ptr<Camera> camera;
	std::vector<std::shared_ptr<LightSource>> lightSources;
	std::shared_ptr<BoundingBox> boundingBoxRoot = std::make_shared<BoundingBox>();
};