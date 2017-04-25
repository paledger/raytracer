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
#include "Lightsource.h"
#include "Camera.h"



class Render {
public:
	static void render(std::shared_ptr<Scene>& scene, int width, int height);
	static glm::vec3 pixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static void firstHit(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);

private:
	static glm::vec3 calculatePixelRay(std::shared_ptr<Scene>& scene, int width, int height, int x, int y);
	static std::shared_ptr<Shape> Render::getFirstHit(std::shared_ptr<Scene>& scene, const glm::vec3& rayDirection, float* intersectT = nullptr);
	static float calculateFirstHit(std::shared_ptr<Scene>& scene, const glm::vec3& rayDirection, const std::shared_ptr<Shape>& shapeToTest);
};
