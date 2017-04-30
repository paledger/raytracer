#include "MyParser.h"

using namespace std;
/* PUBLIC */


bool MyParser::openFile(const string &fileName) {
	this->sceneFile.open(fileName);
	if (!this->sceneFile) {
		return false;
	}
	return true;
}

int MyParser::parseFileToScene(shared_ptr<Scene>  scene) {
	stringstream buffer;
	string strBuffer, tempStr;
	size_t chunkStart = 0, chunkEnd = 0;

	buffer << this->sceneFile.rdbuf();
	strBuffer = buffer.str();
	removeComments(strBuffer);

	while ((chunkEnd = strBuffer.find("}", chunkEnd + 1)) != strBuffer.npos) {
		tempStr = strBuffer.substr(chunkStart, chunkEnd - chunkStart + 1);
		if (count(tempStr.begin(), tempStr.end(), '{') == count(tempStr.begin(), tempStr.end(), '}')) {
			// hand chunk over!!
			handleChunk(tempStr, scene);
			chunkStart = chunkEnd + 1;
		}
	}
	return 0;
}

/* PRIVATE */

void MyParser::removeComments(string& strBuffer) {
	size_t commStart = 0, commEnd = 0;
	while ((commStart = strBuffer.find("//")) != strBuffer.npos) {
		commEnd = strBuffer.find("\n", commStart) + 1;
		strBuffer.erase(commStart, commEnd - commStart);
	}
}

void MyParser::handleChunk(string& strChunk, shared_ptr<Scene> scene) {
	if (contains(strChunk, "camera")) {
		parseCamera(strChunk, scene->createCamera());
	}
	else if (contains(strChunk, "light_source")) {
		parseLightSource(strChunk, scene->createLightSource());
	}
	else if (contains(strChunk, "sphere")) {
		parseSphere(strChunk, scene->createSphere());
	}
	else if (contains(strChunk, "plane")) {
		parsePlane(strChunk, scene->createPlane());
	}
}

bool MyParser::parseCamera(string& stringChunk, shared_ptr<Camera> cam) {
	string location("location");
	string up("up");
	string right("right");
	string look_at("look_at");
	parseKeywordVector(stringChunk, location, cam->location);
	parseKeywordVector(stringChunk, up, cam->up);
	parseKeywordVector(stringChunk, right, cam->right);
	parseKeywordVector(stringChunk, look_at, cam->look_at);
	return true;
}

bool MyParser::parseLightSource(string& stringChunk, shared_ptr<LightSource> ls) {
	string source("source");
	string color("color");
	parseKeywordVector(stringChunk, source, ls->location);
	parseKeywordVector(stringChunk, color, ls->color);
	return true;
}

bool MyParser::parseSphere(string& stringChunk, shared_ptr<Sphere> sphere) {
	string sphereStr("sphere");
	parseKeywordVector(stringChunk, sphereStr, sphere->center);
	parseFloatAfterVec(stringChunk, sphere->radius);
	parsePigment(stringChunk, sphere);
	parseFinish(stringChunk, sphere);
	parseTranslate(stringChunk, sphere);
	parseRotate(stringChunk, sphere);
	parseScale(stringChunk, sphere);
	return true;
}

bool MyParser::parsePlane(string& stringChunk, shared_ptr<Plane> plane) {
	string planeStr("plane");
	parseKeywordVector(stringChunk, planeStr, plane->normal);
	parseFloatAfterVec(stringChunk, plane->distance);
	parsePigment(stringChunk, plane);
	parseFinish(stringChunk, plane);
	parseTranslate(stringChunk, plane);
	parseRotate(stringChunk, plane);
	parseScale(stringChunk, plane);
	return true;
}

bool MyParser::parsePigment(string& str, shared_ptr<Shape> shape) {
	string pigment("pigment");
	parseKeywordVector(str, pigment, shape->pigment);
	return true;
}

