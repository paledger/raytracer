#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>
#include <cstring>

#ifndef GLM_LIBRARY
#define GLM_LIBRARY
#include "glm/glm.hpp"
#endif

#include "Scene.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "LightSource.h"


class MyParser
{
public:
	std::ifstream sceneFile;

	bool openFile(const std::string& fileName);
	int parseFileToScene(std::shared_ptr<Scene>  scene);

private:
	void removeComments(std::string& strBuffer);
	void handleChunk(std::string& strChunk, std::shared_ptr<Scene> scene);
	bool parseCamera(std::string& stringChunk, std::shared_ptr<Camera> cam);
	bool parseLightSource(std::string& stringChunk, std::shared_ptr<LightSource> ls);
	bool parseSphere(std::string& stringChunk, std::shared_ptr<Sphere> sphere);
	bool parsePlane(std::string& stringChunk, std::shared_ptr<Plane> plane);
	bool parsePigment(std::string& str, std::shared_ptr<Shape> shape);
	bool parseFinish(std::string& str, std::shared_ptr<Shape> shape);
	bool parseTranslate(std::string& str, std::shared_ptr<Shape> shape);
	bool parseScale(std::string& str, std::shared_ptr<Shape> shape);
	bool parseRotate(std::string& str, std::shared_ptr<Shape> shape);
	void parseKeywordVector(std::string& stringChunk, std::string& currKeyword, glm::vec3& vec);
	void parse3FloatVector(std::string& vecString, glm::vec3& ret); 	// should be given a string of floats separated by commas
	void parseFloatAfterVec(std::string& floatString, float& flt);
	std::vector<std::string> split(const std::string& text, const std::string& delims);
	bool contains(std::string& str, const std::string substring);
	std::string trim(const std::string& str, const std::string& whitespace = " \t\n\r\v\f");
};

