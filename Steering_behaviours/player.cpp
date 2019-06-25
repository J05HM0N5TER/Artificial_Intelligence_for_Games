#include "player.h"



player::player(aie::Renderer2D* a_renderer, aie::Input* a_input, aie::Texture* a_texture, const Vector2 a_position) :
	game_object(a_renderer, a_texture, a_position), m_input(a_input)
{
	m_size = { float(m_texture->getWidth()), float(m_texture->getHeight()) };
}


void player::update(float a_delta_time)
{
	// ---Player controls---
	float acceleration_speed = 100.0f;
	float rotation_speed = 5.0f;

	if (m_input->isKeyDown(aie::INPUT_KEY_UP))
	{
		this->set_acceleration(acceleration_speed);
	}
	// down
	else if (m_input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		this->set_acceleration(-acceleration_speed);
	}
	else
	{
		this->set_acceleration(0.0f);
	}
	// left
	if (m_input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		this->set_rotation_speed(rotation_speed);
	}
	// right
	else if (m_input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		this->set_rotation_speed(-rotation_speed);
	}
	else
	{
		this->set_rotation_speed(0.0f);
	}

	this->calculate_location(a_delta_time);
}

player::~player()
{
}
