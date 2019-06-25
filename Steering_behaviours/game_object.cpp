#include "game_object.h"
#include <iostream>

game_object::game_object(aie::Renderer2D* a_renderer, aie::Texture* a_texture, const Vector2 a_position,
	const float a_z_rotation /*= 0.0f*/, const Vector2 a_size /*= { 0.0f, 0.0f }*/,
	const float a_spin_speed /*= 0.0f*/, const float a_orbit_speed /*= 0.0f*/) :
	m_renderer(a_renderer), m_rotation_speed(a_spin_speed), m_orbit_speed(a_orbit_speed),
	m_current_rotation(a_z_rotation), m_size(a_size), m_texture(a_texture),
	m_parent(nullptr), m_collider(nullptr), is_valid(true), m_speed(0.0f), m_acceleration(0.0f), m_max_speed(500.0f)
{
	// Set the parent to null at start so it is easy to detect that there is not one set yet.
	//m_parent = nullptr;

	m_local_transform.setRotateZ(m_current_rotation);
	m_local_transform.position = { a_position.x, a_position.y, 1.0f };

	// Default values set.
	//m_speed = 0.0f;
	//m_acceleration = 0.0f;
	//m_max_speed = 500.0f;

	// Set the colider to null at start so it is easy to detect that there is not one set yet.
	//m_collider = nullptr;
	//is_valid = true;
}

void game_object::update(const float a_delta_time)
{
	// Acceleration math.
	m_speed += m_acceleration * a_delta_time;
	// Limit speed to max speed and negative max speed.
	if (m_speed > m_max_speed)
	{
		m_speed = m_max_speed;
	}
	else if (m_speed < -m_max_speed)
	{
		m_speed = -m_max_speed;
	}



	// Calculate based on speed.
	m_local_transform.position += m_local_transform.forwards * m_speed * a_delta_time;

	// Matrix that the transformations are applied to.
	Matrix3 rotation_matrix;

	// Rotate the object.
	rotation_matrix.setRotateZ(a_delta_time * m_rotation_speed);
	m_local_transform *= rotation_matrix;

	// Set orbit speed.
	rotation_matrix.setRotateZ(a_delta_time * m_orbit_speed);
	m_local_transform = rotation_matrix * m_local_transform;

	// childing
	if (m_parent)
	{
		// Calculate the global position of the earth off the sun position.
		m_world_transform = m_parent->get_world_matrix() * m_local_transform;
	}
	else
	{
		m_world_transform = m_local_transform;
	}

	// loop though all children and call update for them.
	for (size_t i = 0; i < m_children.size(); i++)
	{
		m_children[i]->update(a_delta_time);
	}

	// Update position for collider.
	if (m_collider)
	{
		m_collider->set_position({ m_world_transform.position.x, m_world_transform.position.y });
	}
}

void game_object::draw()
{
	m_renderer->drawSpriteTransformed3x3(m_texture,
		m_world_transform, m_size.x, m_size.y);

	// loop though all children and call draw for them.
	for (size_t i = 0; i < m_children.size(); i++)
	{
		m_children[i]->draw();
	}
}

const Matrix3 & game_object::get_world_matrix() const
{
	return m_world_transform;
}

void game_object::set_local_position(const Vector2 & a_position)
{
	m_local_transform.position.x = a_position.x;
	m_local_transform.position.y = a_position.y;
}

const Vector2 game_object::get_local_position() const
{
	return { m_local_transform.position.x, m_local_transform.position.y };
}

void game_object::set_local_rotation(const float & a_rotation)
{
	m_local_transform.setRotateZ(a_rotation);
}

const float game_object::get_global_rotation() const
{
	game_object* current_game_object;
	float rotaion_counter = 0.0f;

	// Checks if the game_object has an assigned parent.
	if (m_parent)
	{
		current_game_object = this->m_parent;

		// While there is a parent.
		while (current_game_object != nullptr)
		{
			// Add to the rotation_counter.
			rotaion_counter += current_game_object->m_orbit_speed + current_game_object->m_rotation_speed;
			// Go to next parent.
			current_game_object = current_game_object->get_parent();
		}
	}
	// Add the local rotation speed and orbit speed.
	rotaion_counter += m_rotation_speed + m_orbit_speed;

	return rotaion_counter;
}

void game_object::set_global_rotation(const float& a_rotaion_speed)
{
	m_rotation_speed = -this->get_global_rotation() + a_rotaion_speed;
}

void game_object::set_global_orbit(const float & a_orbit_speed)
{
	m_orbit_speed = -this->get_global_rotation() + a_orbit_speed;
}

void game_object::set_orbit_speed(const float & a_orbit_speed)
{
	m_orbit_speed = a_orbit_speed;
}

const float & game_object::get_orbit_speed() const
{
	return m_orbit_speed;
}

const float & game_object::get_rotation_speed() const
{
	return m_rotation_speed;
}

void game_object::set_rotation_speed(const float a_rotation_speed)
{
	m_rotation_speed = a_rotation_speed;
}

void game_object::set_parent(game_object * a_parent)
{
	m_parent = a_parent;
	m_parent->add_child(this);
}

game_object * game_object::get_parent() const
{
	return m_parent;
}

void game_object::add_child(game_object * a_child)
{
	m_children.push_back(a_child);
}

void game_object::set_size(const Vector2 & a_size)
{
	m_size = a_size;
}

const Vector2 & game_object::get_size() const
{
	return m_size;
}

void game_object::set_acceleration(const float  a_acceleration)
{
	m_acceleration = a_acceleration;
}

const float game_object::get_acceleration() const
{
	return m_acceleration;
}

void game_object::set_speed(const float & a_speed)
{
	m_speed = a_speed;
}

const float & game_object::get_speed() const
{
	return m_speed;
}

void game_object::set_collider(circle* a_colider)
{
	m_collider = a_colider;
}

const circle* game_object::get_collider() const
{
	return m_collider;
}

void game_object::set_texture(aie::Texture * a_texture)
{
	m_texture = a_texture;
}

const aie::Texture * game_object::get_texture() const
{
	return m_texture;
}

void game_object::set_max_speed(const float a_max_speed)
{
	m_max_speed = a_max_speed;
}

const float game_object::get_max_speed() const
{
	return m_max_speed;
}

const Matrix3 & game_object::get_local_transform() const
{
	return m_local_transform;
}

void game_object::set_local_transform(const Matrix3 & a_local_transform)
{
	m_local_transform = a_local_transform;
}


