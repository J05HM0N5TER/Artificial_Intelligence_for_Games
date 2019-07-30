#pragma once
#include "Vector2.h"
#include "Renderer2D.h"
#include "quad_tree.h"

class flock;

class boid
{
public:
	boid(Vector2& a_spawn_position, flock* a_flock);

	// \brief Sets the parent flock for the boid.
	void set_flock(flock* a_flock);

	/*!	\brief Updates the position of the boid.
		\param a_delta_time The time that has passed since last frame.
		\param a_window_dimensions The size of the window.
		\param a_quad_tree The quad tree that the boid is stored in.
		\param circle_boundry If the boid is using a circle boundary.
	*/
	void update(float a_delta_time, const Vector2& a_window_dimensions, 
		const quad_tree & a_quad_tree, bool a_circle_boundry = true);

	// \brief Draws the boid on screen.
	void draw();

	// \brief Applies a change to the m_velocity vector.
	void apply_force(Vector2& a_force);

	// -- Getters and setters --
	const Vector2 & get_position() const;
	void set_position(const Vector2 & a_position);

	const float get_radus() const;

	// -- Variables --

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

