#include "flock.h"
#include <math.h>
#include <fstream>

flock::flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture, aie::Input* a_input) :
	m_renderer(a_renderer), m_texture(a_texture), m_input(a_input)
{
	m_quad_tree = quad_tree();
}

flock::~flock()
{
	// Delete all boids.
	for (int i = (int)m_boids.size() - 1; i >= 0; i--)
	{
		boid* temp = m_boids[i];
		m_boids.erase(m_boids.begin() + i);
		delete temp;
	}
}

void flock::create_boid(int a_amount, Vector2& a_spawn_position)
{
	m_boids.push_back(new boid(a_spawn_position, this));
}

void flock::create_random_boids(const size_t & a_amount, 
	const Vector2 & a_window_dimentions)
{
	for (size_t i = 0; i < a_amount; i++)
	{
		// Create random position within screen bounds.
		Vector2 new_spawn_position = { float((rand() + 1) % (int)a_window_dimentions.x), 
			float((rand() + 1) % (int)a_window_dimentions.y) };
		// spawn new boid at created position.
		boid* new_boid = new boid(new_spawn_position, this);

		m_boids.push_back(new_boid);
	}
}

void flock::update(float a_delta_time, const size_t & a_window_dimensions_x, 
	const size_t & a_window_dimensions_y, bool a_circle_boundry/* = true*/)
{
	static bool initilised = false;
	static size_t previous_window_x;
	static size_t previous_window_y;
	Vector2 window_dimensions = { float(a_window_dimensions_x), float(a_window_dimensions_y) };
	if (!initilised)
	{
		previous_window_x = a_window_dimensions_x;
		previous_window_y = a_window_dimensions_y;
		m_quad_tree.restart(aabb(window_dimensions *0.5f, window_dimensions * 1.2f), 
			this->m_boids, QUAD_TREE_CAPACITY);
	}

	for (boid* a_boid : m_boids)
	{
		a_boid->update(a_delta_time, window_dimensions, m_quad_tree, a_circle_boundry);
	}

	// Only restart the quad_tree if the dimensions have changed.
	if (previous_window_x == a_window_dimensions_x &&
		previous_window_y == a_window_dimensions_y)
	{
		m_quad_tree.update(m_boids);
	}
	else
	{
		m_quad_tree.restart(aabb(window_dimensions *0.5f, window_dimensions * 1.2f), 
			this->m_boids, QUAD_TREE_CAPACITY);
	}


	// Set previous to current for next update cycle.
	previous_window_x = a_window_dimensions_x;
	previous_window_y = a_window_dimensions_y;
	initilised = true;
}

void flock::draw(bool a_draw_quad_tree)
{
	// Draw all boids.
	for (boid* a_boid : m_boids)
	{
		a_boid->draw();
	}

	// Draw the quad tree if it is selected to.
	if (a_draw_quad_tree)
	{
		m_quad_tree.draw(m_renderer);
	}
}

void flock::clear()
{
	// Delete all boids.
	for (int i = (int)m_boids.size() - 1; i >= 0; i--)
	{
		boid* temp = m_boids[i];
		m_boids.erase(m_boids.begin() + i);
		delete temp;
	}

	// Reset m_boids vector.
	m_boids.clear();
	m_boids.shrink_to_fit();

	// Reset quad tree.
	m_quad_tree.clear();
}

