#pragma once

#include <algorithm>
#include "Shape.h"

class BooleanOperator : public Shape {
public: 
	void printInfo(); 
	std::shared_ptr<Finish> getFinish() override;

	std::vector<std::shared_ptr<Shape>> objects;
	std::shared_ptr<Shape> mostRecentIntersection = nullptr;
};