#include "Application2D.h"

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("Artificial Intelligence for Games", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}