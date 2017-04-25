#include "Main.h"
#include "Render.h"
#include "MyParser.h"

using namespace std;

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
			Render::render(scene, stoi(argv[3]), stoi(argv[4]));
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
			Render::pixelRay(scene, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		}
	// raytrace firsthit <input_filename> <width> <height> <x> <y>
    } else if (!strcmp(argv[1], "firsthit")) { 
		if (argc < 7) {
			cout << "Please follow the following format to see firsthit: raytrace firsthit <input_filename> <width> <height> <x> <y>\n";
		}
		else {
			Render::firstHit(scene, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		}
    } else {
        cout << "Your command is not one of the four options: render sceneinfo pixelray firsthit\n";
    }
  
	return 0;
}

