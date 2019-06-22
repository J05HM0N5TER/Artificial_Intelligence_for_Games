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

	colour_display = true;
	using_dijkstra = true;

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
		colour_display = !colour_display;
	}

	// Controls to toggle algorithm.
	if (input->wasKeyPressed(aie::INPUT_KEY_A))
	{
		using_dijkstra = !using_dijkstra;
	}

	// Select node.
	if (input->wasMouseButtonPressed(0))
	{
		Vector2 mouse_pos(float(input->getMouseX()), float(input->getMouseY()));

		// Loop though each node and compare distance to find closest node.
		for (auto& a_node : m_graph->m_nodes)
		{
			float distance = (mouse_pos - a_node->get_data()).square_magnitude();
			if (distance < shortes_distance)
			{
				shortes_distance = distance;
				closest_node = a_node;
			}
		}
		// Add note to the selection queue.
		m_selection_queue.push(closest_node);

		// If there is already two nodes selected ...
		if (m_selection_queue.size() > 2)
		{
			// ... remove the oldest one
			m_selection_queue.pop();
		}

		// If there is two nodes selected ...
		if (m_selection_queue.size() == 2)
		{
			// ... apply correct algorithm to find the path.
			if (using_dijkstra)
			{
				m_graph->calculate_path_dijkstra(m_selection_queue.front(), m_selection_queue.back());
			}
			else
			{
				m_graph->calculate_path_a_star(m_selection_queue.front(), m_selection_queue.back());
			}
		}
	}

	// Disable node.
	else if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		// Loop though each node and compare distance to find closest node.
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

		// If the user is holding shift ...
		if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
		{
			// ... disable every node they have there mouse close to.
			closest_node->set_valid(false);
		}
		// If the user is holding control ...
		else if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
		{
			// ... enable every node they have there mouse close to.
			closest_node->set_valid(true);
		}
		// If the user just clicked ...
		else if (was_left_mouse_pressed)
		{
			// ... toggle the node they are closest to.
			closest_node->toggle_valid();
		}
	}

	// Reset key.
	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		// Reset all nodes.
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

	// Work out max_f_score for use with the colour picker.
	float max_f_score = 0;
	if (colour_display)
	{
		// Loop though all nodes ...
		for (auto& a_node : m_graph->m_nodes)
		{
			// ... and compare to find the largest g_score.
			max_f_score = (a_node->get_f_score() > max_f_score) ? a_node->get_f_score() : max_f_score;
		}
	}

	// Draw lines edges.
	for (auto& a_edge : m_graph->m_edges)
	{
		// Set colour of edge depending on if it is active.
		if (a_edge->is_valid)
		{
			node<Vector2>* lowest_node = (a_edge->m_nodes[0]->get_g_score() < a_edge->m_nodes[1]->get_g_score()) ? a_edge->m_nodes[0] : a_edge->m_nodes[0]; // Find the node with the lowest g_score and use that.
			// Get colour.
			// If the node is the start node ...
			if (m_selection_queue.size() > 1 && lowest_node == m_selection_queue.front())
			{
				// .. use the other node to get the colour.
				lowest_node = (lowest_node == a_edge->m_nodes[0]) ? a_edge->m_nodes[1] : a_edge->m_nodes[0];
			}
			// Get the colour using the node of the lowest g_score.
			display_colour = colour_picker(lowest_node, max_f_score);

			// Display using colour.
			m_2dRenderer->setRenderColour(display_colour.r, display_colour.g, display_colour.b, 1);

		}
		else
		{
			if (colour_display)
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
		m_2dRenderer->drawLine(A->get_data().x, A->get_data().y, B->get_data().x, B->get_data().y, 2.0f/*Line width*/);
	}



	// Draw nodes.
	for (auto& a_node : m_graph->m_nodes)
	{
		// Set colour of node depending on if it has any active edges connected to it.
		if (a_node->is_valid())
		{
			// Get colour.
			display_colour = colour_picker(a_node, max_f_score);

			// Display using colour.
			m_2dRenderer->setRenderColour(display_colour.r, display_colour.g, display_colour.b, 1);
		}
		else
		{
			if (colour_display)
			{
				m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.5f, 1);

			}
			else
			{
				m_2dRenderer->setRenderColour(0.3f, 0.3f, 0.3f, 1);

			}
		}

		m_2dRenderer->drawCircle(a_node->get_data().x, a_node->get_data().y, 5.0f/*Circle diameter*/);
	}

	// Draw the path.
	// Set colour to red.
	m_2dRenderer->setRenderColour(0.0f, 0.0f, 1.0f, 1);
	for (int i = 0; i < int(m_graph->m_path.size()) - 1; ++i)
	{
		node<Vector2>* A = m_graph->m_path[i];
		node<Vector2>* B = m_graph->m_path[i + 1];

		m_2dRenderer->drawLine(A->get_data().x, A->get_data().y, B->get_data().x, B->get_data().y, 5.0f/*Line width*/);
	}

	// Display selected nodes.
	if (m_selection_queue.size() > 0)
	{
		m_2dRenderer->drawCircle(m_selection_queue.front()->get_data().x, m_selection_queue.front()->get_data().y, 8.0f/*Circle diameter*/);
	}

	if (m_selection_queue.size() > 1)
	{
		m_2dRenderer->drawCircle(m_selection_queue.back()->get_data().x, m_selection_queue.back()->get_data().y, 8.0f/*Circle diameter*/);
	}

