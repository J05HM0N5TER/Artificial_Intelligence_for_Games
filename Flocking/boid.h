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

	void update(float a_delta_time, const Vector2& a_window_dimentions, 
		const quad_tree & a_quad_tree);
	void draw();

	void apply_force(Vector2& a_force);

	const Vector2 & get_position() const;
	void set_position(const Vector2 & a_position);

	const float get_radus() const;

	// The current position of the boid.
	Vector2 m_position;
	// The current velocity -The speed is constant so this only is used for direction-.
	Vector2 m_velocity;

	float m_sprite_timer = 0.0f;

	// Pointer to the parent flock.
	flock* m_flock;

private:
	char m_current_sprite = 0;
};

