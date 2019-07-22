#include "FlockingApp.h"
#include "Texture.h"
#include "Font.h"
#include <ctime>
#include "Input.h"

FlockingApp::FlockingApp()
{}

FlockingApp::~FlockingApp() 
{}

bool FlockingApp::startup() 
{
	bool m_draw_quad_tree = false;

	srand(unsigned int(time(0)));

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_bird_sprite = new aie::Texture("../bin/textures/bird_sprite_sheet.png");

	m_window_dimentions = { float(getWindowWidth()), float(getWindowHeight()) };
	//m_window_dimentions = { 500.0f, 550.0f };

	m_flock = new flock(m_2dRenderer, m_bird_sprite);

	m_flock->create_random_boids(10000, m_window_dimentions);
	//m_flock->create_boid(1, Vector2(2, 2));

	m_input = aie::Input::getInstance();

	return true;
}

void FlockingApp::shutdown() 
{

	delete m_font;
	delete m_2dRenderer;
	delete m_flock;
	delete m_bird_sprite;
}

void FlockingApp::update(float deltaTime) 
{
	if (m_input->wasKeyReleased(aie::INPUT_KEY_Q))
	{
		m_draw_quad_tree = !m_draw_quad_tree;
	}

	//deltaTime = 0.1;

	m_window_dimentions = { float(getWindowWidth()), float(getWindowHeight()) };


	m_flock->update(deltaTime, m_window_dimentions);

	// exit the application
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void FlockingApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_flock->draw(m_draw_quad_tree);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, m_window_dimentions.y - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	m_2dRenderer->drawText(m_font, "Press Q to toggle drawing quad tree", 0, 32);

	// done drawing sprites
	m_2dRenderer->end();
}