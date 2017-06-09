#pragma once

#include "Shape.h"
#include "Flags.h"
#include "Scene.h"
#include "Intersection.h"

#include <memory.h>
#include <memory> 
#include <vector> 

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Ambient {
public:
	static glm::vec3 getAmbient(std::shared_ptr<Scene> scene, std::shared_ptr<Intersection> intersect, int depth, Flags flags);
	static glm::vec3 getNormalAmbient(std::shared_ptr<Shape> shape);
	static glm::vec3 getMonteCarloAmbient(std::shared_ptr<Scene> scene, std::shared_ptr<Intersection> intersect, int depth, Flags flags);

private: 
	static glm::vec3 generateHemisphereSamplePoint(glm::vec3 up, glm::vec3 normal, Flags flags);
	static glm::vec3 generateCosineWeightedPoint(float u, float v, Flags flags);
	static glm::vec3 alignSampleVector(glm::vec3 sample, glm::vec3 up, glm::vec3 normal, Flags flags);
	static glm::vec2 generateRandomUV();
};