#pragma region Display instructions.

	// Initialise text (only done once)
	static const char escape_text[] = "Press [ESC] to quit";
	static const char left_mouse_text[] = "Left mouse to select nodes";
	static const char shift_text[] = "Press and hold left shift and right mouse to deactivate nodes.";
	static const char control_text[] = "Press and hold left control and right mouse to activate nodes.";
	static const char right_mouse_text[] = "Press right mouse to toggle node.";
	static const char colour_text[] = "Press [C] to toggle colour display.";
	static const char algorithm_text[] = "Press [A] to switch algorithm.";

	// Calculate displacement of text off of the screen height to be used later (only done once).
	static float escape_text_displacement;
	static float left_mouse_text_displacement;
	static float shift_text_displacement;
	static float control_text_displacement;
	static float right_mouse_text_displacement;
	static float colour_text_displacement;
	static float algorithm_text_displacement;

	static bool initialised = false;
	if (!initialised)
	{
		escape_text_displacement = m_font->getStringHeight(escape_text);
		left_mouse_text_displacement = escape_text_displacement + m_font->getStringHeight(escape_text);
		shift_text_displacement = left_mouse_text_displacement + m_font->getStringHeight(left_mouse_text);
		control_text_displacement = shift_text_displacement + m_font->getStringHeight(shift_text);
		right_mouse_text_displacement = control_text_displacement + m_font->getStringHeight(control_text);
		colour_text_displacement = right_mouse_text_displacement + m_font->getStringHeight(right_mouse_text);
		algorithm_text_displacement = colour_text_displacement + m_font->getStringHeight(algorithm_text);
		initialised = true;
	}


	// Reset colour for text.
	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	// Calculate and draw text off of displacement and window height.

	const float window_height = float(getWindowHeight());

	const float escape_text_position = window_height - escape_text_displacement;
	m_2dRenderer->drawText(m_font, escape_text, 0.0f, escape_text_position);

	const float left_mouse_text_position = window_height - left_mouse_text_displacement;
	m_2dRenderer->drawText(m_font, left_mouse_text, 0.0f, left_mouse_text_position);

	const float shift_text_position = window_height - shift_text_displacement;
	m_2dRenderer->drawText(m_font, shift_text, 0.0f, shift_text_position);

	const float control_text_position = window_height - control_text_displacement;
	m_2dRenderer->drawText(m_font, control_text, 0.0f, control_text_position);

	const float right_mouse_text_position = window_height - right_mouse_text_displacement;
	m_2dRenderer->drawText(m_font, right_mouse_text, 0.0f, right_mouse_text_position);

	const float colour_text_position = window_height - colour_text_displacement;
	m_2dRenderer->drawText(m_font, colour_text, 0.0f, colour_text_position);

	const float algorithm_text_position = window_height - algorithm_text_displacement;
	m_2dRenderer->drawText(m_font, algorithm_text, 0.0f, algorithm_text_position);

#pragma endregion

	// done drawing sprites
	m_2dRenderer->end();
}

Vector3 Application2D::colour_picker(node<Vector2>* a_node, float a_mox_f_score)
{
	Vector3 output(0.0f, 0.0f, 0.0f);

	// If the display is set to have colour.
	if (colour_display)
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
			output.g = 1 - (a_node->get_f_score() / (float)a_mox_f_score);

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