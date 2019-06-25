#pragma once
#ifndef EDGE_H
#define EDGE_H

#include <vector>

template<typename T>
class node;

template<typename T>
class edge
{
public:
	edge(node<T>* a_node_A, node<T>* a_node_B, float a_weight = 1.0f) : 
		m_weight(a_weight), is_valid(true)
	{
		// Set the nodes.
		m_nodes[0] = a_node_A;
		m_nodes[1] = a_node_B;

		// Tell the nodes that they are connected to this edge.
		m_nodes[0]->add_edge(this);
		m_nodes[1]->add_edge(this);
	}

	~edge() {};

//private:

	// The nodes that are connected by the edge.
	node<T>* m_nodes[2];
	// How much it 'costs' to traverse the edge.
	float m_weight;
	// If the edge can be traversed.
	bool is_valid;
};

#endif // !EDGE_H
