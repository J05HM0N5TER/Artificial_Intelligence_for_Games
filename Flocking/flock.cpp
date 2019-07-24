#include "flock.h"
#include <math.h>
#include <fstream>

flock::flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture, aie::Input* a_input) :
	m_renderer(a_renderer), m_texture(a_texture), m_input(a_input), m_left_mouse_down(false), 
	m_right_mouse_down(false), m_shift_held(false)
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

void flock::create_random_boids(const size_t & a_amount, const Vector2 & a_window_dimentions)
{
	for (size_t i = 0; i < a_amount; i++)
	{
		Vector2 new_spawn_position = { float((rand() + 1) % (int)a_window_dimentions.x), float((rand() + 1) % (int)a_window_dimentions.y) };
		boid* new_boid = new boid(new_spawn_position, this);

		new_boid->m_sprite_timer = fmod(float(rand()) / RAND_MAX, this->SPRITE_ANIMATION_DELAY);

		m_boids.push_back(new_boid);
	}
}

void flock::update(float a_delta_time, const size_t & a_window_dimensions_x, const size_t & a_window_dimensions_y)
{
	static bool initilised = false;
	static int previous_window_x;
	static int previous_window_y;
	Vector2 window_dimensions = { float(a_window_dimensions_x), float(a_window_dimensions_y) };
	if (!initilised)
	{
		previous_window_x = a_window_dimensions_x;
		previous_window_y = a_window_dimensions_y;
		m_quad_tree.restart(aabb(window_dimensions *0.5f, window_dimensions * 1.2f), this->m_boids, QUAD_TREE_CAPACITY);
	}

	m_left_mouse_down = m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT);
	m_right_mouse_down = m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT);
	m_shift_held = m_input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || m_input->isKeyDown(aie::INPUT_KEY_RIGHT_SHIFT);

	for (boid* a_boid : m_boids)
	{
		a_boid->update(a_delta_time, window_dimensions, m_quad_tree);
		//a_boid->update(a_delta_time, a_window_dimentions);
	}

	// Only restart the quad_tree if the dimensions have changed.
	if (previous_window_x == a_window_dimensions_x && previous_window_y == a_window_dimensions_y)
		m_quad_tree.update(m_boids);
	else if (initilised)
		m_quad_tree.restart(aabb(window_dimensions *0.5f, window_dimensions * 1.2f), this->m_boids, QUAD_TREE_CAPACITY);

	previous_window_x = a_window_dimensions_x;
	previous_window_y = a_window_dimensions_y;
	initilised = true;
}

void flock::draw(bool a_draw_quad_tree)
{
	for (boid* a_boid : m_boids)
	{
		a_boid->draw();
	}

	if (a_draw_quad_tree)
	{
		m_quad_tree.draw(m_renderer);
	}
}

