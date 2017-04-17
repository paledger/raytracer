#include "Main.h"
#include "MyParser.cpp"

using namespace std;

glm::vec3 pixelRay(const shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	glm::vec3 rayDirection = scene->calculatePixelRay(width, height, x, y);
	cout << setprecision(4);
	cout << "Pixel: [" << x << " " << y << "] ";
	cout << "Ray: {" << scene->camera->location[0] << \
		" " << scene->camera->location[1] << " " << scene->camera->location[2] << "} ";
	cout << "-> {" << rayDirection[0] << " " << rayDirection[1] << " " << rayDirection[2] << "}\n";
	return rayDirection;
}

void firstHit(const shared_ptr<Scene>& scene, int width, int height, int x, int y) {
	float t;
	glm::vec3 rayDirection = pixelRay(scene, width, height, x, y);
	shared_ptr<Shape> firstHit = scene->getFirstHit(rayDirection, &t);
	cout << setprecision(4);
	if (t == INT_MAX) {
		cout << "No Hit\n";
	}
	else {
		cout << "T = " << t << "\n";
		cout << "Object Type: " << firstHit->getTypeString() << "\n";
		cout << "Color: " << firstHit->pigment[0] << " " << \
			firstHit->pigment[1] << " " << \
			firstHit->pigment[2] << "\n";
	}
}

void render(shared_ptr<Scene>& scene, int width, int height) {
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);
	shared_ptr<Shape> shape;
	glm::vec3 rayDirection;
	float t;
	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			unsigned char red, green, blue;
			rayDirection = scene->calculatePixelRay(width, height, x, y);
			shape = scene->getFirstHit(rayDirection, &t);
			if (shape) {
				red = Helper::convertToRgb(shape->pigment[0]);
				green = Helper::convertToRgb(shape->pigment[1]);
				blue = Helper::convertToRgb(shape->pigment[2]);
			}
			else {
				red = green = blue = 0;
			}

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Please follow this format: raytrace [COMMAND] [INPUT FILENAME].\n";
        return 0;
    }

	auto parser = std::make_shared<MyParser>();
	auto scene = make_shared<Scene>();

	if (!parser->openFile(argv[2])) {
		cout << "Cannot open file given: " << argv[2] << ".\n";
		return 0;
	}

	parser->parseFileToScene(scene);

	// raytrace render <input_filename> <width> <height>
    if (!strcmp(argv[1], "render")) { 
		if (argc < 5) {
			cout << "Please follow the following format to render: raytrace render <input_filename> <width> <height>\n";
		}
		else {
			render(scene, stoi(argv[3]), stoi(argv[4]));
		}
	// raytrace sceneinfo <input_filename>
    } else if (!strcmp(argv[1], "sceneinfo")) { 
		if (argc < 3) {
			cout << "Please follow the following format to see sceneinfo: raytrace sceneinfo <input_filename>\n";
			return 0;
		} 
		scene->printInfo();
	// raytrace pixelray <input_filename> <width> <height> <x> <y>
    } else if (!strcmp(argv[1], "pixelray")) { 
		if (argc < 7) {
			cout << "Please follow the following format to see pixelray: raytrace pixelray <input_filename> <width> <height> <x> <y>\n";
		}
		else {
			// Pixel: [319 239] Ray : {0 0 14} -> {0.220943 0.127908 - 0.966863}
			pixelRay(scene, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		}
	// raytrace firsthit <input_filename> <width> <height> <x> <y>
    } else if (!strcmp(argv[1], "firsthit")) { 
		if (argc < 7) {
			cout << "Please follow the following format to see firsthit: raytrace firsthit <input_filename> <width> <height> <x> <y>\n";
		}
		else {
			firstHit(scene, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		}
    } else {
        cout << "Your command is not one of the four options: render sceneinfo pixelray firsthit\n";
    }
  
	return 0;
}

