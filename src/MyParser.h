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
#include "Triangle.h"
#include "Camera.h"
#include "LightSource.h"
#include "Finish.h"


class MyParser
{
public:
	std::ifstream sceneFile;

	bool openFile(const std::string& fileName);
	int parseFileToScene(std::shared_ptr<Scene>  scene);

private:
	void iterateThroughChunks(std::string& strBuffer, std::shared_ptr<Scene> scene);
	void iterateThroughShapes(std::string& strBuffer, std::vector<std::shared_ptr<Shape>>& shapes);
	void removeComments(std::string& strBuffer);
	bool handleChunk(std::string& strChunk, std::shared_ptr<Scene> scene);
	bool handleShape(std::string& strChunk, std::vector<std::shared_ptr<Shape>>& shapes);
	bool parseCamera(std::string& stringChunk, std::shared_ptr<Camera> cam);
	bool parseLightSource(std::string& stringChunk, std::shared_ptr<LightSource> ls);
	bool parseSphere(std::string& stringChunk, std::shared_ptr<Sphere> sphere);
	bool parsePlane(std::string& stringChunk, std::shared_ptr<Plane> plane); 
	bool parseTriangle(std::string& stringChunk, std::shared_ptr<Triangle> triangle); 
	bool parseBox(std::string& stringChunk, std::shared_ptr<Box> box);
	float parseFinishKeyword(std::string& str, std::string& keyword);
	bool parseFinish(std::string& str, std::shared_ptr<Finish>& finish);
	void parseTransformation(std::string& str, std::shared_ptr<Transformation> transform);
	int findNextTransformation(std::string& str);
	bool parseTranslate(std::string& str, std::shared_ptr<Transformation> shape);
	bool parseScale(std::string& str, std::shared_ptr<Transformation> shape);
	bool parseRotate(std::string& str, std::shared_ptr<Transformation> shape);

	void parseUnion(std::string& str, std::shared_ptr<Union> boolOp);
	void parseIntersect(std::string& str, std::shared_ptr<Intersect> boolOp);
	void parseDifference(std::string& str, std::shared_ptr<Difference> boolOp);

	void parseKeywordVector(std::string& stringChunk, std::string& currKeyword, glm::vec3& vec);
	void parsePigmentVector(std::string& stringChunk, std::string& currKeyword, glm::vec3& vec, float& filter);
	void parse4FloatVector(std::string& vecString, std::vector<float>& ret); 	// should be given a string of floats separated by commas
	void parse3FloatVector(std::string& vecString, glm::vec3& ret); 	// should be given a string of floats separated by commas
	void parseFloatAfterVec(std::string& floatString, float& flt);
	std::vector<std::string> split(const std::string& text, const std::string& delims);
	bool contains(std::string& str, const std::string substring);
	std::string trim(const std::string& str, const std::string& whitespace = " \t\n\r\v\f");
	int getNumOccur(const std::string str, const std::string substr);
};