#pragma once
#ifndef NODE_H
#define NODE_H

#include <vector>
template <typename T>
class edge;

template <typename T>
class node
{
public:
	node<T>(const T& a_data) : m_data(a_data)
	{};

	~node() {};

	/*!	\brief Add a new edge to the node.
		\param a_edge The edge that is being added to the node.
	*/
	void add_edge(edge<T>* a_edge)
	{
		m_edges.push_back(a_edge);
	}

	/*!	\brief Remove an edge from the node.
		\param a_edge The edge that is being removed from the node.
	*/
	void remove_edge(edge<T>* a_edge)
	{
		auto iter = std::find(m_edges.begin(), m_edges.end(), a_edge);
		m_edges.erase(iter);
	}

	/*!	\brief Reset the values to default for path finding.
	*/
	void reset()
	{
		m_previous = nullptr;
		m_g_score = 0;
	}

	/*!	\brief Set all the edges connected to a node to a curtain state (valid or invalid).
		\param a_is_valid The state that you want to set all the connected edges to.
	*/
	void set_valid(bool a_is_valid)
	{
		for (size_t i = 0; i < m_edges.size(); i++)
		{
			m_edges[i]->is_valid = a_is_valid;
		}
	}

	void toggle_valid()
	{
		if (is_valid())
		{
			set_valid(false);
		}
		else
		{
			set_valid(true);
		}
	}

	/*!	\brief Tells if total state of the node according to the connected edges.
		\return True if there is any valid edges connected to the node.
	*/
	bool is_valid()
	{
		for (size_t i = 0; i < m_edges.size(); i++)
		{
			// If there is any edges that is valid then the node is valid.
			if (m_edges[i]->is_valid)
			{
				return true;
			}
		}
		return false;
	}

	//private:
		// All the the edges connected the node.
	std::vector<edge<T>*> m_edges;
	// The data that is being stored in the node.
	T m_data;

	// The previous node that was used to get to this node in path-finding.
	node<T>* m_previous = nullptr;
	// G score used in finding the 'cheapest' path.
	float m_g_score = 0;
};

#endif // !NODE_H
