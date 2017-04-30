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

#ifndef MODES
#define MODES
#define RAYCAST_MODE 0
#define BLINNPHONG_MODE 1
#define COOKTORRANCE_MODE 2
#endif /* MODES */

#define BLACK 0

class Render {
public:
	/*** PROJECT 1 COMMANDS ***/
	static void createOutput(std::shared_ptr<Scene>& scene, int width, int height, unsigned int mode);
	static void raycastPixels(std::shared_ptr<Shape>& shape, unsigned char& retRed, unsigned char& retGreen, unsigned char& retBlue);
	static glm::vec3 pixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static void firstHit(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);

	/*** PROJECT 2 COMMANDS ***/
	static void pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y, unsigned int mode);

private:
	/*** PROJECT 1 COMMANDS ***/
	static glm::vec3 calculatePixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static std::shared_ptr<Shape> getFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, float* intersectT = nullptr);
	static float calculateFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, const std::shared_ptr<Shape>& shapeToTest);

	/*** PROJECT 2 COMMANDS ***/	
	static void shadedPixels(std::shared_ptr<Scene>& scene, 
							 std::shared_ptr<Shape>& shape, glm::vec3& viewRay, float t,
							 unsigned int mode,
							 unsigned char& retRed, unsigned char& retGreen, unsigned char& retBlue);
	static glm::vec3 blinnPhong(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
										std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static glm::vec3 cookTorrance(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
		std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static bool notShaded(float s, float t2);
};
