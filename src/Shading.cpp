#include "Shading.h"
#include "Render.h"

using namespace std;

glm::vec3 Shading::shadedPixels(std::shared_ptr<Scene>& scene,
	std::shared_ptr<Shape>& shape, glm::vec3 origin, glm::vec3& viewRay, float t,
	unsigned int mode, bool test)
{
	shared_ptr<Finish> finish = shape->finish;
	glm::vec3 point = Helper::getPointOnRay(origin, viewRay, t);
	glm::vec3 view = glm::normalize(-viewRay);

	glm::vec3 color;
	for (unsigned int l = 0; l < scene->lightSources.size(); l++) {
		shared_ptr<LightSource> currLight = scene->lightSources[l];
		if (mode == BLINNPHONG_MODE) {
			color = Shading::blinnPhong(scene, currLight, shape, view, point, test);
		}
		else if (mode == COOKTORRANCE_MODE) {
			color = Shading::cookTorrance(scene, currLight, shape, view, point);
		}
	}
	return color;
}

glm::vec3 Shading::blinnPhong(shared_ptr<Scene>& scene, shared_ptr<LightSource>& currLight,
	shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point, bool test)
{
	shared_ptr<Finish> finish = shape->finish;
	float t2;
	float power = (2 / (finish->shininess*finish->shininess) - 2);
	glm::vec3 color, ambient, diffuse, spec;
	glm::vec3 normal = shape->getNormal(point);
	glm::vec3 normalizedL = glm::normalize(currLight->location - point);
	Render::getFirstHit(scene, point + normal * 0.001f, normalizedL, &t2);

	ambient = finish->pigment * finish->ambient;
	if (Shading::notShaded(t2)) {
		ambient = finish->pigment * finish->ambient;
		glm::vec3 halfVec = glm::normalize(view + normalizedL);
		glm::vec3 lightColor = currLight->color;
		diffuse = finish->pigment * finish->diffuse * lightColor * \
					glm::max(glm::dot(normal, normalizedL), 0.0f);
		spec = finish->pigment * finish->specular * lightColor * \
					glm::pow(glm::max(glm::dot(halfVec, normal), 0.0f), power);
	}
	if (test) {
		if (!Shading::notShaded(t2)) {
			cout << "note ----> is shaded" << endl;
		}
		cout << "intersects AT: " << point.x << " " << point.y << " " << point.z << endl;
		cout << "normal: " << normal.x << " " << normal.y << " " << normal.z << endl;
		cout << "ambient: " << ambient.x << " " << ambient.y << " " << ambient.z << endl;
		cout << "diffuse: " << diffuse.x << " " << diffuse.y << " " << diffuse.z << endl;
		cout << "spec: " << spec.x << " " << spec.y << " " << spec.z << endl;
	}
	color = ambient + diffuse + spec;
	return color;
}

glm::vec3 Shading::cookTorrance(shared_ptr<Scene>& scene,
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
	if (Shading::notShaded(t2)) {
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
	if (Shading::notShaded(t2)) {
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

bool Shading::notShaded(float t2) {
	return t2 == INT_MAX;
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
	float F = F_0 + (1 - F_0) * glm::pow(1 - glm::dot(-n, v), 5);
	return F;
}