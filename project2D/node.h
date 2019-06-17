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

	void add_edge(edge<T>* a_edge)
	{
		m_edges.push_back(a_edge);
	}

	void remove_edge(edge<T>* a_edge)
	{
		auto iter = std::find(m_edges.begin(), m_edges.end(), a_edge);
		m_edges.erase(iter);
	}

	void reset()
	{
		m_previous = nullptr;
		m_g_score = 0;
	}

	void set_valid(bool a_is_valid)
	{
		for (size_t i = 0; i < m_edges.size(); i++)
		{
			m_edges[i]->is_valid = a_is_valid;
		}
	}

	bool is_valid()
	{
		for (size_t i = 0; i < m_edges.size(); i++)
		{
			if (m_edges[i]->is_valid)
			{
				return true;
			}
		}
		return false;
	}

//private:
	std::vector<edge<T>*> m_edges;
	T m_data;

	node<T>* m_previous = nullptr;
	float m_g_score = 0;
};

#endif // !NODE_H
