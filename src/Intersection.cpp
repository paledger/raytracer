#include "Intersection.h"
#include "Helper.h"

void Intersection::setTransformedInfo(glm::vec3 origin, glm::vec3 viewRay) 
{
	this->oOrigin = origin;
	this->oRay = viewRay;

	this->tRay = shape->transform->transformVector(viewRay);
	this->tOrigin = shape->transform->transformPoint(origin);
	this->wPt = Helper::getPointOnRay(origin, viewRay, t);
	this->oPt = Helper::getPointOnRay(tOrigin, tRay, t);

	this->n = this->shape->getNormal(this->oPt);
}