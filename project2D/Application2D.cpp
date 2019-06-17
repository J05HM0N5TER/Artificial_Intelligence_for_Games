#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Circle.h"

Application2D::Application2D()
{

}

Application2D::~Application2D()
{

}

bool Application2D::startup()
{

	m_2dRenderer = new aie::Renderer2D();


	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_timer = 0;

	m_graph = new graph<Vector2>();

	int spacing = 40;
	int width = 31;
	int height = 17;

	// Create nodes.
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			m_graph->create_node({ (j + 1.0f) * spacing, (i + 1.0f) * spacing });
		}
	}

	// Connect horizontally
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; j++)
		{
			m_graph->create_edge(
				m_graph->m_nodes[i * width + j],
				m_graph->m_nodes[i * width + (j + 1)]);
		}
	}

	// Connect vertically
	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			m_graph->create_edge(
				m_graph->m_nodes[i * width + j],
				m_graph->m_nodes[(i + 1) * width + j]);
		}
	}

	// Connect diagonally
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			// Down to the right '\'.
			if (j > 0 && i < height - 1)
			{
				m_graph->create_edge(
					m_graph->m_nodes[i * width + j],
					m_graph->m_nodes[(i + 1) * width + (j - 1)], 1.42f);
			}
			// Up to the right '/'.
			if (j < width - 1 && i < height - 1)
			{
				m_graph->create_edge(
					m_graph->m_nodes[i * width + j],
					m_graph->m_nodes[(i + 1) * width + (j + 1)], 1.42f);
			}
		}
	}

	return true;
}

void Application2D::shutdown()
{

	delete m_font;
	delete m_2dRenderer;
	delete m_graph;
}

void Application2D::update(float deltaTime)
{

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();
	bool was_left_mouse_pressed = false;

	// Terrible order N lookup.
	float shortes_distance = FLT_MAX;
	node<Vector2>* closest_node;

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		was_left_mouse_pressed = true;
	}

	// Select node.
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

	// Disable node.
	else if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
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

		if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
		{
			closest_node->set_valid(false);
		}
		else if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
		{
			closest_node->set_valid(true);
		}
		else if (was_left_mouse_pressed)
		{
			closest_node->toggle_valid();
		}
	}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// Draw lines edges.
	for (auto& a_edge : m_graph->m_edges)
	{
		// Set colour of edge depending on if it is active.
		if (a_edge->is_valid)
		{
			// Black if valid.
			m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1);
		}
		else
		{
			// Gray if not.
			m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);
		}
		node<Vector2>* A = a_edge->m_nodes[0];
		node<Vector2>* B = a_edge->m_nodes[1];
		m_2dRenderer->drawLine(A->m_data.x, A->m_data.y, B->m_data.x, B->m_data.y, 2.0f);

	}

	// Draw the path.
	for (int i = 0; i < int(m_graph->m_path.size()) - 1; ++i)
	{
		// Set colour to red.
		m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f, 1);

		node<Vector2>* A = m_graph->m_path[i];
		node<Vector2>* B = m_graph->m_path[i + 1];
		m_2dRenderer->drawLine(A->m_data.x, A->m_data.y, B->m_data.x, B->m_data.y, 5.0f);

	}

	// Draw nodes.
	for (auto& a_nodes : m_graph->m_nodes)
	{
		// Set colour of node depending on if it has any active edges connected to it.
		if (a_nodes->is_valid())
		{
			// Black if valid.
			m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1);
		}
		else
		{
			// Gray if not.
			m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);
		}

		m_2dRenderer->drawCircle(a_nodes->m_data.x, a_nodes->m_data.y, 5.0f);
	}

	// Reset colour.
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

	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	// Calculate and draw text.
	const char escape_text[] = "Press ESC to quit";
	int escape_text_position = getWindowHeight() - m_font->getStringHeight(escape_text);

	m_2dRenderer->drawText(m_font, escape_text, 0.0f, escape_text_position);

	const char left_mouse_text[] = "Left mouse to select nodes";
	int left_mouse_text_position = escape_text_position - m_font->getStringHeight(escape_text);

	m_2dRenderer->drawText(m_font, left_mouse_text, 0.0f, left_mouse_text_position);

	const char shift_text[] = "Press and hold left shift and right mouse to deactivate nodes.";
	int shift_text_position = left_mouse_text_position - m_font->getStringHeight(left_mouse_text);

	m_2dRenderer->drawText(m_font, shift_text, 0.0f, shift_text_position);
	
	const char control_text[] = "Press and hold left control and right mouse to activate nodes.";
	int control_text_position = shift_text_position - m_font->getStringHeight(shift_text);

	m_2dRenderer->drawText(m_font, control_text, 0.0f, control_text_position);
	
	const char right_mouse_text[] = "Press right mouse to toggle node.";
	int right_mouse_text_position = control_text_position - m_font->getStringHeight(control_text);

	m_2dRenderer->drawText(m_font, right_mouse_text, 0.0f, right_mouse_text_position);



	// done drawing sprites
	m_2dRenderer->end();
}