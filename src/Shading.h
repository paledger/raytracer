#pragma once

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

class Shading {
public:
	static glm::vec3 shadedPixels(std::shared_ptr<Scene>& scene,
		std::shared_ptr<Shape>& shape, glm::vec3 origin,
		glm::vec3 viewRay, float t, unsigned int mode, bool test = false);
	static glm::vec3 blinnPhong(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
		std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point, bool test = false);
	static glm::vec3 cookTorrance(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
		std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static glm::vec3 cookTorrance_BlinnPhong(std::shared_ptr<Scene>& scene, std::shared_ptr<LightSource>& currLight,
		std::shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point);
	static bool notShaded(float t2);
	static float chiGGX(float v);
	static float GGX_Distribution(glm::vec3 n, glm::vec3 h, float alpha);
	static float GGX_Geometry(glm::vec3 v, glm::vec3 n, glm::vec3 h, float alpha);

	static float getSchlickApproximation(const glm::vec3 n, const float ior, const glm::vec3 v);

};