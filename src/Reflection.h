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

class Reflection {
public: 
	static glm::vec3 getReflection(std::shared_ptr<Scene> scene, std::shared_ptr<Shape> shape, const glm::vec3 point,
		const glm::vec3 d, unsigned int depth, bool test = false);
};