#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#ifndef GLM_LIBRARY
#define GLM_LIBRARY
#include "glm/glm.hpp"
#endif

#include "Scene.h"
#include "Shape.h"
#include "LightSource.h"
#include "Camera.h"
#include "Finish.h"
#include "Transformation.h"
#include "Flags.h"
#include "Intersection.h"

#ifndef MODES
#define MODES
#define RAYCAST_MODE 0
#define BLINNPHONG_MODE 1
#define COOKTORRANCE_MODE 2
#endif /* MODES */

#define BLACK 0
#define PI 3.14

class Render {
public:
	/*** PROJECT 1 COMMANDS ***/

	static void createOutput(std::shared_ptr<Scene>& scene, int width, int height, Flags flags);
	static glm::vec3 raycastPixels(std::shared_ptr<Shape>& shape);
	static glm::vec3 pixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static void firstHit(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static glm::vec3 getPixelColor(std::shared_ptr<Scene>& scene, glm::vec3 origin, 
		glm::vec3& viewRay, int depth, Flags flags);
	static glm::vec3 calculatePixelRay(std::shared_ptr<Scene>& scene, 
		int width, int height, int x, int y);
	static glm::vec3 calculatePixelRay(std::shared_ptr<Scene>& scene, 
		int width, int height, int x, int y, int s, int m, int n);
	static std::shared_ptr<Shape> getFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, 
		float* intersectT = nullptr, bool transform = true);
	static float calculateFirstHit(glm::vec3 origin, glm::vec3 rayDirection, const std::shared_ptr<Shape>& shapeToTest);

	/*** PROJECT 2 COMMANDS ***/

	static void pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y, Flags flags);

	/*** PROJECT 5 COMMANDS ***/

	static std::shared_ptr<Shape> getFirstHitBVH(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection,
		float* intersectT = nullptr, bool test = false);

	/*** PROJECT 6 COMMANDS ***/
	static std::shared_ptr<Intersection> getFirstHitAsIntersectionObject(std::shared_ptr<Scene>& scene,
		glm::vec3 origin, glm::vec3 rayDirection, float* intersectT, Flags flags);

private: 
	static void getFirstHitBVHRecurse(std::shared_ptr<BoundingBox> currBoundingBox,
		glm::vec3 origin, glm::vec3 rayDirection, std::vector<Intersection> &allIntersects, bool test = false);
};
