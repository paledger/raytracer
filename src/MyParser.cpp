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
	else if (contains(strChunk, "triangle")) {
		parseTriangle(strChunk, scene->createTriangle());
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
	parseFinish(stringChunk, sphere->finish);
	parseTranslate(stringChunk, sphere);
	parseRotate(stringChunk, sphere);
	parseScale(stringChunk, sphere);
	return true;
}

bool MyParser::parsePlane(string& stringChunk, shared_ptr<Plane> plane) {
	string planeStr("plane");
	parseKeywordVector(stringChunk, planeStr, plane->normal);
	parseFloatAfterVec(stringChunk, plane->distance);
	parseFinish(stringChunk, plane->finish);
	parseTranslate(stringChunk, plane);
	parseRotate(stringChunk, plane);
	parseScale(stringChunk, plane);
	return true;
}

bool MyParser::parseTriangle(string& stringChunk, shared_ptr<Triangle> triangle) {
	string triStr("triangle");
	string substr, endVector = string(">");
	parseKeywordVector(stringChunk, triStr, triangle->a); 
	substr = stringChunk.substr(stringChunk.find(">"));
	parseKeywordVector(substr, endVector, triangle->b);
	substr = substr.substr(substr.find(">") + 1);
	parseKeywordVector(substr, endVector, triangle->c);
	parseFinish(stringChunk, triangle->finish);
	parseTranslate(stringChunk, triangle);
	parseRotate(stringChunk, triangle);
	parseScale(stringChunk, triangle);
	return true;
}

float MyParser::parseFinishKeyword(string& str, string& keyword) {
	size_t keywordStart = str.find(keyword);
	string substr;
	if (keywordStart != str.npos) {
		substr = str.substr(keywordStart + keyword.length(), str.npos);
		return stof(substr.substr(0, substr.find_first_of("mradis}")));
	}
	return 0.0f;
}

bool MyParser::parseFinish(string& str, shared_ptr<Finish>& finish) {
	if (str.find("finish") == str.npos) {
		return false;
	}
	string pigment("pigment");
	string ambient("ambient");
	string diffuse("diffuse");
	string specular("specular");
	string roughness("roughness");
	string metallic("metallic");
	string reflection("reflection");
	string refraction("refraction");
	string filter("filter");
	string ior("ior");
	parsePigmentVector(str, pigment, finish->pigment, finish->filter);
	finish->ambient = MyParser::parseFinishKeyword(str, ambient);
	finish->diffuse = MyParser::parseFinishKeyword(str, diffuse);
	finish->specular = MyParser::parseFinishKeyword(str, specular);
	finish->shininess = MyParser::parseFinishKeyword(str, roughness);
	finish->metallic = MyParser::parseFinishKeyword(str, metallic);
	finish->reflection = MyParser::parseFinishKeyword(str, reflection);
	finish->refraction = MyParser::parseFinishKeyword(str, refraction);
	finish->ior = MyParser::parseFinishKeyword(str, ior);

	return true;
}

bool MyParser::parseTranslate(string& str, shared_ptr<Shape> shape) {
	shared_ptr<Transformation> transform = shape->transform;
	glm::vec3 tempVec(0.0, 0.0, 0.0);
	string translate("translate");
	parseKeywordVector(str, translate, tempVec);
	transform->translate = tempVec;
	return true;
}

bool MyParser::parseScale(string& str, shared_ptr<Shape> shape) {
	shared_ptr<Transformation> transform = shape->transform;
	glm::vec3 tempVec(1.0, 1.0, 1.0);
	string scale("scale");
	parseKeywordVector(str, scale, tempVec);
	transform->scale = tempVec;
	return true;
}

bool MyParser::parseRotate(string& str, shared_ptr<Shape> shape) {
	shared_ptr<Transformation> transform = shape->transform;
	glm::vec3 tempVec(0.0, 0.0, 0.0);
	string rotation("rotate");
	parseKeywordVector(str, rotation, tempVec);
	transform->rotateDir = tempVec;
	transform->setRotation();
	return true;
}

void MyParser::parseKeywordVector(string& stringChunk, string& currKeyword, glm::vec3& vec) {
	size_t currStart = 0, vecStart = 0, vecEnd = 0;
	currStart = stringChunk.find(currKeyword);
	vector<float> vec4 = vector<float>();
	if (currStart != stringChunk.npos) {
		vecStart = stringChunk.find("<", currStart + currKeyword.size());
		vecEnd = stringChunk.find(">", currStart + currKeyword.size());
		string subString(stringChunk.substr(vecStart + 1, vecEnd - vecStart - 1));
		parse3FloatVector(subString, vec);
	}
}

void MyParser::parsePigmentVector(string& stringChunk, string& currKeyword, glm::vec3& vec, float& filter) {
	size_t currStart = 0, vecStart = 0, vecEnd = 0;
	vector<float> rgbfVec = vector<float>();
	currStart = stringChunk.find(currKeyword);
	vector<float> vec4 = vector<float>();
	if (currStart != stringChunk.npos) {
		vecStart = stringChunk.find("<", currStart + currKeyword.size());
		vecEnd = stringChunk.find(">", currStart + currKeyword.size());
		string subString(stringChunk.substr(vecStart + 1, vecEnd - vecStart - 1));
		if (stringChunk.find("rgbf") != stringChunk.npos) {
			parse4FloatVector(subString, rgbfVec);
			vec.r = rgbfVec[0];
			vec.g = rgbfVec[1];
			vec.g = rgbfVec[2];
			filter = rgbfVec[3];
		}
		else {
			parse3FloatVector(subString, vec);
		}
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

void MyParser::parse4FloatVector(string& vecString, vector<float>& ret) {
	size_t startPos = 0, endPos = 0;
	for (int i = 0; i < 4; i++) {
		endPos = vecString.find(",", startPos);
		ret.push_back(stof(vecString.substr(startPos, endPos - startPos)));
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


int MyParser::getNumOccur(const std::string str, const std::string substr) {
	size_t currPos = 0;
	int count = 0;
	while ((currPos = str.find(substr, currPos + substr.size())) != str.npos) {
		count++;
	}

	return count;
}