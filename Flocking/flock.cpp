#include "flock.h"
#include <math.h>
#include <fstream>

flock::flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture) :
	m_renderer(a_renderer), m_texture(a_texture)
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

void flock::update(float a_delta_time, Vector2& a_window_dimentions)
{
	static float timer = 0.0f;
	timer += a_delta_time;

	if (timer > 5.f)
	{
		m_quad_tree.clear();
		timer -= 5.f;
	}


	m_quad_tree.restart(aabb(a_window_dimentions * 0.5f, a_window_dimentions * 1.2f), QUAD_TREE_CAPACITY);

	for (boid* a_boid : m_boids)
	{
		m_quad_tree.insert(a_boid);
	}

	for (boid* a_boid : m_boids)
	{
		a_boid->update(a_delta_time, a_window_dimentions, m_quad_tree);
		//a_boid->update(a_delta_time, a_window_dimentions);
	}
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

