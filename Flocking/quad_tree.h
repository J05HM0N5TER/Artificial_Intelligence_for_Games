#pragma once
#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "aabb.h"
#include <vector>
#include "Collision_manager.h"
#include "Renderer2D.h"

class boid;

class quad_tree
{
public:
	quad_tree() = delete;
	quad_tree(const aabb & a_boundry, int a_capacity = 4);
	~quad_tree();

	bool insert(boid * a_boid);

	void search(const aabb & a_range, std::vector<boid*>& a_found_out, boid* a_exclude_boid = nullptr) const;
	void search(const circle & a_range, std::vector<boid*>& a_found_out, boid* a_exclude_boid = nullptr) const;

	void clear();

	void draw(aie::Renderer2D* a_renerer) const;

private:
	bool m_is_divided;
	short m_capacity;

	aabb m_boundry;

	std::vector<boid*> m_boids;

	quad_tree* m_north_east;
	quad_tree* m_north_west;
	quad_tree* m_south_east;
	quad_tree* m_south_west;

	void sub_divide();

	bool contains(const aabb & a_range, const boid* a_boid) const;
	bool contains(const circle & a_range, const boid* a_boid) const;

};

#endif // !QUAD_TREE_H
