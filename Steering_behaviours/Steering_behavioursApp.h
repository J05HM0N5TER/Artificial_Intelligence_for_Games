#pragma once

#include "Application.h"
#include "Renderer2D.h"

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

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};