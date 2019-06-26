#include "flock.h"


flock::flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture) :
	m_renderer(a_renderer), m_texture(a_texture)
{
}

void flock::create_boid(int a_amount, Vector2& a_spawn_position)
{
	m_boids.push_back(new boid(m_renderer, m_texture, a_spawn_position));
}

void flock::create_random_boids(int a_amount, Vector2 & a_window_dimentions)
{
	for (size_t i = 0; i < a_amount; i++)
	{
		Vector2 new_spawn_position = { float((rand() + 1) % (int)a_window_dimentions.x), float((rand() + 1) % (int)a_window_dimentions.y) };
		boid* new_boid = new boid(m_renderer, m_texture, new_spawn_position);
		m_boids.push_back(new_boid);
		new_boid->set_flock(this);
	}
}

void flock::update(float a_delta_time, Vector2& a_window_dimentions)
{
	for (boid* a_boid : m_boids)
	{
		a_boid->update(a_delta_time, a_window_dimentions);
	}
}

void flock::draw()
{
	for (boid* a_boid : m_boids)
	{
		a_boid->draw();
	}
}

