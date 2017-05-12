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
	static void createOutput(std::shared_ptr<Scene>& scene, int width, int height, unsigned int mode);
	static glm::vec3 raycastPixels(std::shared_ptr<Shape>& shape);
	static glm::vec3 pixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static void firstHit(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static glm::vec3 getPixelColor(std::shared_ptr<Scene>& scene, const glm::vec3 origin, 
		glm::vec3& viewRay, unsigned int mode, int depth, bool test = false);
	static glm::vec3 calculatePixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static std::shared_ptr<Shape> getFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, float* intersectT = nullptr);
	static float calculateFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, const std::shared_ptr<Shape>& shapeToTest);

	/*** PROJECT 2 COMMANDS ***/
	static void pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y, unsigned int mode);

};
