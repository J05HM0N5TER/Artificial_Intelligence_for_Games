#ifndef A_STAR_HEAP_H_
#define A_STAR_HEAP_H_

#include <tuple>

#include "node.h"
#include "Vector2.h"

class a_star_heap
{
public:
	a_star_heap() : m_item_count(0) , m_capacity(default_heap_size)
	{
		m_data = new node<Vector2>*[m_capacity];

	}

	~a_star_heap()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	static const size_t default_heap_size = 1024;

	// Return copy of lowest element without removal
	node<Vector2>* peek() { return m_data[0]; }

	// Copy of current member count
	size_t size() { return m_item_count;  }

	// Reset the contents
	void clear()
	{
		delete[] m_data;
		m_data = new node<Vector2>*[m_capacity];
	}

	int find(const node<Vector2>* a_item)
	{
		for (int i = 0; i < m_item_count; i++)
		{
			if (m_data[i] == a_item)
			{
				return i;
			}
		}
		return -1;
	}

	void add(node<Vector2>* a_item)
	{
		// Add at first available index
		m_data[m_item_count] = a_item;
		++m_item_count;
	
		// Re-balance | parent swap - Min heap
		int where_we_are = int(m_item_count) - 1;
		int our_parent = parent_of(where_we_are);
	
		while  ((where_we_are > 0) && 
				(m_data[where_we_are]->get_f_score() < m_data[our_parent]->get_f_score()))
		{
			// Swap and repeat
			node<Vector2>* swap_buffer = m_data[where_we_are];
			m_data[where_we_are] = m_data[our_parent];
			m_data[our_parent] = swap_buffer;
			// Iterate
			where_we_are = our_parent;
			our_parent = parent_of(where_we_are);
		}
	
	
	}

	node<Vector2>* pop()
	{
		node<Vector2>* out_data = m_data[0];
	
		// Last becomes first
		m_data[0] = m_data[m_item_count - 1];
	
		// Swap down the tree
		int where_we_are = 0;
		int left_child = 0;
		int right_child = 0;
	
		bool trading_down = true;
		while (/*bool trading_down = true;*/ trading_down)
		{
			// Gather indexes
			children_of(where_we_are, left_child, right_child);
	
			//auto[left, right] = children_of(where_we_are);
	
			int smaller_child_index = -1;
			if (left_child > 0 && right_child > 0)
			{
				// Identify smallest child
				smaller_child_index =
					(m_data[left_child]->get_g_score() > m_data[right_child]->get_g_score()) ? right_child : left_child;
			}
			else if (left_child > 0)
			{ 
				smaller_child_index = left_child; 
			}
			else
			{
				break; // Swapped as low as we can go.
			}
	
			// Swap if smaller than where we are
			if (m_data[where_we_are]->get_g_score() > m_data[smaller_child_index]->get_g_score())
			{ 
				node<Vector2>* swap_buffer = m_data[where_we_are];
				m_data[where_we_are] = m_data[smaller_child_index];
				m_data[smaller_child_index] = swap_buffer;
				where_we_are = smaller_child_index; // Continue trading down
			}
			else
			{
				trading_down = false;
			}
		}
	
		m_item_count--;
		return out_data;
	}

	node<Vector2>** m_data = nullptr;
	size_t m_capacity = 0;
	size_t m_item_count = 0;

	
	int parent_of(int a_index)
	{
		return (a_index > 0) ? (a_index - 1) / 2 : -1;
	}
	
	void children_of(int a_index, int& a_left_out, int& a_right_out)
	{
		a_left_out = left_child_of(a_index);
		a_right_out = right_child_of(a_index);
	}

	auto children_of(int a_index)
	{
		return std::make_tuple( left_child_of(a_index),  right_child_of(a_index) );
	}

	int left_child_of(int a_index)
	{
		int left_child_index = (2 * a_index + 1);
		return (left_child_index < m_item_count) ? left_child_index : -1;
	}

	int right_child_of(int a_index)
	{
		int right_child_index = (2 * a_index + 2);
		return (right_child_index < m_item_count) ? right_child_index : -1;
	}
};

#endif // !A_STAR_HEAP_H_
