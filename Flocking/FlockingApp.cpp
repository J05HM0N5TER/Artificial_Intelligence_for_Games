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
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_bird_sprite = new aie::Texture("../bin/textures/bird_sprite_sheet.png");


	m_input = aie::Input::getInstance();
	m_2dRenderer = new aie::Renderer2D();

	m_draw_quad_tree = false;
	m_flock = new flock(m_2dRenderer, m_bird_sprite, m_input);
	size_t amount_of_boids = 10000;
	Vector2 window_dimensions = { float(getWindowWidth()), float(getWindowHeight()) };
	m_flock->create_random_boids(amount_of_boids, window_dimensions);

	srand(unsigned int(time(0)));
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
	if (m_input->isKeyDown(aie::INPUT_KEY_2))
		deltaTime *= 2;
	if (m_input->isKeyDown(aie::INPUT_KEY_3))
		deltaTime *= 3;
	if (m_input->isKeyDown(aie::INPUT_KEY_4))
		deltaTime *= 4;
	if (m_input->isKeyDown(aie::INPUT_KEY_5))
		deltaTime *= 5;
	if (m_input->isKeyDown(aie::INPUT_KEY_6))
		deltaTime *= 6;
	if (m_input->isKeyDown(aie::INPUT_KEY_7))
		deltaTime *= 7;
	if (m_input->isKeyDown(aie::INPUT_KEY_8))
		deltaTime *= 8;
	if (m_input->isKeyDown(aie::INPUT_KEY_9))
		deltaTime *= 9;
	if (m_input->isKeyDown(aie::INPUT_KEY_0))
		deltaTime *= 10;

	if (m_input->wasKeyReleased(aie::INPUT_KEY_Q))
	{
		m_draw_quad_tree = !m_draw_quad_tree;
	}

	//deltaTime = 0.1;

	m_flock->update(deltaTime, getWindowWidth(), getWindowHeight());

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


	m_2dRenderer->setRenderColour(.5f, 0.f, 0.f);
	//m_2dRenderer->drawCircle(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, 1.f);
	m_2dRenderer->drawBox(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, 1, 1);
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f);

	// draw your stuff here!
	m_flock->draw(m_draw_quad_tree);
	short int text_layer = 0;

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, getWindowHeight() - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 32/*Font hight*/ * text_layer++);
	m_2dRenderer->drawText(m_font, "Press Q to toggle drawing quad tree", 0, 32/*Font hight*/ * text_layer++);
	if (m_input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || m_input->isKeyDown(aie::INPUT_KEY_RIGHT_SHIFT))
	{
		//m_2dRenderer->drawText(m_font, "release shift to switch to regular controls.", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold left mouse to attract boids fast", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold right mouse to repel boids fast", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold right mouse and left mouse to teleport boids to mouse", 0, 32/*Font hight*/ * text_layer++);
	}
	else
	{
		//m_2dRenderer->drawText(m_font, "Hold shift to switch to cheat controls.", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold left mouse to attract boids", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold right mouse to repel boids", 0, 32/*Font hight*/ * text_layer++);
	}
	m_2dRenderer->drawText(m_font, "Press numbers to speed up simulation", 0, 32/*Font hight*/ * text_layer++);


	// done drawing sprites
	m_2dRenderer->end();
}