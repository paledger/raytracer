#include "Render.h"
#include "Helper.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

using namespace std;

/* PUBLIC */

/*** PROJECT 2 COMMANDS ***/

void Render::pixelcolor(std::shared_ptr<Scene>& scene, int width, int height, int x, int y, unsigned int mode) {
	unsigned char red, green, blue;
	float t;
	glm::vec3 color;
	glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
	shared_ptr<Shape> shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
	if (shape) {
		float reflection = shape->finish->reflection;
		Render::pixelRay(scene, width, height, x, y);
		cout << setprecision(4);
		cout << "T = " << t << endl;
		cout << "Object Type: " << shape->getTypeString() << endl;
		if (mode == RAYCAST_MODE) {
			color = Render::raycastPixels(shape);
		}
		else if (mode == BLINNPHONG_MODE) {
			color = (1 - reflection) * Render::shadedPixels(scene, shape, scene->camera->location, rayDirection, t, mode);
			cout << "BRDF: Blinn-Phong" << endl;
		}
		else if (mode == COOKTORRANCE_MODE) {
			color = Render::shadedPixels(scene, shape, scene->camera->location, rayDirection, t, mode);
			cout << "BRDF: Cook-Torrance" << endl;
		}

		// reflection
		glm::vec3 reflectionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 intersectionPt = Helper::getPointOnRay(scene->camera->location, rayDirection, t);
		reflectionColor = getReflection(scene, shape, intersectionPt, rayDirection, 0, true);
		color += reflection * reflectionColor;

		red = Helper::convertToRgb(color[0]);
		green = Helper::convertToRgb(color[1]);
		blue = Helper::convertToRgb(color[2]);
		cout << "Color: (" << (int)red << ", " << (int)green << ", " << (int)blue << ")" << endl;
	}
	else {
		cout << "No Hit" << endl;
	}
}


/*** PROJECT 1 COMMANDS ***/
void Render::createOutput(shared_ptr<Scene>& scene, int width, int height, unsigned int mode) {
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);
	shared_ptr<Shape> shape;
	glm::vec3 rayDirection, color;
	float t;
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	glm::vec3 reflectionColor;
	float reflection = 0.0f;
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			unsigned char red, green, blue;

			rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
			shared_ptr<Shape> shape = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
			if (shape) {
				reflection = shape->finish->reflection;
			}
			color = (1 - reflection) * Render::getPixelColor(scene, shape, scene->camera->location, rayDirection, mode, t);
			if (shape) {
				reflectionColor = glm::vec3(0.0f, 0.0f, 0.0f);
				glm::vec3 intersectionPt = Helper::getPointOnRay(scene->camera->location, rayDirection, t);
				reflectionColor = getReflection(scene, shape, intersectionPt, rayDirection, 0);
				color += reflection * reflectionColor;
			}
			red = Helper::convertToRgb(color[0]);
			green = Helper::convertToRgb(color[1]);
			blue = Helper::convertToRgb(color[2]);

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}
	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}


glm::vec3 Render::raycastPixels(std::shared_ptr<Shape>& shape) 
{
	return shape->finish->pigment;
}


glm::vec3 Render::pixelRay(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	glm::vec3 rayDirection = Render::calculatePixelRay(scene, width, height, x, y);
	cout << setprecision(4);
	cout << "Pixel: [" << x << ", " << y << "] ";
	cout << "Ray: {" << scene->camera->location[0] << \
		" " << scene->camera->location[1] << " " << scene->camera->location[2] << "} ";
	cout << "-> {" << rayDirection[0] << " " << rayDirection[1] << " " << rayDirection[2] << "}\n";
	return rayDirection;
}

void Render::firstHit(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	float t;
	glm::vec3 rayDirection = Render::pixelRay(scene, width, height, x, y);
	shared_ptr<Shape> firstHit = Render::getFirstHit(scene, scene->camera->location, rayDirection, &t);
	shared_ptr<Finish> finish = firstHit->finish;
	cout << setprecision(4);
	if (t == INT_MAX) {
		cout << "No Hit\n";
	}
	else {
		cout << "T = " << t << "\n";
		cout << "Object Type: " << firstHit->getTypeString().c_str() << "\n";
		cout << "Color: " << finish->pigment[0] << " " << \
			finish->pigment[1] << " " << \
			finish->pigment[2] << "\n";
	}
}

