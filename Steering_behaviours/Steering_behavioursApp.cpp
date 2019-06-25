#include "Steering_behavioursApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Steering_behavioursApp::Steering_behavioursApp() 
{

}

Steering_behavioursApp::~Steering_behavioursApp() 
{

}

bool Steering_behavioursApp::startup() 
{
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);



	m_input = aie::Input::getInstance();



	m_player = new player(m_2dRenderer, m_input, new aie::Texture("../bin/textures/player_texture.png"), { 200.0f, 200.0f });

	return true;
}

void Steering_behavioursApp::shutdown() 
{

	delete m_font;
	delete m_2dRenderer;
}

void Steering_behavioursApp::update(float deltaTime) 
{
	m_player->update(deltaTime);

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
	m_player->draw();
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}