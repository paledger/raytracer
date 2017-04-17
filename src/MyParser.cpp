#include "MyParser.h"
#include "Scene.cpp"

using namespace std;

class MyParser
{
public:
	ifstream sceneFile;

	bool openFile(const string &fileName) {
		sceneFile.open(fileName);
		if (!sceneFile) {
			return false;
		}
		return true;
	}

	int parseFileToScene(shared_ptr<Scene>  scene) {
		stringstream buffer;
		string strBuffer, tempStr;
		size_t chunkStart = 0, chunkEnd = 0, currStart = 0, currEnd = 0;
		int counter = 0;

		buffer << sceneFile.rdbuf();
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

private: 
	void removeComments(string& strBuffer) {
		size_t commStart = 0, commEnd = 0;
		while ((commStart = strBuffer.find("//")) != strBuffer.npos) {
			commEnd = strBuffer.find("\n", commStart) + 1;
			strBuffer.erase(commStart, commEnd - commStart);
		}
	}

	void handleChunk(string& strChunk, shared_ptr<Scene> scene) {
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

	bool parseCamera(string& stringChunk, shared_ptr<Camera> cam) {
		parseKeywordVector(stringChunk, string("location"), cam->location);
		parseKeywordVector(stringChunk, string("up"), cam->up);
		parseKeywordVector(stringChunk, string("right"), cam->right);
		parseKeywordVector(stringChunk, string("look_at"), cam->look_at);
		return true;
	}

	bool parseLightSource(string& stringChunk, shared_ptr<LightSource> ls) {
		parseKeywordVector(stringChunk, string("source"), ls->location);
		parseKeywordVector(stringChunk, string("color"), ls->color);
		return true;
	}

	bool parseSphere(string& stringChunk, shared_ptr<Sphere> sphere) {
		parseKeywordVector(stringChunk, string("sphere"), sphere->center);
		parseFloatAfterVec(stringChunk, sphere->radius);
		parsePigment(stringChunk, sphere);
		parseFinish(stringChunk, sphere);
		parseTranslate(stringChunk, sphere);
		parseRotate(stringChunk, sphere);
		parseScale(stringChunk, sphere);
		return true;
	}

	bool parsePlane(string& stringChunk, shared_ptr<Plane> plane) {
		parseKeywordVector(stringChunk, string("plane"), plane->normal);
		parseFloatAfterVec(stringChunk, plane->distance);
		parsePigment(stringChunk, plane);
		parseFinish(stringChunk, plane);
		parseTranslate(stringChunk, plane);
		parseRotate(stringChunk, plane);
		parseScale(stringChunk, plane);
		return true;
	}

	bool parsePigment(string& str, shared_ptr<Shape> shape) {
		parseKeywordVector(str, string("pigment"), shape->pigment);
		return true;
	}

	bool parseFinish(string& str, shared_ptr<Shape> shape) {
		if (str.find("finish") == str.npos) {
			return false;
		}
		size_t ambientStart = str.find("ambient") + strlen("ambient");
		size_t diffuseStart = str.find("diffuse") + strlen("diffuse");

		if (ambientStart != str.npos) {
			shape->ambient = stof(str.substr(ambientStart, str.find_first_of("d}", ambientStart) - ambientStart));
		}
		if (diffuseStart != str.npos) {
			shape->diffuse = stof(str.substr(diffuseStart, str.find_first_of("a}", diffuseStart) - diffuseStart));
		}
		return true;
	}

	bool parseTranslate(string& str, shared_ptr<Shape> shape) {
		glm::vec3 tempVec(0.0, 0.0, 0.0);
		parseKeywordVector(str, string("translate"), tempVec);
		shape->translate = shape->translate + tempVec;
		return true;
	}

	bool parseScale(string& str, shared_ptr<Shape> shape) {
		glm::vec3 tempVec(0.0, 0.0, 0.0);
		parseKeywordVector(str, string("scale"), tempVec);
		shape->scale = shape->scale + tempVec;
		return true;
	}

	bool parseRotate(string& str, shared_ptr<Shape> shape) {
		glm::vec3 tempVec(0.0, 0.0, 0.0);
		parseKeywordVector(str, string("rotate"), tempVec);
		shape->rotate = shape->rotate + tempVec;
		return true;
	}

	void parseKeywordVector(string& stringChunk, string& currKeyword, glm::vec3& vec) {
		size_t currStart = 0, vecStart = 0, vecEnd = 0;

		currStart = stringChunk.find(currKeyword);
		if (currStart != stringChunk.npos) {
			vecStart = stringChunk.find("<", currStart + currKeyword.size());
			vecEnd = stringChunk.find(">", currStart + currKeyword.size());
			parse3FloatVector(stringChunk.substr(vecStart + 1, vecEnd - vecStart - 1), vec);
		}
	}

	// should be given a string of floats separated by commas
	void parse3FloatVector(string& vecString, glm::vec3& ret) {
		size_t startPos = 0, endPos = 0;
		for (int i = 0; i < 3; i++) {
			endPos = vecString.find(",", startPos);
			ret[i] = stof(vecString.substr(startPos, endPos - startPos));
			startPos = endPos + 1;
		}
	}

	void parseFloatAfterVec(string& floatString, float& flt) {
		size_t startRadius = floatString.find(",", floatString.find(">")) + 1;
		size_t endRadius = floatString.find("\n", startRadius);
		flt = stof(floatString.substr(startRadius, endRadius - startRadius));
	}

	vector<string> MyParser::tokenizer(const std::string& inString, char delim) {
		vector<std::string> tokens;
		stringstream   mySstream(inString);
		string         temp;

		while (getline(mySstream, temp, delim)) {
			tokens.push_back(temp);
		}

		return tokens;
	}

	std::vector<std::string> split(const std::string& text, const std::string& delims)
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

	bool contains(string& str, const string substring) {
		if (str.find(substring) != std::string::npos) {
			return true;
		}
		return false;
	}

	string trim(const string& str, const string& whitespace = " \t\n\r\v\f")
	{
		auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
			return ""; // no content

		auto strEnd = str.find_last_not_of(whitespace);
		auto strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}
};