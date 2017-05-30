#pragma once

#include "Box.h"
#include "Shape.h"

#include "glm/glm.hpp"

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>		// std::vector

class BoundingBox : public Box 
{
public:
	BoundingBox() {
		this->min = glm::vec3(INFINITY);
		this->max = glm::vec3(-INFINITY);
	}

	void recursiveTreeBuild(std::vector<std::shared_ptr<Shape>> objects, const unsigned int axis, bool test = false);
	void calculateBoundingBox(bool test = false);
	static void sortObjectsOnAxis(std::vector<std::shared_ptr<Shape>> &objects, const unsigned int axis, bool test = false);
	void recursePrint(int depth);

	std::vector<std::shared_ptr<Shape>> objects;
	std::shared_ptr<BoundingBox> left = nullptr;
	std::shared_ptr<BoundingBox> right = nullptr;	

private:
	static std::vector<std::shared_ptr<Shape>> leftHalfArray(std::vector<std::shared_ptr<Shape>>, bool test = false);
	static std::vector<std::shared_ptr<Shape>> rightHalfArray(std::vector<std::shared_ptr<Shape>>, bool test = false);

	void makeParentBoundingBox(glm::vec3 &min, glm::vec3 &max, bool test = false);
	void BoundingBox::transformBoundingBox(std::shared_ptr<Transformation> transform, bool test = false);

};

static bool compareXAxis(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
static bool compareYAxis(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
static bool compareZAxis(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);