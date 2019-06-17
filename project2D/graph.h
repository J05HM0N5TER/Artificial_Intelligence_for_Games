#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "edge.h"
#include "node.h"

template<typename T>
class graph
{
public:
	graph<T>() {};
	~graph() 
	{
		for (auto& node : m_nodes)
		{
			delete node;
		}

		for (auto& edge : m_edges)
		{
			delete edge;
		}
	}

	node<T>* create_node(const T& a_data)
	{
		node<T>* new_node = new node<T>(a_data);
		m_nodes.push_back(new_node);
		return new_node;
	}


	edge<T>* create_edge(node<T>* a_node_A, node<T>* a_node_B)
	{
		edge<T>* new_edge = new edge<T>(a_node_A, a_node_B);
		m_edges.push_back(new_edge);
		return new_edge;
	}

	void remove_node(node<T>* a_node)
	{

		while (a_node->m_edges.size() > 0)
		{ 
			this->remove_edge(a_node->m_edges.at(0));
		}

		auto iter = std::find(m_nodes.begin(), m_nodes.end(), a_node);
		delete (*iter);
		m_nodes.erase(iter);
	}

	void remove_edge(edge<T>* a_edge)
	{
		a_edge[0]->remove_edge(a_edge);
		a_edge[1]->remove_edge(a_edge);
	}

//private:
	std::vector<node<T>*> m_nodes;
	std::vector<edge<T>*> m_edges;
};

#endif // !GRAPH_H
