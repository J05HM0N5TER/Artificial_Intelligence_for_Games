#pragma once
#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "boid.h"
#include "aabb.h"
#include <vector>
#include "Collision_manager.h"

class quad_tree
{
public:
	quad_tree() = delete;
	quad_tree(const aabb & a_boundry, int a_capacity = 4);
	~quad_tree();

	bool insert(boid * a_boid);

	void search(const aabb & a_range, std::vector<boid*>* a_found_out);
	void search(const circle & a_range, std::vector<boid*>* a_found_out);

	void clear();

private:
	bool m_is_divided = false;
	int m_capacity;

	aabb m_boundry;

	std::vector<boid*> m_boids;

	quad_tree* m_north_east = nullptr;
	quad_tree* m_north_west = nullptr;
	quad_tree* m_south_east = nullptr;
	quad_tree* m_south_west = nullptr;

	void sub_divide();

	bool contains(const aabb & a_range, const boid* a_boid);
	bool contains(const circle & a_range, const boid* a_boid);

};

#endif // !QUAD_TREE_H
