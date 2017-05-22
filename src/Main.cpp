#include "Main.h"
#include "Render.h"
#include "MyParser.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 3) {
        cout << "Please follow this format: raytrace [COMMAND] [INPUT FILENAME].\n";
        return 0;
    }

	auto parser = std::make_shared<MyParser>();
	auto scene = make_shared<Scene>();


	if ((!strcmp(argv[1], "raycast") ||
		!strcmp(argv[1], "sceneinfo") ||
		!strcmp(argv[1], "pixelray") ||
		!strcmp(argv[1], "firsthit") ||
		!strcmp(argv[1], "render") ||
		!strcmp(argv[1], "pixelcolor") ||
		!strcmp(argv[1], "pixeltrace")))
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
			cout << "Please follow the following format to raycast: raytrace raycast <input_filename> <width> <height>\n";
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
		unsigned int mode = BLINNPHONG_MODE, ss = 1;
		bool fresnel = false;
		if (argc < 5) {
			cout << "Please follow the following format to render: raytrace render <input_filename> <width> <height> [-altbrdf]\n";
		}
		else {
			if (argc >= 6) {
				for (int i = 5; i < argc; i++) {
					string arg = string(argv[i]);
					if (arg.find("-altbrdf") != arg.npos) { // -ALTBRDF FOUND
						mode = COOKTORRANCE_MODE;
					}
					if (arg.find("-fresnel") != arg.npos) { // -ALTBRDF FOUND
						fresnel = true;
					}
					if (arg.find("-ss") != arg.npos) { // -ALTBRDF FOUND
						string subnum = arg.substr(arg.find("=") + 1, arg.find_first_of(" \n"));
						unsigned int num = (unsigned int) stoi(subnum.c_str());
						ss = num;
					}
				}
			}

			Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), mode, fresnel, ss);
		}
	}
	// raytrace pixelcolor <input_filename> <width> <height> <x> <y> [-altbrdf]
	else if (!strcmp(argv[1], "pixelcolor")) {
		if (argc < 7) {
			cout << "Please follow the following format to render: raytrace pixelcolor <input_filename> <width> <height> <x> <y> [-altbrdf]\n";
		}
		else {
			if (argc > 7) {
				string arg7 = string(argv[7]);
				if (arg7.find("-altbrdf") != arg7.npos) {
					Render::pixelcolor(scene, stoi(argv[3]), 
						stoi(argv[4]), stoi(argv[5]), stoi(argv[6]), COOKTORRANCE_MODE);
				}
			}
			else {
				Render::pixelcolor(scene, stoi(argv[3]), stoi(argv[4]), 
					stoi(argv[5]), stoi(argv[6]), BLINNPHONG_MODE);
			}
		}
	}
	else if (!strcmp(argv[1], "pixeltrace")) {
		if (argc < 7) {
			cout << "Please follow the following format to render: raytrace pixeltrace <input_filename> <width> <height> <x> <y> [-altbrdf]\n";
		}
		else {
			if (argc > 7) {
				string arg7 = string(argv[7]);
				if (arg7.find("-altbrdf") != arg7.npos) {
					Render::pixelcolor(scene, stoi(argv[3]),
						stoi(argv[4]), stoi(argv[5]), stoi(argv[6]), COOKTORRANCE_MODE);
				}
			}
			else {
				Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), BLINNPHONG_MODE);
				Render::pixelcolor(scene, stoi(argv[3]), stoi(argv[4]),
					stoi(argv[5]), stoi(argv[6]), BLINNPHONG_MODE);
			}
		}
	}
  
	return 0;
}

