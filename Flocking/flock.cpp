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
	m_boids.push_back(new boid(m_renderer, m_texture, a_spawn_position, this));
}

void flock::create_random_boids(int a_amount, Vector2 & a_window_dimentions)
{
	for (size_t i = 0; i < a_amount; i++)
	{
		Vector2 new_spawn_position = { float((rand() + 1) % (int)a_window_dimentions.x), float((rand() + 1) % (int)a_window_dimentions.y) };
		boid* new_boid = new boid(m_renderer, m_texture, new_spawn_position, this);
		float randVal = float(rand()) / RAND_MAX;
		new_boid->m_sprite_timer = fmod(randVal, this->SPRITE_ANIMATION_DELAY);

		m_boids.push_back(new_boid);
	}
}

void flock::update(float a_delta_time, Vector2& a_window_dimentions)
{
	/*std::ofstream file("debug.csv", std::ios::out | std::ios::in);
	if (!file.good())
	{
		file.close();
		std::ofstream file("debug.csv", std::ios::out);
	}
	else
	{
		file.seekp(0, std::ios::end);
		for (boid* a_boid : m_boids)
		{
			file << a_boid->get_position().x << "," << a_boid->get_position().y << "," << a_boid->m_velocity.x << "," << a_boid->m_velocity.y << ",,";
		}
	}



	file << std::endl;

	file.close();*/

	for (boid * a_boid : m_boids)
	{
		if (isnan(a_boid->m_velocity.x))
			throw("is not a number");
	}
	
	m_quad_tree.restart(aabb(Vector2() - a_window_dimentions * 0.1, a_window_dimentions * 1.2), 4);


	bool result = false;

	for (boid* a_boid : m_boids)
	{
		if (isnan(a_boid->get_position().x))
			throw("is not a number");
		if (m_quad_tree.insert(a_boid))
			result = true;
	}

	for (boid* a_boid : m_boids)
	{
		a_boid->update(a_delta_time, a_window_dimentions, m_quad_tree);
	}
}

void flock::draw()
{
	for (boid* a_boid : m_boids)
	{
		a_boid->draw();
	}

	m_quad_tree.draw(m_renderer);
}

