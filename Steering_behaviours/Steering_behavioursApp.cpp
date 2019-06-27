#include "Steering_behavioursApp.h"
#include "Texture.h"
#include "Font.h"
#include <ctime>
#include "Input.h"

#define DEFAULT_WINDOW_WIDTH
#define DEFAULT_WINDOW_HEIGHT

Steering_behavioursApp::Steering_behavioursApp() 
{

}

Steering_behavioursApp::~Steering_behavioursApp() 
{

}

bool Steering_behavioursApp::startup() 
{
	srand(time(0));

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./bin/font/consolas.ttf", 32);

	m_bird_sprite = new aie::Texture("./bin/textures/bird_sprite_sheet.png");

	//m_actors.push_back(new actor(m_2dRenderer, m_bird_sprite, { (1.0f) * spacing, (1.0f) * spacing }));
	m_window_dimentions = { float(getWindowWidth()), float(getWindowHeight()) };

	m_flock = new flock(m_2dRenderer, m_bird_sprite);

	m_flock->create_random_boids(1500, m_window_dimentions);

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
	m_window_dimentions = { float(getWindowWidth()), float(getWindowHeight()) };

	m_player->update(deltaTime, m_window_dimentions);

	m_flock->update(deltaTime, m_window_dimentions);

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

	m_flock->draw();
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}