/* PRIVATE */

/*** PROJECT 3 COMMANDS ***/

glm::vec3 Render::getReflection(shared_ptr<Scene> scene, shared_ptr<Shape> shape,
	glm::vec3 intersectionPt, glm::vec3& d, unsigned int depth, bool test)
{
	glm::vec3 addition;
	glm::vec3 incident = glm::normalize(d);
	float newT;

	if (depth >= 6 || !shape) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 n = shape->getNormal(intersectionPt);
	glm::vec3 reflectionVec = glm::normalize(incident - 2 * glm::dot(incident, n) * n);
	// find new reflection information 
	shared_ptr<Shape> newShape = Render::getFirstHit(scene, intersectionPt,
		reflectionVec, &newT);
	glm::vec3 newPoint = Helper::getPointOnRay(intersectionPt, reflectionVec, newT);

	// get reflection to multiply
	float reflection;
	reflection = shape->finish->reflection;
	addition = Render::getPixelColor(scene, newShape, intersectionPt, reflectionVec, BLINNPHONG_MODE, newT);
	if (test) {
		cout << shape->getTypeString() << endl;
		cout << "reflection: " << reflection << endl;
		glm::vec3 rgb = Helper::convertToRgb(addition);
		cout << "intersectionPt: " << newPoint.x << " " << newPoint.y << " " << newPoint.z << endl;
		cout << "next color: " << rgb.r << " " << rgb.g << " " << rgb.b << endl;
	}
	if (newShape && newShape->finish->reflection)
		return (1 - reflection) * addition + reflection * getReflection(scene, newShape, newPoint, reflectionVec, depth + 1, test);
	else {
		if (test)
			cout << newShape->getTypeString() << endl;
		return (1 - reflection) * addition;
	}
}


/*** PROJECT 2 COMMANDS ***/

glm::vec3 Render::shadedPixels(std::shared_ptr<Scene>& scene,
	std::shared_ptr<Shape>& shape, glm::vec3 origin, glm::vec3& viewRay, float t,
	unsigned int mode)
{
	shared_ptr<Finish> finish = shape->finish;
	glm::vec3 point = Helper::getPointOnRay(scene->camera->location, viewRay, t);
	glm::vec3 view = glm::normalize(-viewRay);

	glm::vec3 color = finish->pigment * finish->ambient;
	for (unsigned int l = 0; l < scene->lightSources.size(); l++) {
		shared_ptr<LightSource> currLight = scene->lightSources[l];
		if (mode == BLINNPHONG_MODE) {
			color += Render::blinnPhong(scene, currLight, shape, view, point);
		}
		else if (mode == COOKTORRANCE_MODE) {
			color += Render::cookTorrance(scene, currLight, shape, view, point);
		}
	}
	return color;
}

glm::vec3 Render::blinnPhong(shared_ptr<Scene>& scene, shared_ptr<LightSource>& currLight, 
						shared_ptr<Shape>& shape, glm::vec3 view, glm::vec3 point) 
{
	shared_ptr<Finish> finish = shape->finish;
	float t2, epsilon = .001f;
	float power = (2 / (finish->shininess*finish->shininess) - 2);
	glm::vec3 color;	
	glm::vec3 normal = shape->getNormal(point);
	glm::vec3 normalizedL = glm::normalize(currLight->location - point);
	
	Render::getFirstHit(scene, point, normalizedL, &t2);
	if (Render::notShaded(t2)) {
		glm::vec3 halfVec = glm::normalize(view + normalizedL);
		glm::vec3 lightColor = currLight->color;
		color += finish->pigment * finish->diffuse * lightColor * \
			glm::max(glm::dot(normal, normalizedL), 0.0f);
		color += finish->pigment * finish->specular * lightColor * \
			glm::pow(glm::max(glm::dot(halfVec, normal), 0.0f), power);
	}
	return color;
}

