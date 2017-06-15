#include "BooleanOperator.h" 

using namespace std;

void BooleanOperator::printInfo() {
	cout << std::setprecision(4);
	cout << "Type: " << this->getTypeString().c_str() <<  " ---" << endl;
	for (unsigned int o = 0; o < this->objects.size(); o++) {
		cout << endl;
		cout << "Constructive object [" << o << "]:" << endl;
		this->objects[o]->printInfo();
	}
	cout << "---" << endl;
	Shape::printInfo();
}

shared_ptr<Finish> BooleanOperator::getFinish()
{
	glm::vec3 pigment = this->finish->pigment;
	if (pigment != glm::vec3(0.0f)) {
		return this->finish;
	}
	else if (this->mostRecentIntersection != nullptr) {
		return this->mostRecentIntersection->finish;
	}
	return this->finish;
}