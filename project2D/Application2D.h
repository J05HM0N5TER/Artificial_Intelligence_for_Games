#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "graph.h"
#include "Vector2.h"
#include <queue>
#include "Vector3.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Vector3 colour_picker(node<Vector2>* a_node, int a_mox_g_score);

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	std::queue<node<Vector2>*> m_selection_queue;

	bool colour_active;

	graph<Vector2>* m_graph;

	float m_timer;
};