glm::vec3 Render::cookTorrance(shared_ptr<Scene>& scene, 
	shared_ptr<LightSource>& currLight,	shared_ptr<Shape>& shape, 
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
	if (Render::notShaded(t2)) {
		glm::vec3 h = glm::normalize(view + l);
		glm::vec3 lightColor = currLight->color;
		float alpha = finish->shininess*finish->shininess;
		float power = ((2 / (alpha*alpha)) - 2);
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

glm::vec3 Render::cookTorrance_BlinnPhong(shared_ptr<Scene>& scene,
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
	if (Render::notShaded(t2)) {
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

bool Render::notShaded(float t2) {
	return t2 == INT_MAX;
}

float Render::chiGGX(float v)
{
	return v > 0 ? 1 : 0;
}

float Render::GGX_Distribution(glm::vec3 n, glm::vec3 h, float alpha)
{
	float NoH = glm::dot(n, h);
	float alpha2 = alpha * alpha;
	float NoH2 = NoH * NoH;
	float den = NoH2 * alpha2 + (1 - NoH2);
	return (Render::chiGGX(NoH) * alpha2) / (PI * den * den);
}

float Render::GGX_Geometry(glm::vec3 v, glm::vec3 n, glm::vec3 h, float alpha)
{
	float VoH2 = glm::dot(v, h);
	float chi = Render::chiGGX(VoH2 / glm::dot(v, n));
	VoH2 = VoH2 * VoH2;
	float tan2 = (1 - VoH2) / VoH2;
	return (chi * 2) / (1 + glm::sqrt(1 + alpha * alpha * tan2));
}

/*** PROJECT 1 COMMANDS ***/

glm::vec3 Render::getPixelColor(shared_ptr<Scene>& scene, 
	shared_ptr<Shape>& shape, const glm::vec3 origin, glm::vec3& viewRay, unsigned int mode, float t, bool test)
{
	glm::vec3 color;
	if (shape) {
		if (mode == RAYCAST_MODE) {
			color = Render::raycastPixels(shape);
		}
		else if (mode == BLINNPHONG_MODE || mode == COOKTORRANCE_MODE) {
			color = Render::shadedPixels(scene, shape, origin, viewRay, t, mode);
		}
	}
	else {
		color = glm::vec3(0.0f, 0.0f, 0.0f); // set to all black
	}
	return color;
}

glm::vec3 Render::calculatePixelRay(shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	float right = glm::length(glm::normalize(scene->camera->right)) / 2.0f;
	float top = glm::length(scene->camera->up) / 2.0f;
	float left = -right;
	float bottom = -top;
	float u = (left + (right - left)*(x + 0.5f) / width);
	float v = (bottom + (top - bottom)*(y + 0.5f) / height);
	glm::vec3 l = glm::normalize(scene->camera->look_at - scene->camera->location);
	return glm::normalize(u*scene->camera->right + \
						  v*scene->camera->up +	\
						  l);
}

shared_ptr<Shape> Render::getFirstHit(shared_ptr<Scene>& scene, 
	glm::vec3 origin, glm::vec3 rayDirection, float* intersectT)
{
	shared_ptr<Shape> closestShape;
	float closestT = (float)INT_MAX, t = -1;
	for (unsigned int sh = 0; sh < scene->shapes.size(); sh++) {
		t = calculateFirstHit(scene, origin, rayDirection, scene->shapes[sh]);
		if (t > 0 && t < closestT) {
			closestT = t;
			closestShape = scene->shapes[sh];
		}
	}
	if (intersectT != nullptr) {
		*intersectT = closestT;
	}
	return closestShape;
}

float Render::calculateFirstHit(shared_ptr<Scene>& scene,  glm::vec3 origin, 
	glm::vec3 rayDirection, const shared_ptr<Shape>& shapeToTest) 
{
	vector<float> t = shapeToTest->getIntersection(rayDirection, origin);
	if (!t.empty()) {
		sort(t.begin(), t.end());
		return t[0];
	}
	return -1;
}