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

	/*** PROJECT 2 COMMANDS ***/
	static void pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y, unsigned int mode);

private:
	/*** PROJECT 1 COMMANDS ***/
	static glm::vec3 getPixelColor(std::shared_ptr<Scene>& scene, std::shared_ptr<Shape>& shape, 
		const glm::vec3 origin, glm::vec3& viewRay, unsigned int mode, float t, bool test = false);
	static glm::vec3 calculatePixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static std::shared_ptr<Shape> getFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, float* intersectT = nullptr);
	static float calculateFirstHit(std::shared_ptr<Scene>& scene, glm::vec3 origin, glm::vec3 rayDirection, const std::shared_ptr<Shape>& shapeToTest);

	/*** PROJECT 2 COMMANDS ***/	
	static glm::vec3 shadedPixels(std::shared_ptr<Scene>& scene, 
							 std::shared_ptr<Shape>& shape, glm::vec3 origin, 
							glm::vec3& viewRay, float t, unsigned int mode);
	static glm::vec3 blinnPhong(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
										std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static glm::vec3 cookTorrance(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
		std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static glm::vec3 cookTorrance_BlinnPhong(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
		std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static bool notShaded(float t2);
	static float chiGGX(float v);
	static float GGX_Distribution(glm::vec3 n, glm::vec3 h, float alpha);
	static float GGX_Geometry(glm::vec3 v, glm::vec3 n, glm::vec3 h, float alpha);

	/*** PROJECT 3 COMMANDS ***/
	static glm::vec3 getReflection(std::shared_ptr<Scene> scene, std::shared_ptr<Shape> shape, glm::vec3 point, 
		glm::vec3& d, unsigned int depth, bool test = false);


};
