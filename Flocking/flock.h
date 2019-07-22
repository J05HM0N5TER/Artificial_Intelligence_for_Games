#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include <vector>
#include "boid.h"
#include "quad_tree.h"
#include "Input.h"

class flock
{
public:

	flock() = delete;

	/*!	\brief The default constructor for the flock.
		\param a_renderer A pointer to the renderer for the window.
		\param a_texture A pointer to the texture that the boids are being drawn as.
	*/
	flock(aie::Renderer2D* a_renderer, aie::Texture* a_texture, aie::Input* a_input);
	~flock();

	/*!	\brief Creates boids at specified position.
		\param a_amount The amount of boids that you want to spawn at that position
		\param a_spawn_position The position that you want the boids to spawn at.
	*/
	void create_boid(int a_amount, Vector2& a_spawn_position);

	/*!	\brief Creates a boid at a random position within the screen dimensions.
		\param a_amount The amount of boids that you want to spawn.
		\param The dimensions that the boids can spawn in.
	*/
	void create_random_boids(const size_t & a_amount, const Vector2 & a_window_dimentions);

	//	\brief Updates the position for the boids to be drawn at.
	void update(float a_delta_time, Vector2& a_window_dimentions);

	/*	\brief Draws the boids on screen.
		\param a_draw_quad_tree True if the quad tree is being drawn
	*/
	void draw(bool a_draw_quad_tree);

	// The vector that holds all the boids in the flock.
	std::vector<boid*> m_boids;

	/* ---Global variables for the flock--- */

	float SPRITE_COUNT = 4.0f;
	float SPRITE_ANIMATION_DELAY = 0.5f;
	float NEIGHBOUR_RADUS = 25.0f;
	float BOID_SPEED = 100.0f;
	float SEPERATION_FORCE_MAG = 20.0f;
	float COHESION_FOECE_MAG = 20.0f;
	float CIECLE_FORCE_MULT = 10.0f;
	float ALIGHMENT_FORCE_MULT = 7.0f;
	short QUAD_TREE_CAPACITY = 10;
	float ATTRACT_MULT = 20.0f;

	Vector2 m_draw_size = { 10.0f * 1, 5.0f * 1 };

//private:

	aie::Input* m_input;

	// The quad tree that holds all of the boid*.
	quad_tree m_quad_tree;

	// A pointer to the renderer.
	aie::Renderer2D* m_renderer;
	// A pointer to the texture that the boids are being drawn at.
	aie::Texture* m_texture;

};

