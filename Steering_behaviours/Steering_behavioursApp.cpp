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

	// DEBUG FOR AGENT
	if (m_agent->m_current_state == Agent::WANDER)
	{
		// Draw wander projection
		float start_x = m_agent->m_transform.position.x;
		float start_y = m_agent->m_transform.position.y;
		Vector2 end = { start_x, start_y };
		end += Vector2(m_agent->m_transform.forwards.x, m_agent->m_transform.forwards.y) * m_agent->wander_projection;
		float end_x = end.x;
		float end_y = end.y;
		m_2dRenderer->drawLine(start_x, start_y, end_x, end_y);

		m_2dRenderer->drawCircle(end_x, end_y, m_agent->wander_radus);
		m_2dRenderer->setRenderColour(0, 0, 0, 1);
		m_2dRenderer->drawCircle(end_x, end_y, m_agent->wander_radus - 1);
		m_2dRenderer->setRenderColour(1, 1, 1, 1);

		m_2dRenderer->setRenderColour(1, 0, 0);
		m_2dRenderer->drawLine(m_agent->m_target_position.x, m_agent->m_target_position.y, end_x, end_y);
		m_2dRenderer->setRenderColour(1, 1, 1);
	}


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}