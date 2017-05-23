#include "Triangle.h"

using namespace std;


void Triangle::printInfo() 
{
	cout << std::setprecision(4);
	cout << "- Type: Triangle\n";
	cout << "- Point a: {" << a[0] << " " << a[1] << " " << a[2] << "}\n";
	cout << "- Point b: {" << b[0] << " " << b[1] << " " << b[2] << "}\n";
	cout << "- Point c: {" << c[0] << " " << c[1] << " " << c[2] << "}\n";
	Shape::printInfo();
}

// returns a vector of floats of the "t" value of intersection
vector<float> Triangle::getIntersection(const glm::vec3& dir, const glm::vec3& origin)
{
	vector<float> vec;
	glm::vec3 intersectionPt;
	float D, t, denom, edge1, edge2, edge3;
	float epsilon = 0.0001f;

	glm::vec3 n = glm::normalize(this->getNormal(origin));

	if ((denom = glm::dot(n, dir)) != 0) {
		D = glm::dot(n, this->a);
		t = (D - glm::dot(origin, n)) / denom;
		intersectionPt = Helper::getPointOnRay(origin, dir, t);
		edge1 = glm::dot(glm::cross(b - a, intersectionPt - a), n);
		edge2 = glm::dot(glm::cross(c - b, intersectionPt - b), n);
		edge3 = glm::dot(glm::cross(a - c, intersectionPt - c), n);
		if (edge1 >= 0 &&
			edge2 >= 0 &&
			edge3 >= 0 && 
			t > epsilon) 
		{
			vec.push_back(t);
		}
	}

	return vec;

}

string Triangle::getTypeString()
{
	string triStr("Triangle");
	return triStr;
}

glm::vec3 Triangle::getNormal(glm::vec3 point)
{
	glm::vec3 U = b - a;
	glm::vec3 V = c - a;
	glm::vec3 normal = glm::normalize(glm::cross(U, V));
	return transform->transformNormal(normal);
}