#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Circle.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();


	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	m_graph = new graph<Vector2>();

	int spacing = 40;
	int width = 31;
	int height = 17;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			m_graph->create_node({ (j + 1.0f) * spacing, (i + 1.0f) * spacing });
		}
	}

	// Horizontals
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; j++)
		{
			m_graph->create_edge(
				m_graph->m_nodes[i * width + j],
				m_graph->m_nodes[i * width + (j + 1)]);
		}
	}

	// Verticals
	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			m_graph->create_edge(
				m_graph->m_nodes[i * width + j],
				m_graph->m_nodes[(i + 1) * width + j]);
		}
	}

	// Diagonal
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			if (j > 0 && i < height - 1)
			{
				m_graph->create_edge(
					m_graph->m_nodes[i * width + j],
					m_graph->m_nodes[(i + 1) * width + (j - 1)], 1.42f);
			}
			if (j < width - 1 && i < height - 1)
			{
				m_graph->create_edge(
					m_graph->m_nodes[i * width + j],
					m_graph->m_nodes[(i + 1) * width + (j + 1)], 1.42f);
			}
		}
	}

	/*auto node_A = m_graph->create_node({ 100, 100 });
	auto node_B = m_graph->create_node({ 100, 300 });
	auto node_C = m_graph->create_node({ 300, 100 });
	auto node_D = m_graph->create_node({ 300, 300 });

	m_graph->create_edge(node_A, node_B);
	m_graph->create_edge(node_B, node_D);
	m_graph->create_edge(node_D, node_C);
	m_graph->create_edge(node_C, node_A);*/

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	

	// Terrible order N lookup.
	float shortes_distance = FLT_MAX;
	node<Vector2>* closest_node;

	if (input->wasMouseButtonPressed(0))
	{
		Vector2 mouse_pos(float(input->getMouseX()), float(input->getMouseY()));

		for (auto& a_node : m_graph->m_nodes)
		{
			float distance = (mouse_pos - a_node->m_data).square_magnitude();
			if (distance < shortes_distance)
			{
				shortes_distance = distance;
				closest_node = a_node;
			}
		}
		m_selection_queue.push(closest_node);
		if (m_selection_queue.size() > 2)
		{
			m_selection_queue.pop();
		}

		if (m_selection_queue.size() == 2)
		{
			m_graph->calculate_path_dijkstra(m_selection_queue.front(), m_selection_queue.back());
		}
	}


	
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		Vector2 mouse_pos(float(input->getMouseX()), float(input->getMouseY()));

		for (auto& a_node : m_graph->m_nodes)
		{
			float distance = (mouse_pos - a_node->m_data).square_magnitude();
			if (distance < shortes_distance)
			{
				shortes_distance = distance;
				closest_node = a_node;
			}
		}
		
		closest_node->set_valid(!closest_node->is_valid());
	}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// Draw lines edges.
	for (auto& a_edge : m_graph->m_edges)
	{
		if (a_edge->is_valid)
		{
			m_2dRenderer->setRenderColour(1, 1, 1, 1);
		}
		else
		{
			m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);
			//continue;

		}
			node<Vector2>* A = a_edge->m_nodes[0];
			node<Vector2>* B = a_edge->m_nodes[1];
			m_2dRenderer->drawLine(A->m_data.x, A->m_data.y, B->m_data.x, B->m_data.y, 2.0f);
		
	}

	// Edges?!
	for (int i = 0; i < int(m_graph->m_path.size()) - 1; ++i)
	{
		m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f, 1);

		node<Vector2>* A = m_graph->m_path[i];
		node<Vector2>* B = m_graph->m_path[i + 1];
		m_2dRenderer->drawLine(A->m_data.x, A->m_data.y, B->m_data.x, B->m_data.y, 5.0f);

	}

	// Draw nodes.
	for (auto& a_nodes : m_graph->m_nodes)
	{
		if (a_nodes->is_valid())
		{
			m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1);
		}
		else
		{
			m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);
		}

		m_2dRenderer->drawCircle(a_nodes->m_data.x, a_nodes->m_data.y, 5.0f);
	}


	m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f, 1);

	// Display selected nodes.
	if (m_selection_queue.size() > 0)
	{
		m_2dRenderer->drawCircle(m_selection_queue.front()->m_data.x, m_selection_queue.front()->m_data.y, 8.0f);
	}

	if (m_selection_queue.size() > 1)
	{
		m_2dRenderer->drawCircle(m_selection_queue.back()->m_data.x, m_selection_queue.back()->m_data.y, 8.0f);
	}




	// done drawing sprites
	m_2dRenderer->end();
}