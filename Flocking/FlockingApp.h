#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "flock.h"
#include "Input.h"
#include "quad_tree.h"

enum class GAME_STATE
{
	START,
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

	std::vector<char> m_user_number;

	GAME_STATE current_state;

	bool m_draw_quad_tree;

	aie::Texture* m_bird_sprite;

	flock* m_flock;

	aie::Input* m_input;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};