#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include <vector>
#include "boid.h"

class flock
{
public:
	flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture);

	void create_boid(int a_amount, Vector2& a_spawn_position);

	void create_random_boids(int a_amount, Vector2& a_window_dimentions);

	void update(float a_delta_time, Vector2& a_window_dimentions);
	void draw();

	std::vector<boid*> m_boids;
private:

	aie::Renderer2D* m_renderer;
	aie::Texture* m_texture;
};

