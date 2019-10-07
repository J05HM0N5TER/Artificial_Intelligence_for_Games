#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Agent.h"

class Steering_behavioursApp : public aie::Application {
public:

	Steering_behavioursApp();
	virtual ~Steering_behavioursApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Agent* m_agent;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture* m_ship_texture;
};