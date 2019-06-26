#include "boid.h"
#include "flock.h"
#include <iostream>

const float boid::sprite_count = 4.0f;
const float boid::neighbour_radus_squared = 25.0f;
const float boid::boid_speed = 20.0f;
const float boid::seperation_force_mag = 20.0f;
const float boid::cohesion_force_mag = 20.0f;


boid::boid(aie::Renderer2D* a_renderer, aie::Texture* a_texture, Vector2& a_spawn_position) :
	m_renderer(a_renderer), m_texture(a_texture)
{
	m_draw_size = { 50.0f, 30.0f };

	m_position = a_spawn_position;

	m_velocity = Vector2( 0.0f, 30.0f );

	// If velocity is invalid.
	if (m_velocity.magnitude() <= 0.000001)
	{
		// set to go east.
		m_velocity = { boid_speed, 0.0f };
	}
	else
	{
		m_velocity /= m_velocity.magnitude();
		m_velocity *= boid_speed;
	}

}

void boid::set_flock(flock * a_flock)
{
	m_parent_flock = a_flock;
}


void boid::update(float a_delta_time, Vector2& a_window_dimentions)
{
	m_sprite_timer += a_delta_time;

	if (m_sprite_timer > 0.05f)
	{
		m_current_sprite++;
		m_sprite_timer = 0.0f;
	}
	if (m_current_sprite > sprite_count)
	{
		m_current_sprite = 0;
	}


	std::vector<boid*> neighbours;
	for (boid* a_boid : m_parent_flock->m_boids)
	{
		// Skip if this is the boid that it is checking.
		if (a_boid == this)
		{
			continue;
		}
		// Check distance and if it is in the neighbourhood.
		if ((a_boid->m_position - this->m_position).square_magnitude() < neighbour_radus_squared)
		{
			neighbours.push_back(a_boid);
		}
	}

	// --Separation--
	Vector2 seperation_force;
	for (boid* a_neighbour : neighbours)
	{
		Vector2 from_neibour_to_us = this->m_position - a_neighbour->m_position;
		from_neibour_to_us /= from_neibour_to_us.magnitude();
		from_neibour_to_us *= seperation_force;
		seperation_force += from_neibour_to_us;
	}

	this->apply_force(seperation_force);


	// --Cohesion--
	if (neighbours.size() > 0)
	{
		Vector2 average_neighbour_position;
		for (boid* a_neighbour : neighbours)
		{
			average_neighbour_position += a_neighbour->m_position;
		}
		average_neighbour_position /= neighbours.size();

		Vector2 from_us_to_average = average_neighbour_position - this->m_position;

		from_us_to_average /= from_us_to_average.magnitude();
		from_us_to_average *= cohesion_force_mag;
		this->apply_force(from_us_to_average);
	}


	// --Alignment--
	if (neighbours.size() > 0)
	{
		Vector2 average_neighbour_velocity;
		for (boid* a_neighbour : neighbours)
		{
			average_neighbour_velocity += a_neighbour->m_velocity;
		}
		average_neighbour_velocity /= neighbours.size();
	}

	// If velocity is invalid.
	if (m_velocity.magnitude() <= 0.000001)
	{
		// set to go east.
		m_velocity = { boid_speed, 0.0f };
	}
	else
	{
		m_velocity /= m_velocity.magnitude();
		m_velocity *= boid_speed;
	}

	m_position += this->m_velocity * a_delta_time;

	

}

void boid::draw()
{
	m_renderer->setUVRect(m_current_sprite / sprite_count, 0, 1 / sprite_count, 1);

	Vector2 normalised = m_velocity.normalised();

	m_renderer->drawSprite(m_texture, m_position.x, m_position.y, m_draw_size.x, m_draw_size.y, atan2f(normalised.y, normalised.x) - 3.1415f / 2);

	m_renderer->setUVRect(0, 0, 1, 1);

}

void boid::apply_force(Vector2 & a_force)
{
	m_velocity += a_force;
}
