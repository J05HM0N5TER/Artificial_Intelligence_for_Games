#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "edge.h"
#include "node.h"
#include <list>

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


	edge<T>* create_edge(node<T>* a_node_A, node<T>* a_node_B, float a_weight = 1.0f)
	{
		edge<T>* new_edge = new edge<T>(a_node_A, a_node_B, a_weight);
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


	std::vector<node<T>*>& calculate_path_dijkstra(node<T>* a_start, node<T>* a_end)
	{
		for (auto& a_node : m_nodes)
		{
			a_node->reset();
		}
		m_path.clear();


		if (!a_start || !a_end)
		{
			return m_path;
		}

		if (a_start == a_end)
		{
			m_path.push_back(a_start);
			return m_path;
		}

		std::list<node<T>*> open_list;
		std::list<node<T>*> closed_list;

		open_list.push_back(a_start);

		node<T>* current_node;
		while (open_list.size())
		{

			current_node = open_list.front();
			open_list.pop_front();

			closed_list.push_back(current_node);

			for (auto& a_edge : current_node->m_edges)
			{
				if (!a_edge->is_valid)
				{
					continue;
				}

				node<T>* other_node = nullptr;
				if (a_edge->m_nodes[0] == current_node)
				{
					other_node = a_edge->m_nodes[1];
				}
				else
				{
					other_node = a_edge->m_nodes[0];
				}


				// If the other_node is not in the closed list.
				//if (closed_list.find(other_node) == closed_list.last())

				if (std::find(std::begin(closed_list), std::end(closed_list), other_node) == closed_list.end())
				{
					int current_g_score = current_node->m_g_score + a_edge->m_weight;

					// If the other_nodes is not in the open_list
					if (std::find(std::begin(open_list), std::end(open_list), other_node) == open_list.end())
					{
						// Set the current_g_score for the other_node.
						other_node->m_g_score = current_node->m_g_score + a_edge->m_weight;

						other_node->m_previous = current_node;

						// Add the other_node to the open_list.
						open_list.push_back(other_node);
					}

					// If the other_node is in the closed list but the new current_g_score is better then the one set already.
					else if (current_g_score < other_node->m_g_score)
					{
						// Overwrite the current_g_score.
						other_node->m_g_score = current_g_score;
						// and overwrite the previous.
						other_node->m_previous = current_node;
					}
				}
			}
		}

		node<T>* end_node = a_end;
		m_path.push_back(end_node);
		while (end_node != a_start)
		{
			end_node = end_node->m_previous;
			m_path.push_back(end_node);
		}
		return m_path;
	}

	//private:
	std::vector<node<T>*> m_path;

	std::vector<node<T>*> m_nodes;
	std::vector<edge<T>*> m_edges;
};

#endif // !GRAPH_H
