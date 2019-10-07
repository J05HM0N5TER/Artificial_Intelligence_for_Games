#include "Steering_behavioursApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Steering_behavioursApp::Steering_behavioursApp() {

}

Steering_behavioursApp::~Steering_behavioursApp() {

}

bool Steering_behavioursApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_ship_texture = new aie::Texture("../bin/textures/player_texture.png");

	m_agent = new Agent();

	return true;
}

void Steering_behavioursApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_ship_texture;
	delete m_agent;
}

void Steering_behavioursApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_agent->update(deltaTime);


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Steering_behavioursApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawSpriteTransformed3x3(m_ship_texture, m_agent->m_transform, 100, 100);


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}