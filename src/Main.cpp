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

	if (!strcmp(argv[1], "raycast") ||
		!strcmp(argv[1], "sceneinfo") ||
		!strcmp(argv[1], "pixelray") ||
		!strcmp(argv[1], "firsthit") ||
		!strcmp(argv[1], "render") ||
		!strcmp(argv[1], "pixelcolor")) 
	{
		if (!parser->openFile(argv[2])) {
			cout << "Cannot open file given: " << argv[2] << ".\n";
			return 0;
		}
	}
	else {
		cout << "Your command is not one of the options: raytrace sceneinfo pixelray firsthit render pixelcolor\n";
	}

	

	parser->parseFileToScene(scene);

	/*** PROJECT 1 COMMANDS ***/
	// raytrace raycast <input_filename> <width> <height>
    if (!strcmp(argv[1], "raycast")) { 
		if (argc < 5) {
			cout << "Please follow the following format to render: raytrace raycast <input_filename> <width> <height>\n";
		}
		else {
			Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), RAYCAST_MODE);
		}
    } 
	// raytrace sceneinfo <input_filename>
	else if (!strcmp(argv[1], "sceneinfo")) {
		if (argc < 3) {
			cout << "Please follow the following format to see sceneinfo: raytrace sceneinfo <input_filename>\n";
			return 0;
		} 
		scene->printInfo();
    } 
	// raytrace pixelray <input_filename> <width> <height> <x> <y>
	else if (!strcmp(argv[1], "pixelray")) { 
		if (argc < 7) {
			cout << "Please follow the following format to see pixelray: raytrace pixelray <input_filename> <width> <height> <x> <y>\n";
		}
		else {
			// Pixel: [319 239] Ray : {0 0 14} -> {0.220943 0.127908 - 0.966863}
			Render::pixelRay(scene, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		}
    } 
	// raytrace firsthit <input_filename> <width> <height> <x> <y>
	else if (!strcmp(argv[1], "firsthit")) { 
		if (argc < 7) {
			cout << "Please follow the following format to see firsthit: raytrace firsthit <input_filename> <width> <height> <x> <y>\n";
		}
		else {
			Render::firstHit(scene, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		}
	}
	/*** PROJECT 2 COMMANDS ***/
	// raytrace render <input_filename> <width> <height> [-altbrdf]
	else if (!strcmp(argv[1], "render")) {
		if (argc < 5) {
			cout << "Please follow the following format to render: raytrace render <input_filename> <width> <height> [-altbrdf]\n";
		}
		else {
			string arg1 = string(argv[1]);
			if (arg1.find("-altbrdf") != arg1.npos) {
			} 
			else {
				Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), BLINNPHONG_MODE);
			}
		}
	}
	// raytrace pixelcolor <input_filename> <width> <height> <x> <y> [-altbrdf]
	else if (!strcmp(argv[1], "pixelcolor")) {

	}
  
	return 0;
}

