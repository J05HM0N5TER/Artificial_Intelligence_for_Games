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

	// Change to "./consolas.ttf" When deploying (put the font in the same folder as the .exe
	m_font = new aie::Font("../bin/font/consolas.ttf", 20);

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
					m_graph->m_nodes[(i + 1) * width + (j - 1)], 1.414213562f);
			}
			// Up to the right '/'.
			if (j < width - 1 && i < height - 1)
			{
				m_graph->create_edge(
					m_graph->m_nodes[i * width + j],
					m_graph->m_nodes[(i + 1) * width + (j + 1)], 1.414213562f);
			}
		}
	}

	colour_active = false;

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

	// Check if they are only clicking and not holding right click.
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		was_left_mouse_pressed = true;
	}

	// Controls to toggle colour mode.
	if (input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		colour_active = !colour_active;
	}

	// Select node.
	if (input->wasMouseButtonPressed(0))
	{
		Vector2 mouse_pos(float(input->getMouseX()), float(input->getMouseY()));

		for (auto& a_node : m_graph->m_nodes)
		{
			float distance = (mouse_pos - a_node->get_data()).square_magnitude();
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
			//m_graph->calculate_path_a_star(m_selection_queue.front(), m_selection_queue.back());
		}
	}

	// Disable node.
	else if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		Vector2 mouse_pos(float(input->getMouseX()), float(input->getMouseY()));

		for (auto& a_node : m_graph->m_nodes)
		{
			float distance = (mouse_pos - a_node->get_data()).square_magnitude();
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

	// Reset key.
	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		for (auto& a_node : m_graph->m_nodes)
		{
			a_node->set_valid(true);
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

	Vector3 display_colour{};

	// Work out max_g_score for use with the colour picker.
	float max_g_score = 0;
	if (colour_active)
	{
		for (auto& a_node : m_graph->m_nodes)
		{
			max_g_score = (a_node->get_g_score() > max_g_score) ? a_node->get_g_score() : max_g_score;
		}
	}

	// Draw lines edges.
	for (auto& a_edge : m_graph->m_edges)
	{
		// Set colour of edge depending on if it is active.
		if (a_edge->is_valid)
		{
			node<Vector2>* lowest_node = (a_edge->m_nodes[0]->get_g_score() < a_edge->m_nodes[1]->get_g_score()) ? a_edge->m_nodes[0] : a_edge->m_nodes[0]; // Find the node with the lowest g_score and use that.
			// Get color.
			// If the node is the start node ...
			if (m_selection_queue.size() > 1 && lowest_node == m_selection_queue.front())
			{
				// .. use the other node to get the colour.
				lowest_node = (lowest_node == a_edge->m_nodes[0]) ? a_edge->m_nodes[1] : a_edge->m_nodes[0];
			}
			// Get the colour using the node of the lowest g_score.
			display_colour = colour_picker(lowest_node, max_g_score);

			// Display using colour.
			m_2dRenderer->setRenderColour(display_colour.r, display_colour.g, display_colour.b, 1);

		}
		else
		{
			if (colour_active)
			{
				m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.3f, 1);

			}
			else
			{
				m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);

			}
		}

		node<Vector2>* A = a_edge->m_nodes[0];
		node<Vector2>* B = a_edge->m_nodes[1];
		m_2dRenderer->drawLine(A->get_data().x, A->get_data().y, B->get_data().x, B->get_data().y, 2.0f);
	}

	// Draw the path.
	// Set colour to red.
	m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f, 1);
	for (int i = 0; i < int(m_graph->m_path.size()) - 1; ++i)
	{
		node<Vector2>* A = m_graph->m_path[i];
		node<Vector2>* B = m_graph->m_path[i + 1];

		m_2dRenderer->drawLine(A->get_data().x, A->get_data().y, B->get_data().x, B->get_data().y, 5.0f);
	}


	// Draw nodes.
	for (auto& a_node : m_graph->m_nodes)
	{
		// Set colour of node depending on if it has any active edges connected to it.
		if (a_node->is_valid())
		{
			// Get color.
			display_colour = colour_picker(a_node, max_g_score);

			// Display using colour.
			m_2dRenderer->setRenderColour(display_colour.r, display_colour.g, display_colour.b, 1);
		}
		else
		{
			if (colour_active)
			{
				m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.5f, 1);

			}
			else
			{
				m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);

			}
		}

		m_2dRenderer->drawCircle(a_node->get_data().x, a_node->get_data().y, 5.0f);
	}


	// Display selected nodes.
	// Set colour to red.
	m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f, 1);

	if (m_selection_queue.size() > 0)
	{
		m_2dRenderer->drawCircle(m_selection_queue.front()->get_data().x, m_selection_queue.front()->get_data().y, 8.0f);
	}

	if (m_selection_queue.size() > 1)
	{
		m_2dRenderer->drawCircle(m_selection_queue.back()->get_data().x, m_selection_queue.back()->get_data().y, 8.0f);
	}

#pragma region Display instructions.

	// Reset colour for text.
	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	// Calculate and draw text.
	const char escape_text[] = "Press ESC to quit";
	float escape_text_position = getWindowHeight() - m_font->getStringHeight(escape_text);

	m_2dRenderer->drawText(m_font, escape_text, 0.0f, escape_text_position);

	const char left_mouse_text[] = "Left mouse to select nodes";
	float left_mouse_text_position = escape_text_position - m_font->getStringHeight(escape_text);

	m_2dRenderer->drawText(m_font, left_mouse_text, 0.0f, left_mouse_text_position);

	const char shift_text[] = "Press and hold left shift and right mouse to deactivate nodes.";
	float shift_text_position = left_mouse_text_position - m_font->getStringHeight(left_mouse_text);

	m_2dRenderer->drawText(m_font, shift_text, 0.0f, shift_text_position);

	const char control_text[] = "Press and hold left control and right mouse to activate nodes.";
	float control_text_position = shift_text_position - m_font->getStringHeight(shift_text);

	m_2dRenderer->drawText(m_font, control_text, 0.0f, control_text_position);

	const char right_mouse_text[] = "Press right mouse to toggle node.";
	float right_mouse_text_position = control_text_position - m_font->getStringHeight(control_text);

	m_2dRenderer->drawText(m_font, right_mouse_text, 0.0f, right_mouse_text_position);

	const char colour_text[] = "Press 'c' to toggle colour display.";
	float colour_text_position = right_mouse_text_position - m_font->getStringHeight(right_mouse_text);

	m_2dRenderer->drawText(m_font, colour_text, 0.0f, colour_text_position);

#pragma endregion

	// done drawing sprites
	m_2dRenderer->end();
}

Vector3 Application2D::colour_picker(node<Vector2>* a_node, float a_mox_g_score)
{
	Vector3 output(0.0f, 0.0f, 0.0f);

	// If the display is set to have color.
	if (colour_active)
	{
		if (a_node->get_g_score() < 0.1f)
		{
			output.r = 0.5f;
			output.g = 0.5f;
			output.b = 0.5f;
		}
		else
		{
			// Calculate green value off of g score.
			output.g = 1 - (a_node->get_g_score() / (float)a_mox_g_score);

			// Calculate red value off of green value.
			output.r = 1 - output.g;
		}
	}
	// If the display is set to not have colour.
	else
	{
		output.r = 1.0f;
		output.g = 1.0f;
		output.b = 1.0f;
	}

	return output;
}