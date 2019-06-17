#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "graph.h"
#include "Vector2.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	graph<Vector2>* m_graph;

	float m_timer;
};