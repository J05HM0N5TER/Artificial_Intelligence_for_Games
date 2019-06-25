#pragma once
#ifndef HEAP_H
#define HEAP_H

#include <tuple>

template <typename T>
class heap
{
public:
	heap() : m_count(0), m_capacity(default_heap_size)
	{
		m_data = new T[m_capacity]{ 0 };
	}

	~heap()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	static const size_t default_heap_size = 1024;

	void add(const T& a_item)
	{
		// Add at first available index.
		m_data[m_count] = a_item;
		++m_count;

		// Rebalance | parent swap - Min heap
		int current_index = int(m_count);
		int our_parent = get_parent_index_of(current_index);

		while ((m_data[current_index] < m_data[our_parent]) && (current_index > 0))
		{
			// Swap and repeat.
			T swap_buffer = m_data[current_index];
			m_data[current_index] = m_data[our_parent];
			m_data[our_parent] = swap_buffer;

			current_index = our_parent;
			our_parent = get_parent_index_of(current_index);
		}
	}

	size_t size() { return m_count; }


	int find(const T& a_item)
	{
		for (size_t i = 0; i < m_count; i++)
		{
			if (m_data[i] == a_item)
			{
				return i;
			}
		}
	}

	T pop()
	{
		T out_data = m_data[0];

		// Last becomes first.
		m_data[0] = m_data[m_count - 1];
		int current_index = 0;
		int left_child = 0;
		int right_child = 0;
		bool trading_down = true;
		while (/*bool trading_down = true;*/ trading_down)
		{
			// Gather indexes.
			get_children_index_of(current_index, left_child, right_child);

			int smaller_child_index = -1;
			if (left_child > 0 && right_child > 0)
			{
				// Identify smallest child.
				smaller_child_index =
					(m_data[left_child] > m_data[right_child]) ? right_child : left_child;
			}
			else if (left_child > 0)
			{
				smaller_child_index = left_child;
			}
			else
			{
				break; // Swapped as low as we can go.
			}

			// Swap if smaller then current.
			if (m_data[current_index] > m_data[smaller_child_index])
			{
				T swap_buffer = m_data[current_index];
				m_data[current_index] = m_data[smaller_child_index];
				m_data[smaller_child_index] = swap_buffer;

				current_index = smaller_child_index; // Continue trading down.
			}
			else
			{
				trading_down = false;
			}

		}


		return out_data;
	}
	//private:

	T* m_data = nullptr;
	size_t m_capacity = 0;
	size_t m_count = 0;

	/*!	\brief Gets the parent of the specified index.
		\param The index of the element that you are getting the parent of.
		\note Will return -1 if a_index is not valid.
	*/
	int get_parent_index_of(int a_index)
	{
		return (a_index > 0) ? (a_index - 1) / 2 : -1;
	}

	/*!	\brief Get the children’s index.
		\param a_index The index of the element that you are getting
			the children of.
		\param a_left_out The reference of the location that it is writing the
			location of the left child to.
		\param a_right_out The reference of the location that it is writing the
			location of the right child to.
		\note If a_index is not valid then it will set values to -1.
	*/
	void get_children_index_of(int a_index, int& a_left_out, int& a_right_out)
	{
		a_left_out = get_left_child_index_of(a_index);
		a_right_out = get_right_child_index_of(a_index);
	}

	/*!	\brief Get the children’s index.
		\param a_index The index of the element that you are getting
			the children of.
		\return A tuple with [ left_child, right_child ].
		\note If a_index is not valid then it will set values to -1.
	*/
	auto get_children_index_of(int a_index)
	{
		return std::make_tuple(get_left_child_index_of(a_index),
			get_right_child_index_of(a_index));
	}

	/*!	\brief Get the left child’s index.
		\param a_index The index of the element that you are getting
			the left child of.
		\return The left child
		\note If a_index is not valid then it will set values to -1.
	*/
	int get_left_child_index_of(int a_index)
	{
		int left_child_index = (2 * a_index + 1);
		return  (left_child_index <= m_count) ? left_child_index : -1;
	}

	/*!	\brief Get the right child’s index.
		\param a_index The index of the element that you are getting
			the right child of.
		\return The right child
		\note If a_index is not valid then it will set values to -1.
	*/
	int get_right_child_index_of(int a_index)
	{
		int right_child_index = (2 * a_index + 2);
		return  (right_child_index <= m_count) ? right_child_index : -1;
	}
};



#endif // !HEAP_H

