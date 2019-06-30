#include "Steering_behavioursApp.h"
#include "Texture.h"
#include "Font.h"
#include <ctime>
#include "Input.h"

Steering_behavioursApp::Steering_behavioursApp() 
{ }

Steering_behavioursApp::~Steering_behavioursApp() 
{ }

bool Steering_behavioursApp::startup() 
{
	srand(unsigned int(time(0)));

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_window_dimentions = { float(getWindowWidth()), float(getWindowHeight()) };

	m_input = aie::Input::getInstance();

	return true;
}

void Steering_behavioursApp::shutdown() 
{
	delete m_font;
	delete m_2dRenderer;
}

void Steering_behavioursApp::update(float deltaTime) 
{
	m_window_dimentions = { float(getWindowWidth()), float(getWindowHeight()) };


	// exit the application
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Steering_behavioursApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, m_window_dimentions.y - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}