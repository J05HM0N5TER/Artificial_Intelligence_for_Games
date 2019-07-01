#include "boid.h"
#include "flock.h"
#include <iostream>

boid::boid(aie::Renderer2D* a_renderer, aie::Texture* a_texture, Vector2& a_spawn_position, flock* a_flock) :
	m_renderer(a_renderer), m_texture(a_texture), m_parent_flock(a_flock)
{
	m_draw_size = { 10.0f * 1, 5.0f * 1};

	m_position = a_spawn_position;

	m_velocity = Vector2( 0.0f, 30.0f );

	// If velocity is invalid.
	float temp_mag = this->m_velocity.magnitude();
	if (temp_mag <= 0.00001f)
	{
		// set to go east.
		this->m_velocity = Vector2(m_parent_flock->BOID_SPEED, 0.0f);
	}
	else
	{
		this->m_velocity /= temp_mag;
		this->m_velocity *= m_parent_flock->BOID_SPEED;
	}

}

void boid::set_flock(flock * a_flock)
{
	m_parent_flock = a_flock;
}


void boid::update(float a_delta_time, Vector2& a_window_dimentions)
{
	m_sprite_timer += a_delta_time;

	if (m_sprite_timer > m_parent_flock->SPRITE_ANIMATION_DELAY)
	{
		m_current_sprite++;
		m_sprite_timer -= m_parent_flock->SPRITE_ANIMATION_DELAY;
	}
	if (m_current_sprite > m_parent_flock->SPRITE_COUNT)
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
		if ((a_boid->m_position - this->m_position).square_magnitude() < m_parent_flock->NEIGHBOUR_RADUS * m_parent_flock->NEIGHBOUR_RADUS)
		{
			neighbours.push_back(a_boid);
		}
	}

	// ---Stay in a circle---
	Vector2 world_centre(a_window_dimentions / 2);
	Vector2 to_centre = world_centre - this->m_position;
	float to_centre_mag = to_centre.magnitude();
	float distance_outside_circle = to_centre_mag - a_window_dimentions.y / 2;
	if (distance_outside_circle > 0.0f)
	{
		to_centre /= to_centre_mag;
		to_centre *= distance_outside_circle * m_parent_flock->CIECLE_FORCE_MULT;
		this->apply_force(to_centre);
	}


	// --Separation--
	Vector2 seperation_force;
	for (boid* a_neighbour : neighbours)
	{
		Vector2 from_neibour_to_us = this->m_position - a_neighbour->m_position;
		from_neibour_to_us /= from_neibour_to_us.magnitude();
		from_neibour_to_us *= m_parent_flock->SEPERATION_FORCE_MAG;
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
		from_us_to_average *= m_parent_flock->COHESION_FOECE_MAG;
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

		this->apply_force(average_neighbour_velocity *= m_parent_flock->ALIGHMENT_FORCE_MULT);
	}

	/*
	// --Cursor interaction--
	Vector2 boid_to_cursor = flock->cursor_position - this->m_position;

	float force_magnitude = boid_to_cursor.magnitude();

	force_magnitude *= 0.1f;
	force_magnitude = flock->attract_mult * 10000.0f / (force_magnitude * force_magnitude + 1?)

	boid_to_cursor /= boid_to_cursor.magnitude();
	boid_to_cursor *= force_magnitude;

	this->apply_force(boid_to_cursor);
	*/

	// If velocity is invalid.
	float temp_mag = this->m_velocity.magnitude();
	if (temp_mag <= 0.00001f)
	{
		// set to go east.
		this->m_velocity = Vector2(m_parent_flock->BOID_SPEED, 0.0f );
	}
	else
	{
		this->m_velocity /= temp_mag;
		this->m_velocity *= m_parent_flock->BOID_SPEED;
	}

	this->m_position += this->m_velocity * a_delta_time;

	

}

void boid::draw()
{
	// Set current sprite in texture.
	m_renderer->setUVRect(m_current_sprite / m_parent_flock->SPRITE_COUNT, 0, 1 / m_parent_flock->SPRITE_COUNT, 1);

	// Get the normalised velocity so that I don't have to call that function twice.
	Vector2 normalised = this->m_velocity.normalised();

	// Draw the sprite.
	m_renderer->drawSprite(m_texture, m_position.x, m_position.y, m_draw_size.x, m_draw_size.y, atan2f(normalised.y, normalised.x) - 3.1415f / 2);

	// Reset the UV rect for other things to use.
	m_renderer->setUVRect(0, 0, 1, 1);

	
	//m_renderer->setRenderColour((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);

	//m_renderer->drawCircle(m_position.x, m_position.y, 25.0f);

	//m_renderer->setRenderColour(1, 1, 1);

}

void boid::apply_force(Vector2 & a_force)
{
	this->m_velocity += a_force;
}
