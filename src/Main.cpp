#include "Main.h"
#include "Render.h"
#include "MyParser.h"
#include "Flags.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 3) {
        cout << "Please follow this format: raytrace [COMMAND] [INPUT FILENAME].\n";
        return 0;
    }

	auto parser = make_shared<MyParser>();
	auto scene = make_shared<Scene>();
	Flags flags = Flags();


	if ((!strcmp(argv[1], "raycast") ||
		!strcmp(argv[1], "sceneinfo") ||
		!strcmp(argv[1], "pixelray") ||
		!strcmp(argv[1], "firsthit") ||
		!strcmp(argv[1], "render") ||
		!strcmp(argv[1], "pixelcolor") ||
		!strcmp(argv[1], "pixeltrace") ||
		!strcmp(argv[1], "printrays") ||
		!strcmp(argv[1], "bvhtest")))
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
			flags.mode = RAYCAST_MODE;
			Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), flags);
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
			if (argc >= 5) {
				for (int i = 5; i < argc; i++) {
					string arg = string(argv[i]);
					if (arg.find("-altbrdf") != arg.npos) { // -ALTBRDF FOUND
						flags.mode = COOKTORRANCE_MODE;
					}
					if (arg.find("-fresnel") != arg.npos) { // -FRESNEL FOUND
						cout << "FRESNEL ON" << endl;
						flags.fresnel = true;
					}
					if (arg.find("-sds") != arg.npos) { // -SDS FOUND
						cout << "BVH ON" << endl;
						flags.bvh = true;
					}
					if (arg.find("-ss") != arg.npos) { // -SS found and calculated
						string subnum = arg.substr(arg.find("=") + 1, arg.find_first_of(" \n"));
						unsigned int num = (unsigned int) stoi(subnum.c_str());
						flags.ss = num;
					}
				}
			}

			Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), flags);
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
					flags.mode = COOKTORRANCE_MODE;
					Render::pixelcolor(scene, stoi(argv[3]), 
						stoi(argv[4]), stoi(argv[5]), stoi(argv[6]), flags);
				}
			}
			else {
				Render::pixelcolor(scene, stoi(argv[3]), stoi(argv[4]), 
					stoi(argv[5]), stoi(argv[6]), flags);
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
					flags.mode = COOKTORRANCE_MODE;
					Render::pixelcolor(scene, stoi(argv[3]),
						stoi(argv[4]), stoi(argv[5]), stoi(argv[6]), flags);
				}
			}
			else {
				Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), flags);
				Render::pixelcolor(scene, stoi(argv[3]), stoi(argv[4]),
					stoi(argv[5]), stoi(argv[6]), flags);
			}
		}
	}
	else if (!strcmp(argv[1], "printrays")) {
		if (argc < 7) {
			cout << "Please follow the following format to render: raytrace printrays <input_filename> <width> <height> <x> <y> [-altbrdf]\n";
		}
		else {
			if (argc >= 8) {
				for (int i = 5; i < argc; i++) {
					string arg = string(argv[i]);
					if (arg.find("-altbrdf") != arg.npos) { // -ALTBRDF FOUND
						flags.mode = COOKTORRANCE_MODE;
					}
					if (arg.find("-fresnel") != arg.npos) { // -FRESNEL FOUND
						cout << "FRESNEL ON\n";
						flags.fresnel = true;
					}
					if (arg.find("-ss") != arg.npos) { // -SS FOUND
						string subnum = arg.substr(arg.find("=") + 1, arg.find_first_of(" \n"));
						unsigned int num = (unsigned int)stoi(subnum.c_str());
						flags.ss = num;
					}
				}
			}

			Render::pixelcolor(scene, stoi(argv[3]), stoi(argv[4]),
				stoi(argv[5]), stoi(argv[6]), flags);
			//Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), mode, fresnel, ss);
		}
	}
	else if (!strcmp(argv[1], "bvhtest")) {
		if (argc < 7) {
			cout << "Please follow the following format to render: raytrace printrays <input_filename> <width> <height> <x> <y> [-altbrdf]\n";
		}
		else {
			if (argc >= 8) {
				for (int i = 5; i < argc; i++) {
					string arg = string(argv[i]);
					if (arg.find("-altbrdf") != arg.npos) { // -ALTBRDF FOUND
						flags.mode = COOKTORRANCE_MODE;
					}
					if (arg.find("-fresnel") != arg.npos) { // -FRESNEL FOUND
						cout << "FRESNEL ON\n";
						flags.fresnel = true;
					}
					if (arg.find("-ss") != arg.npos) { // -SS FOUND
						string subnum = arg.substr(arg.find("=") + 1, arg.find_first_of(" \n"));
						unsigned int num = (unsigned int)stoi(subnum.c_str());
						flags.ss = num;
					}
				}
			}
			flags.bvh = true;
			flags.bvhtest = true;
			Render::pixelcolor(scene, stoi(argv[3]), stoi(argv[4]),
				stoi(argv[5]), stoi(argv[6]), flags);
			flags.bvhtest = false;
			Render::createOutput(scene, stoi(argv[3]), stoi(argv[4]), flags);
		}
	}
  
	return 0;
}

