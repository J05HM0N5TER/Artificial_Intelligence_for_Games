#include "FlockingApp.h"
#include "Texture.h"
#include "Font.h"
#include <ctime>
#include "Input.h"
#include <string>

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

	current_state = GAME_STATE::START;

	m_input = aie::Input::getInstance();
	m_2dRenderer = new aie::Renderer2D();

	m_flock = new flock(m_2dRenderer, m_bird_sprite, m_input);
	m_draw_quad_tree = false;

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
	switch (current_state)
	{
	case GAME_STATE::START:
		start_update(deltaTime);
		break;
	case GAME_STATE::ACTIVE:
		active_update(deltaTime);
		break;
	default:
		break;
	}

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

	switch (current_state)
	{
	case GAME_STATE::START:
		start_draw();
		break;
	case GAME_STATE::ACTIVE:
		active_draw();
		break;
	default:
		break;
	}


	// done drawing sprites
	m_2dRenderer->end();
}

void FlockingApp::active_update(float deltaTime)
{
	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (m_input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (m_input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (m_input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (m_input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);


	// Check for all number inputs.
	for (char i = 0; i < 10; i++)
	{
		// And multiply time by that number.
		if (m_input->isKeyDown(aie::INPUT_KEY_0 + i))
			deltaTime *= i;
	}

	if (m_input->wasKeyReleased(aie::INPUT_KEY_Q))
	{
		m_draw_quad_tree = !m_draw_quad_tree;
	}
	if (m_input->wasKeyReleased(aie::INPUT_KEY_R))
	{
		m_flock->clear();
		current_state = GAME_STATE::START;
	}

	//deltaTime = 0.1;

	m_flock->update(deltaTime, getWindowWidth(), getWindowHeight());
}

void FlockingApp::active_draw()
{

	m_2dRenderer->setRenderColour(.5f, 0.f, 0.f);
	//m_2dRenderer->drawCircle(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, 1.f);
	m_2dRenderer->drawBox(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f, 1, 1);
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f);

	// draw your stuff here!
	m_flock->draw(m_draw_quad_tree);
	if (m_draw_quad_tree)
	{
		// If the quad tree is being drawn then draw the outside boundaries.
		float window_height = float(getWindowHeight());
		float windwo_width = float(getWindowWidth());

		m_2dRenderer->drawLine(-(windwo_width * 0.1f), -(window_height * 0.1f), windwo_width * 1.1f, -(window_height * 0.1f));
		m_2dRenderer->drawLine(-(windwo_width * 0.1f), -(window_height * 0.1f), -(windwo_width * 0.1f), window_height * 1.1f);
		m_2dRenderer->drawLine(windwo_width * 1.1f, window_height * 1.1f, -(windwo_width * 0.1f), window_height * 1.1f);
		m_2dRenderer->drawLine(windwo_width * 1.1f, window_height * 1.1f, windwo_width * 1.1f, -(window_height * 0.1f));
	}

	short int text_layer = 0;

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, getWindowHeight() - 32.f);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 32.f/*Font hight*/ * text_layer++);
	m_2dRenderer->drawText(m_font, "Press Q to toggle drawing quad tree", 0, 32.f/*Font hight*/ * text_layer++);
	if (m_input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || m_input->isKeyDown(aie::INPUT_KEY_RIGHT_SHIFT))
	{
		//m_2dRenderer->drawText(m_font, "release shift to switch to regular controls.", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold left mouse to attract boids fast", 0, 32.f/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold right mouse to repel boids fast", 0, 32.f/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "press T to teleport boids to mouse", 0, 32.f/*Font hight*/ * text_layer++);
	}
	else
	{
		//m_2dRenderer->drawText(m_font, "Hold shift to switch to cheat controls.", 0, 32/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold left mouse to attract boids", 0, 32.f/*Font hight*/ * text_layer++);
		m_2dRenderer->drawText(m_font, "Hold right mouse to repel boids", 0, 32.f/*Font hight*/ * text_layer++);
	}
	m_2dRenderer->drawText(m_font, "Press numbers to change simulation speed", 0, 32.f/*Font hight*/ * text_layer++);
	m_2dRenderer->drawText(m_font, "Press R to reset", 0, 32.f/*Font hight*/ * text_layer++);
}

void FlockingApp::start_update(float deltaTime)
{
	// Check for all number inputs.
	for (int i = 0; i < 10; i++)
	{
		// And add any numbers has been pressed.
		if (m_input->wasKeyPressed(aie::INPUT_KEY_0 + i))
			m_user_number.push_back(i);
	}

	if (m_input->wasKeyPressed(aie::INPUT_KEY_BACKSPACE))
	{
		if (m_user_number.size() > 0)
			m_user_number.pop_back();
	}


	if (m_input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		size_t amount_of_boids = 0;

		for (size_t i = 0; i < m_user_number.size(); i++)
		{
			size_t ten_pow_i = 1;
			for (int j = 0; j < m_user_number.size() - (i + 1); j++)
			{
				ten_pow_i *= 10;
			}

			amount_of_boids += m_user_number[i] * ten_pow_i;

			//amount_of_boids += m_user_number[i] * pow(10, m_user_number.size() - i - 1);
		}

		Vector2 window_dimensions = { float(getWindowWidth()), float(getWindowHeight()) };
		m_flock->create_random_boids(amount_of_boids, window_dimensions);

		current_state = GAME_STATE::ACTIVE;
	}
}

void FlockingApp::start_draw()
{
	// String to hold converted std::vector copy.
	std::string user_display_string;

	// Copy values to string.
	for (int i = 0; i < int(m_user_number.size()); i++)
	{
		user_display_string = user_display_string + char(48 + m_user_number[i]);
	}

	// Create dynamic char array.
	char* user_number_display = new char[m_user_number.size() + 1]{ char('/0') };

	// Copying the contents of the string to char array .
	strcpy(user_number_display, user_display_string.c_str());

	float number_string_height = m_font->getStringHeight(user_number_display);
	float number_string_width = m_font->getStringWidth(user_number_display);

	float window_height = float(getWindowHeight());
	float window_width = float(getWindowWidth());

	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f);
	m_2dRenderer->drawBox(getWindowWidth() / 2.f, window_height / 2.f + number_string_height / 2.f, number_string_width + 40.f, number_string_height + 40.f);
	m_2dRenderer->setRenderColour(0.8f, 0.2f, 0.f);

	// Display number.
	m_2dRenderer->drawText(m_font, user_number_display, window_width / 2.f - number_string_width / 2.f, window_height / 2.f);

	// Display instructions.
	char instructions[] = "Enter the amount of boids you want and press enter to continue.";
	m_2dRenderer->drawText(m_font, instructions, window_width / 2.f - m_font->getStringWidth(instructions) / 2.f, window_height - 32);

	char instruction2[] = "Be careful on the amount because too many will cause a crash!";
	m_2dRenderer->drawText(m_font, instruction2, window_width / 2.f - m_font->getStringWidth(instruction2) / 2.f, window_height - 32 * 2);

	delete[] user_number_display;
	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f);

	//m_2dRenderer->drawText()
}
