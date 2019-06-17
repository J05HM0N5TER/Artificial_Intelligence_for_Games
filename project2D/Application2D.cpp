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

	auto node_A = m_graph->create_node({ 100, 100 });
	auto node_B = m_graph->create_node({ 100, 300 });
	auto node_C = m_graph->create_node({ 300, 100 });
	auto node_D = m_graph->create_node({ 300, 300 });

	m_graph->create_edge(node_A, node_B);
	m_graph->create_edge(node_B, node_D);
	m_graph->create_edge(node_D, node_C);
	m_graph->create_edge(node_C, node_A);

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


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	for (auto& a_edge : m_graph->m_edges)
	{
		node<Vector2>* A = a_edge->m_nodes[0];
		node<Vector2>* B = a_edge->m_nodes[1];
		m_2dRenderer->drawLine(A->m_data.x, A->m_data.y, B->m_data.x, B->m_data.y, 2.0f);
	}

	for (auto& a_nodes : m_graph->m_nodes)
	{
		m_2dRenderer->drawCircle(a_nodes->m_data.x, a_nodes->m_data.y, 10.0f);
	}

	// done drawing sprites
	m_2dRenderer->end();
}