#include "boid.h"
#include "flock.h"
#include <iostream>

boid::boid(Vector2& a_spawn_position, flock* a_flock) :
	m_flock(a_flock), m_position(a_spawn_position)
{
	m_velocity = Vector2(0.0f, 30.0f);

	// If velocity is invalid.
	float temp_mag = this->m_velocity.magnitude();
	if (temp_mag <= 0.00001f)
	{
		// set to go east.
		this->m_velocity = Vector2(m_flock->BOID_SPEED, 0.0f);
	}
	else
	{
		this->m_velocity /= temp_mag;
		this->m_velocity *= m_flock->BOID_SPEED;
	}

}

void boid::set_flock(flock * a_flock)
{
	m_flock = a_flock;
}


void boid::update(float a_delta_time, const Vector2 & a_window_dimentions, const quad_tree & a_quad_tree)
{
	m_sprite_timer += a_delta_time;

	if (m_sprite_timer > m_flock->SPRITE_ANIMATION_DELAY)
	{
		m_current_sprite++;
		m_sprite_timer -= m_flock->SPRITE_ANIMATION_DELAY;
	}
	if (m_current_sprite > m_flock->SPRITE_COUNT)
	{
		m_current_sprite = 0;
	}

	// Find neighbours.
	std::vector<boid*> neighbours;
	a_quad_tree.search(circle(this->get_position(), m_flock->NEIGHBOUR_RADUS), neighbours, this);


	// ---Stay in a circle---
	Vector2 world_centre(a_window_dimentions / 2);
	Vector2 to_centre = world_centre - this->m_position;
	float to_centre_mag = to_centre.magnitude();
	float distance_outside_circle = to_centre_mag - a_window_dimentions.y / 2;
	if (distance_outside_circle > 0.0f)
	{
		to_centre /= to_centre_mag;
		to_centre *= distance_outside_circle * m_flock->CIECLE_FORCE_MULT;
		this->apply_force(to_centre);
	}


	// --Separation--
	Vector2 seperation_force;
	for (boid* a_neighbour : neighbours)
	{
		Vector2 from_neibour_to_us = this->m_position - a_neighbour->m_position;
		from_neibour_to_us /= from_neibour_to_us.magnitude();
		from_neibour_to_us *= m_flock->SEPERATION_FORCE_MAG;
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
		average_neighbour_position /= float(neighbours.size());

		Vector2 from_us_to_average = average_neighbour_position - this->m_position;

		from_us_to_average /= from_us_to_average.magnitude();
		from_us_to_average *= m_flock->COHESION_FOECE_MAG;
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
		average_neighbour_velocity /= float(neighbours.size());

		this->apply_force(average_neighbour_velocity *= m_flock->ALIGHMENT_FORCE_MULT);
	}

	
	// --Cursor interaction--

	// Attract with left mouse button..
	if (m_flock->m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		Vector2 mouse_pos(float(m_flock->m_input->getMouseX()), float(m_flock->m_input->getMouseY()));
		Vector2 boid_to_cursor = mouse_pos - this->m_position;

		float force_magnitude = boid_to_cursor.magnitude();

		force_magnitude *= 0.1f;
		force_magnitude = m_flock->ATTRACT_MULT / (force_magnitude * force_magnitude);

		boid_to_cursor /= boid_to_cursor.magnitude();
		boid_to_cursor *= force_magnitude;

		this->apply_force(boid_to_cursor);
	}
	
	// Force away with right mouse button.
	if (m_flock->m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		Vector2 mouse_pos(float(m_flock->m_input->getMouseX()), float(m_flock->m_input->getMouseY()));
		Vector2 boid_to_cursor = mouse_pos - this->m_position;

		float force_magnitude = boid_to_cursor.magnitude();

		force_magnitude *= 0.1f;
		force_magnitude = m_flock->REPEL_MULT / (force_magnitude * force_magnitude);

		boid_to_cursor /= boid_to_cursor.magnitude();
		boid_to_cursor *= force_magnitude;

		this->apply_force(boid_to_cursor);
	}


	// If velocity is invalid.
	float temp_mag = this->m_velocity.magnitude();
	if (temp_mag <= 0.00001f)
	{
		// set to go east.
		this->m_velocity = Vector2(m_flock->BOID_SPEED, 0.0f);
	}
	else
	{
		// Check that the boid is going the correct speed.
		this->m_velocity /= temp_mag;
		this->m_velocity *= m_flock->BOID_SPEED;
	}


	// Cheat controls (These can change the speed of the boid so they are not technically correct boids then.)
	if (m_flock->m_input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || m_flock->m_input->isKeyDown(aie::INPUT_KEY_RIGHT_SHIFT))
	{
		if (m_flock->m_input->isKeyDown(aie::INPUT_KEY_T))
		{
			m_position = { float(m_flock->m_input->getMouseX()) + float(rand() % 100 - 50), 
				float(m_flock->m_input->getMouseY()) + float(rand() % 100 - 50) };
		}

		// Attract with left mouse button..
		else if (m_flock->m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
		{
			Vector2 mouse_pos(float(m_flock->m_input->getMouseX()), float(m_flock->m_input->getMouseY()));
			Vector2 boid_to_cursor = mouse_pos - this->m_position;

			float force_magnitude = boid_to_cursor.magnitude();

			force_magnitude *= 0.1f;
			force_magnitude = m_flock->ATTRACT_MULT / (force_magnitude * force_magnitude);

			boid_to_cursor /= boid_to_cursor.magnitude();
			boid_to_cursor *= force_magnitude;

			this->apply_force(boid_to_cursor);
		}

		// Force away with right mouse button.
		else if (m_flock->m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
		{
			Vector2 mouse_pos(float(m_flock->m_input->getMouseX()), float(m_flock->m_input->getMouseY()));
			Vector2 boid_to_cursor = mouse_pos - this->m_position;

			float force_magnitude = boid_to_cursor.magnitude();

			force_magnitude *= 0.1f;
			force_magnitude = m_flock->REPEL_MULT / (force_magnitude * force_magnitude);

			boid_to_cursor /= boid_to_cursor.magnitude();
			boid_to_cursor *= force_magnitude;

			this->apply_force(boid_to_cursor);
		}
	}

	// Apply changes.
	this->m_position += this->m_velocity * a_delta_time;
}

void boid::draw()
{
	// Draw as texture--

	// Set current sprite in texture.
	m_flock->m_renderer->setUVRect(m_current_sprite / m_flock->SPRITE_COUNT, 
		0, 1 / m_flock->SPRITE_COUNT, 1);

	// Cache normalised velocity.
	Vector2 normalised = this->m_velocity.normalised();

	// Draw the sprite.
	m_flock->m_renderer->drawSprite(m_flock->m_texture, m_position.x, m_position.y, 
		m_flock->m_draw_size.x, m_flock->m_draw_size.y, 
		atan2f(normalised.y, normalised.x) - 3.14159f / 2);

	// Reset the UV rect for other things to use.
	m_flock->m_renderer->setUVRect(0, 0, 1, 1);
	


	// -- Draw as circle--
	//m_renderer->setRenderColour((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);

	//m_flock->m_renderer->drawCircle(m_position.x, m_position.y, 3.0f);

	//m_renderer->setRenderColour(1, 1, 1);
}

void boid::apply_force(Vector2 & a_force)
{
	this->m_velocity += a_force;
}

const Vector2 & boid::get_position() const
{
	return m_position;
}

void boid::set_position(const Vector2 & a_position)
{
	m_position = a_position;
}

const float boid::get_radus() const
{
	return m_flock->NEIGHBOUR_RADUS;
}
