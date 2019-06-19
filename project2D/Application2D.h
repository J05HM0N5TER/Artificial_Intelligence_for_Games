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

	/*!	\brief Selector for colour based on g_score.
		\param a_node The node that you are sending in to find the colour for.
		\param a_max_score The maximum g_score across every node.
		\return A Vector3 with the values for red, green and blue stored in it.
	*/
	Vector3 colour_picker(node<Vector2>* a_node, int a_mox_g_score);

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	// A queue that holds all the nodes that the user has selected.
	std::queue<node<Vector2>*> m_selection_queue;

	// True if the user has selected to display in colour.
	bool colour_active;

	// The graph that holds all the nodes and edges.
	graph<Vector2>* m_graph;

	float m_timer;
};