#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "flock.h"
#include "Input.h"
#include "quad_tree.h"

class FlockingApp : public aie::Application {
public:

	FlockingApp();
	virtual ~FlockingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	bool m_draw_quad_tree;

	aie::Texture* m_bird_sprite;

	flock* m_flock;

	aie::Input* m_input;

	Vector2 m_window_dimentions;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};