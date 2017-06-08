#include "Shading.h"
#include "Render.h"
#include "Ambient.h"

using namespace std;

glm::vec3 Shading::shadedPixels(shared_ptr<Scene>& scene, shared_ptr<Intersection> intersect, int depth, Flags flags)
{
	shared_ptr<Shape> shape = intersect->shape;
	shared_ptr<Finish> finish = shape->finish;
	glm::vec3 origin = intersect->oOrigin;
	glm::vec3 viewRay = intersect->oRay;
	float t = intersect->t;

	glm::vec3 ambient = Ambient::getAmbient(scene, intersect, depth, flags);
	glm::vec3 color = ambient;
	for (unsigned int l = 0; l < scene->lightSources.size(); l++) {
		if (flags.test) {
			cout << "\nLight " << l << ":";
			cout << "\n" << finish->ambient << " * ambient: " << ambient.x << " " << ambient.y << " " << ambient.z << endl;
		}

		shared_ptr<LightSource> currLight = scene->lightSources[l];
		if (flags.mode == BLINNPHONG_MODE) {
			color += Shading::blinnPhong(scene, currLight, shape, origin, viewRay, t, flags);
		}
		else if (flags.mode == COOKTORRANCE_MODE) {
			color += Shading::cookTorrance(scene, currLight, shape, origin, viewRay, t);
		}
	}
	return color;
}

glm::vec3 Shading::blinnPhong(shared_ptr<Scene>& scene, shared_ptr<LightSource>& currLight,
	shared_ptr<Shape>& shape, glm::vec3 origin, glm::vec3 ray, float t, Flags flags)
{
	shared_ptr<Finish> finish = shape->finish;
	shared_ptr<Transformation> transform = shape->transform;
	float t2;
	float power = (2 / (finish->shininess*finish->shininess) - 2);
	glm::vec3 color, diffuse, spec;

	glm::vec3 tRay = shape->transform->transformVector(ray);
	glm::vec3 tOrigin = shape->transform->transformPoint(origin);
	glm::vec3 oPoint = Helper::getPointOnRay(tOrigin, tRay, t);
	glm::vec3 wPoint = Helper::getPointOnRay(origin, ray, t);

	glm::vec3 view = (-tRay);
	glm::vec3 wNormal = shape->getNormal(oPoint);
	glm::vec3 normalizedL = glm::normalize(currLight->location - wPoint);
	
	shared_ptr<Shape> shader;
	if (flags.bvh) {
		shader = Render::getFirstHitBVH(scene, wPoint + wNormal * 0.001f, normalizedL, &t2);
	}
	else {
		shader = Render::getFirstHit(scene, wPoint + wNormal * 0.001f, normalizedL, &t2);
	}

	if (Shading::notShaded(glm::length(currLight->location - wPoint), t2)) {
		glm::vec3 halfVec = glm::normalize(view + normalizedL);
		glm::vec3 lightColor = currLight->color;
		diffuse = finish->pigment * finish->diffuse * lightColor * \
					glm::max(glm::dot(wNormal, normalizedL), 0.0f);
		spec = finish->pigment * finish->specular * lightColor * \
					glm::pow(glm::max(glm::dot(halfVec, wNormal), 0.0f), power);
	}
	if (flags.test) {
		if (!Shading::notShaded(glm::length(currLight->location - wPoint), t2)) {
			cout << "note ----> is shaded at " << t2 << " " << glm::length(currLight->location - wPoint) << endl;
			shader->printInfo();
		}
		cout << "normalized L: " << normalizedL.x << " " << normalizedL.y << " " << normalizedL.z << endl;
		cout << "intersects AT: " << wPoint.x << " " << wPoint.y << " " << wPoint.z << endl;
		cout << "normal: " << wNormal.x << " " << wNormal.y << " " << wNormal.z << endl;
		cout << finish->diffuse << " * diffuse: " << diffuse.x << " " << diffuse.y << " " << diffuse.z << endl;
		cout << finish->specular << " * spec: " << spec.x << " " << spec.y << " " << spec.z << endl;
	}
	color = diffuse + spec;
	return color;
}

