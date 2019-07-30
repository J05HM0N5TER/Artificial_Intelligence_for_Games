#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "flock.h"
#include "Input.h"
#include "quad_tree.h"

enum class GAME_STATE
{
	// Selecting the amount of boids menu.
	START,
	// When the boids are already spawned.
	ACTIVE
};

class FlockingApp : public aie::Application {
public:

	FlockingApp();
	virtual ~FlockingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void active_update(float deltaTime);
	void active_draw();

	void start_update(float deltaTime);
	void start_draw();


protected:

	// The selection for the amount of boids that the user wants.
	std::vector<char> m_user_number;

	// The current game state.
	GAME_STATE current_state;

	// True if the user wants to draw the quad tree -set to false by default-.
	bool m_draw_quad_tree;
	bool m_use_circle_boundry;

	// The texture that is used for the boids.
	aie::Texture* m_bird_sprite;

	// The flock that holds all of the boids.
	flock* m_flock;

	// Needed default bootstrap components.
	aie::Input* m_input;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};