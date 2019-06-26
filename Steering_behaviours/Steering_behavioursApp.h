#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "player.h"
#include "flock.h"

class Steering_behavioursApp : public aie::Application 
{
public:

	Steering_behavioursApp();
	virtual ~Steering_behavioursApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Texture* m_bird_sprite;

	flock* m_flock;

	player* m_player;

	aie::Input* m_input;

	Vector2 m_window_dimentions;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};