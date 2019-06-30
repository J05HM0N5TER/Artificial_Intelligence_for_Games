#include "player.h"



player::player(aie::Renderer2D* a_renderer, aie::Input* a_input, aie::Texture* a_texture, const Vector2 a_position) :
	game_object(a_renderer, a_texture, a_position), m_input(a_input)
{
	m_size = { float(m_texture->getWidth()) * 0.75f, float(m_texture->getHeight()) * 0.75f };

	m_max_speed = 350.0f;
	m_max_reverse_speed = -150.0f;
}


void player::update(float a_delta_time, Vector2& a_window_dimentions)
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

	if (m_local_transform.position.x > a_window_dimentions.x)
	{
		m_local_transform.position.x = a_window_dimentions.x;
	}
	else if (m_local_transform.position.x < 0.0f)
	{
		m_local_transform.position.x = 0.1f;
	}
	if (m_local_transform.position.y > a_window_dimentions.y)
	{
		m_local_transform.position.y = a_window_dimentions.y;
	}
	else if (m_local_transform.position.y < 0.0f)
	{
		m_local_transform.position.y = 0.0f;
	}
}

player::~player()
{
}
