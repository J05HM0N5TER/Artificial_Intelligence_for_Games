#pragma once
#include "Vector2.h"
#include "Renderer2D.h"

class flock;

class boid
{
public:
	boid(aie::Renderer2D* a_renderer, aie::Texture* a_texture, Vector2& a_spawn_position, flock* a_flock);

	void set_flock(flock* a_flock);

	void update(float a_delta_time, Vector2& a_window_dimentions);
	void draw();

	void apply_force(Vector2& a_force);

	Vector2 m_position;
	Vector2 m_velocity;
private:
	Vector2 m_draw_size;
	aie::Renderer2D* m_renderer;
	aie::Texture* m_texture;


	flock* m_parent_flock;

	float m_sprite_timer = 0.0f;
	int m_current_sprite = 0;
	
	static const float SPRITE_COUNT;

	static const float NEIGHBOUR_RADUS;
	static const float BOID_SPEED;
	static const float SEPERATION_FORCE_MAG;
	static const float COHESION_FOECE_MAG;
	static const float CIECLE_FORCE_MULT;
	static const float ALIGHMENT_FORCE_MULT;
};

