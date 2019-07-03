#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include <vector>
#include "boid.h"
#include "quad_tree.h"

class flock
{
public:
	flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture);
	~flock();


	void create_boid(int a_amount, Vector2& a_spawn_position);

	void create_random_boids(int a_amount, Vector2& a_window_dimentions);

	void update(float a_delta_time, Vector2& a_window_dimentions);
	void draw();

	std::vector<boid*> m_boids;


	float SPRITE_COUNT = 4.0f;
	float SPRITE_ANIMATION_DELAY = 0.5f;
	float NEIGHBOUR_RADUS = 25.0f;
	float BOID_SPEED = 100.0f;
	float SEPERATION_FORCE_MAG = 20.0f;
	float COHESION_FOECE_MAG = 20.0f;
	float CIECLE_FORCE_MULT = 10.0f;
	float ALIGHMENT_FORCE_MULT = 7.0f;
private:

	quad_tree m_quad_tree;

	aie::Renderer2D* m_renderer;
	aie::Texture* m_texture;

};

