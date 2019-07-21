#pragma once
#include "Vector2.h"
#include "Renderer2D.h"
#include "quad_tree.h"

class flock;

class boid
{
public:
	boid(Vector2& a_spawn_position, flock* a_flock);

	void set_flock(flock* a_flock);

	void update(float a_delta_time, const Vector2& a_window_dimentions, const quad_tree & a_quad_tree);
	void draw();

	void apply_force(Vector2& a_force);

	const Vector2 & get_position() const;
	void set_position(const Vector2 & a_position);

	const float get_radus() const;

	Vector2 m_position;
	Vector2 m_velocity;

	float m_sprite_timer = 0.0f;
private:

	flock* m_parent_flock;

	char m_current_sprite = 0;
};

