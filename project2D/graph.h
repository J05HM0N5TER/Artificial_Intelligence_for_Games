#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "edge.h"
#include "node.h"
#include <list>
#include "a_star_heap.h"

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

	/*!	\brief Creates a new node
		\param a_data The data that is being stored int the node.
		\return The pointer to the new node.
	*/
	node<T>* create_node(const T& a_data)
	{
		node<T>* new_node = new node<T>(a_data);
		m_nodes.push_back(new_node);
		return new_node;
	}

	/*!	\brief Creates a new edge to connect two nodes.
		\param a_node_A The first node that is being connected.
		\param a_node_B The second node that is being connected.
		\param a_weight The 'cost' that it takes to traverse the edge in path-finding.
		\return The pointer to the new edge.
	*/
	edge<T>* create_edge(node<T>* a_node_A, node<T>* a_node_B, float a_weight = 1.0f)
	{
		edge<T>* new_edge = new edge<T>(a_node_A, a_node_B, a_weight);
		m_edges.push_back(new_edge);
		return new_edge;
	}

	/*!	\brief Removes a specified node from the graph.
		\param The pointer to the node that is being removed.
	*/
	void remove_node(node<T>* a_node)
	{

		while (a_node->get_edges().size() > 0)
		{
			this->remove_edge(a_node->get_edges().at(0));
		}

		auto iter = std::find(m_nodes.begin(), m_nodes.end(), a_node);
		delete (*iter);
		m_nodes.erase(iter);
	}

	/*!	\brief Removes a specified edge from the graph.
		\param a_edge The pointer to the edge that is bing removed.
	*/
	void remove_edge(edge<T>* a_edge)
	{
		a_edge[0]->remove_edge(a_edge);
		a_edge[1]->remove_edge(a_edge);
	}

	/*!	\brief Calculated a path between two nodes in the graph using Dijkstra algorithm.
		\param a_start The pointer to the start point that the path is being calculated from.
		\param a_end The pointer to the end point that the path is being calculated to.
		\return A reference the locally stored path that was calculated.
	*/
	std::vector<node<T>*>& calculate_path_dijkstra(node<T>* a_start, node<T>* a_end)
	{
		// Reset all values to default so that they don't interfere.
		for (auto& a_node : m_nodes)
		{
			a_node->reset();
		}

		// Wipe any previous data in path.
		m_path.clear();


		// If any of the pointers point to NULL
		if (!a_start || !a_end)
		{
			return m_path;
		}

		// If the start and the end are the same position.
		if (a_start == a_end)
		{
			m_path.push_back(a_start);
			return m_path;
		}

		// Create the lists used to keep track of the nodes when traversing graph.
		// Open list is the nodes that have yet to be checked.
		std::list<node<T>*> open_list;
		// Closed list is nodes that have been checked already.
		std::list<node<T>*> closed_list;

		// Add the start node to the open list to start path-finding.
		open_list.push_back(a_start);

		node<T>* current_node;
		while (open_list.size())
		{
			// Set up the lists.
			current_node = open_list.front();
			open_list.pop_front();

			// Add the current node to the closed list due it being checked now.
			closed_list.push_back(current_node);

			for (auto& a_edge : current_node->get_edges())
			{
				// Skip this edge if it is disabled.
				if (!a_edge->is_valid)
				{
					continue;
				}

				// Set up what end of the edge is being tested.
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
					float current_g_score = current_node->get_g_score() + a_edge->m_weight;

					// If the other_nodes is not in the open_heap
					if (std::find(std::begin(open_list), std::end(open_list), other_node) == open_list.end())
					{
						// Set the current_g_score for the other_node.
						other_node->set_g_score(current_node->get_g_score() + a_edge->m_weight);

						other_node->set_previous(current_node);

						// Add the other_node to the open_heap.
						open_list.push_back(other_node);
					}

					// If the other_node is in the closed list but the new current_g_score is better then the one set already.
					else if (current_g_score < other_node->get_g_score())
					{
						// Overwrite the current_g_score.
						other_node->set_g_score(current_g_score);
						// and overwrite the previous.
						other_node->set_previous(current_node);
					}
				}
			}
		}

		// Will get here if there is no more paths to check.
		node<T>* end_node = a_end;
		m_path.push_back(end_node);

		// Backtrack the best path.
		while (end_node != a_start)
		{
			// If there is no valid path.
			if (!end_node)
			{
				m_path.clear();
				return m_path;
			}

			end_node = end_node->get_previous();
			m_path.push_back(end_node);
		}
		// Return the found path.
		return m_path;
	}

	/*!	\brief Calculated a path between two nodes in the graph using Dijkstra algorithm.
		\param a_start The pointer to the start point that the path is being calculated from.
		\param a_end The pointer to the end point that the path is being calculated to.
		\return A reference the locally stored path that was calculated.
	*/
	std::vector<node<T>*>& calculate_path_a_star(node<T>* a_start, node<T>* a_end)
	{
		// Reset all values to default so that they don't interfere.
		for (auto& a_node : m_nodes)
		{
			a_node->reset();
		}

		// Wipe any previous data in path.
		m_path.clear();


		// If any of the pointers point to NULL
		if (!a_start || !a_end)
		{
			return m_path;
		}

		// If the start and the end are the same position.
		if (a_start == a_end)
		{
			m_path.push_back(a_start);
			return m_path;
		}

		// Create the lists used to keep track of the nodes when traversing graph.
		// Open list is the nodes that have yet to be checked.
		a_star_heap open_heap;
		// Closed list is nodes that have been checked already.
		std::list<node<T>*> closed_list;

		// Add the start node to the open list to start path-finding.
		open_heap.add(a_start);

		node<T>* current_node;
		while (open_heap.size() != 0)
		{
			// Set up the lists.
			current_node = open_heap.pop();
			//open_heap.pop();

			// Add the current node to the closed list due it being checked now.
			closed_list.push_back(current_node);

			for (auto& a_edge : current_node->get_edges())
			{
				// Skip this edge if it is disabled.
				if (!a_edge->is_valid)
				{
					continue;
				}

				// Set up what end of the edge is being tested.
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

				//if (std::find(std::begin(closed_list), std::end(closed_list), other_node) == closed_list.end())
				if (open_heap.find(other_node) == -1)
				{
					float current_g_score = current_node->get_g_score() + a_edge->m_weight;

					// If the other_nodes is not in the open_heap
					if (open_heap.find(other_node) == -1)
					{
						// Set the current_g_score for the other_node.
						other_node->set_g_score(current_node->get_g_score() + a_edge->m_weight);

						other_node->set_previous(current_node);

						// Add the other_node to the open_heap.
						open_heap.add(other_node);
					}

					// If the other_node is in the closed list but the new current_g_score is better then the one set already.
					else if (current_g_score < other_node->get_g_score())
					{
						// Overwrite the current_g_score.
						other_node->set_g_score(current_g_score);
						// and overwrite the previous.
						other_node->set_previous(current_node);
					}
				}
			}
		}

		// Will get here if there is no more paths to check.
		node<T>* end_node = a_end;
		m_path.push_back(end_node);

		// Backtrack the best path.
		while (end_node != a_start)
		{
			// If there is no valid path.
			if (!end_node)
			{
				m_path.clear();
				return m_path;
			}

			end_node = end_node->get_previous();
			m_path.push_back(end_node);
		}
		// Return the found path.
		return m_path;
	}


	//private:
	// The previously found path.
	std::vector<node<T>*> m_path;

	// The nodes that are in the graph.
	std::vector<node<T>*> m_nodes;
	// The edges that are in the graph.
	std::vector<edge<T>*> m_edges;
};

#endif // !GRAPH_H