bool MyParser::parseFinish(string& str, shared_ptr<Shape> shape) {
	if (str.find("finish") == str.npos) {
		return false;
	}
	size_t ambientStart = str.find("ambient");
	size_t diffuseStart = str.find("diffuse");
	size_t specStart = str.find("specular");
	size_t roughStart = str.find("roughness");
	size_t metallicStart = str.find("metallic");

	string substr;
	if (ambientStart != str.npos) {
		substr = str.substr(ambientStart + strlen("ambient"), str.npos);
		shape->ambient = stof(substr.substr(0, substr.find_first_of("mrads}")));
	}
	if (diffuseStart != str.npos) {
		substr = str.substr(diffuseStart + strlen("diffuse"), str.npos);
		shape->diffuse = stof(substr.substr(0, substr.find_first_of("mrads}")));
	}
	if (specStart != str.npos) {
		substr = str.substr(specStart + strlen("specular"), str.npos);
		shape->specular = stof(substr.substr(0, substr.find_first_of("mrads}")));
	}
	if (roughStart != str.npos) {
		substr = str.substr(roughStart + strlen("roughness"), str.npos);
		shape->shininess = stof(substr.substr(0, substr.find_first_of("mrads}")));
	}
	if (metallicStart != str.npos) {
		substr = str.substr(metallicStart + strlen("metallic"), str.npos);
		shape->metallic = stof(substr.substr(0, substr.find_first_of("mrads}")));
	}
	return true;
}

bool MyParser::parseTranslate(string& str, shared_ptr<Shape> shape) {
	glm::vec3 tempVec(0.0, 0.0, 0.0);
	string translate("translate");
	parseKeywordVector(str, translate, tempVec);
	shape->translate = shape->translate + tempVec;
	return true;
}

bool MyParser::parseScale(string& str, shared_ptr<Shape> shape) {
	glm::vec3 tempVec(0.0, 0.0, 0.0);
	string scale("scale");
	parseKeywordVector(str, scale, tempVec);
	shape->scale = shape->scale + tempVec;
	return true;
}

bool MyParser::parseRotate(string& str, shared_ptr<Shape> shape) {
	glm::vec3 tempVec(0.0, 0.0, 0.0);
	string rotate("rotate");
	parseKeywordVector(str, rotate, tempVec);
	shape->rotate = shape->rotate + tempVec;
	return true;
}

void MyParser::parseKeywordVector(string& stringChunk, string& currKeyword, glm::vec3& vec) {
	size_t currStart = 0, vecStart = 0, vecEnd = 0;

	currStart = stringChunk.find(currKeyword);
	if (currStart != stringChunk.npos) {
		vecStart = stringChunk.find("<", currStart + currKeyword.size());
		vecEnd = stringChunk.find(">", currStart + currKeyword.size());
		string subString(stringChunk.substr(vecStart + 1, vecEnd - vecStart - 1));
		parse3FloatVector(subString, vec);
	}
}

// should be given a string of floats separated by commas
void MyParser::parse3FloatVector(string& vecString, glm::vec3& ret) {
	size_t startPos = 0, endPos = 0;
	for (int i = 0; i < 3; i++) {
		endPos = vecString.find(",", startPos);
		ret[i] = stof(vecString.substr(startPos, endPos - startPos));
		startPos = endPos + 1;
	}
}

void MyParser::parseFloatAfterVec(string& floatString, float& flt) {
	size_t startRadius = floatString.find(",", floatString.find(">")) + 1;
	size_t endRadius = floatString.find("\n", startRadius);
	flt = stof(floatString.substr(startRadius, endRadius - startRadius));
}

std::vector<std::string> MyParser::split(const std::string& text, const std::string& delims)
{
	std::vector<std::string> tokens;
	std::size_t start = text.find_first_not_of(delims), end = 0;

	while ((end = text.find_first_of(delims, start)) != std::string::npos)
	{
		tokens.push_back(text.substr(start, end - start));
		start = text.find_first_not_of(delims, end);
	}
	if (start != std::string::npos)
		tokens.push_back(text.substr(start));

	return tokens;
}

bool MyParser::contains(string& str, const string substring) {
	if (str.find(substring) != std::string::npos) {
		return true;
	}
	return false;
}

string MyParser::trim(const string& str, const string& whitespace)
{
	auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	auto strEnd = str.find_last_not_of(whitespace);
	auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}
