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
	edge(node<T>* a_node_A, node<T>* a_node_B)
	{
		m_nodes[0] = a_node_A;
		m_nodes[1] = a_node_B;

		m_nodes[0]->add_edge(this);
		m_nodes[1]->add_edge(this);
	}

	~edge() {};

//private:
	node<T>* m_nodes[2];
};

#endif // !EDGE_H
