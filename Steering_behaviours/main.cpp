#include "Steering_behavioursApp.h"

int main() 
{
	
	// allocation
	auto app = new Steering_behavioursApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}