glm::vec3 Shading::cookTorrance(shared_ptr<Scene>& scene,
	shared_ptr<LightSource>& currLight, shared_ptr<Shape>& shape,
	glm::vec3 origin, glm::vec3 ray, float t)
{
	shared_ptr<Finish> finish = shape->finish;
	float specular = finish->metallic;
	float diffuse = 1 - specular;
	float t2, epsilon = .0001f;
	glm::vec3 shadingColor;
	glm::vec3 tRay = shape->transform->transformVector(ray);
	glm::vec3 tOrigin = shape->transform->transformPoint(origin);
	glm::vec3 oPoint = Helper::getPointOnRay(tOrigin, tRay, t);
	glm::vec3 wPoint = Helper::getPointOnRay(origin, ray, t);

	glm::vec3 view = (-tRay);
	glm::vec3 n = shape->getNormal(oPoint);
	glm::vec3 l = glm::normalize(currLight->location - wPoint);

	Render::getFirstHit(scene,wPoint + l*epsilon, l, &t2);
	if (Shading::notShaded(glm::length(currLight->location - wPoint), t2)) {
		glm::vec3 h = glm::normalize(view + l);
		glm::vec3 lightColor = currLight->color;
		float alpha = finish->shininess*finish->shininess;
		float D = GGX_Distribution(n, h, alpha);
		float G = GGX_Geometry(view, n, h, alpha);
		float F_0 = ((finish->ior - 1)*(finish->ior - 1)) / ((finish->ior + 1)*(finish->ior + 1));
		float F = F_0 + (1 - F_0) * glm::pow(1 - glm::dot(view, h), 5);
		float r_d = finish->diffuse;
		float r_s = glm::max(0.0f, (D*G*F) / (4 * glm::dot(n, view)));
		shadingColor += (finish->pigment) * lightColor * glm::max(0.0f, diffuse * glm::dot(n, l) * r_d + \
			specular * r_s);
	}
	return shadingColor;
}

glm::vec3 Shading::cookTorrance_BlinnPhong(shared_ptr<Scene>& scene,
	shared_ptr<LightSource>& currLight, shared_ptr<Shape>& shape,
	glm::vec3 view, glm::vec3 point)
{
	shared_ptr<Finish> finish = shape->finish;
	float specular = finish->metallic;
	float diffuse = 1 - specular;
	float t2, epsilon = .0001f;
	glm::vec3 shadingColor;
	glm::vec3 n = shape->getNormal(point);
	glm::vec3 l = glm::normalize(currLight->location - point);

	Render::getFirstHit(scene, point + l*epsilon, l, &t2);
	if (Shading::notShaded(glm::length(currLight->location - point), t2)) {
		glm::vec3 h = glm::normalize(view + l);
		glm::vec3 lightColor = currLight->color;
		float HoN = glm::dot(h, n);
		float alpha = finish->shininess*finish->shininess;
		float power = ((2 / (alpha*alpha)) - 2);
		float D = (1.0f / (float(PI)*alpha*alpha))*glm::pow(HoN, power);
		float constant = (2 * HoN / glm::dot(view, h));
		float G = glm::min(1.0f, \
			glm::min(constant * glm::dot(n, view), \
				constant * glm::dot(n, l)
			));
		float F_0 = ((finish->ior - 1)*(finish->ior - 1)) / ((finish->ior + 1)*(finish->ior + 1));
		float F = F_0 + (1 - F_0) * glm::pow(1 - glm::dot(view, h), 5);
		float r_d = finish->diffuse;
		float r_s = glm::max(0.0f, (D*G*F) / (4 * glm::dot(n, view)));
		shadingColor += (finish->pigment) * lightColor * glm::max(0.0f, diffuse * glm::dot(n, l) * r_d + \
			specular * r_s);
	}
	return shadingColor;
}

bool Shading::notShaded(float s, float t2) {
	return t2 == INT_MAX || t2 > s;
}

float Shading::chiGGX(float v)
{
	return v > 0 ? 1.0f : 0.0f;
}

float Shading::GGX_Distribution(glm::vec3 n, glm::vec3 h, float alpha)
{
	float NoH = glm::dot(n, h);
	float alpha2 = alpha * alpha;
	float NoH2 = NoH * NoH;
	float den = NoH2 * alpha2 + (1 - NoH2);
	return (Shading::chiGGX(NoH) * alpha2) / (3.14f * den * den);
}

float Shading::GGX_Geometry(glm::vec3 v, glm::vec3 n, glm::vec3 h, float alpha)
{
	float VoH2 = glm::dot(v, h);
	float chi = Shading::chiGGX(VoH2 / glm::dot(v, n));
	VoH2 = VoH2 * VoH2;
	float tan2 = (1 - VoH2) / VoH2;
	return (chi * 2) / (1 + glm::sqrt(1 + alpha * alpha * tan2));
}


float Shading::getSchlickApproximation(const glm::vec3 n, const float ior, const glm::vec3 v) {
	float F_0 = glm::pow(ior - 1, 2) / glm::pow(ior + 1, 2);
	float F = F_0 + (1 - F_0) * glm::pow(glm::clamp(1 - glm::dot(-n, v), 0.0f, 1.0f), 5);
	return F;
}
