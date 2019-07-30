#pragma once
#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <vector>
#include "Collision_manager.h"
#include "Renderer2D.h"

class boid;

class quad_tree
{
public:
	quad_tree(aabb & a_boundry = aabb(), const int & a_capacity = 4);
	~quad_tree();

	/*!	\brief Remakes the quad tree and sets it to empty.
		\param a_boundry The area that the quad tree takes up.
		\param a_capacity The amount of boid* that one quad tree can 
			hold before it sub-divides
	*/
	void restart(aabb & a_boundry, const int & a_capacity = 4);

	/*!	\brief Remakes the quad tree and populates it.
		\param a_boundry The area that the quad tree takes up.
		\param a_boids A vector with all the boids that are being 
			put into the quad tree.
		\param a_capacity The amount of boid* that one quad 
			tree can hold before it sub-divides.
	*/void restart(aabb & a_boundry, std::vector<boid*> & a_boids, 
	const int & a_capacity = 4);

	/*!	\brief To update the position of the boids without remaking the quad tree.
		\param a_boids A reference to where all the boid* are being stored.
		\note This does not update the dimensions of the quad tree.
	*/
	void update(std::vector<boid*> & a_boids);

	/*!	\brief To insert a boid into the quad tree.
		\param a_boid The pointer to the boid being inserted.
	*/
	bool insert(boid * a_boid);

	/*!	\brief Search for all of the boids in a area.
		\param a_range The area that you are searching for the boids in.
		\param a_found_out The vector that holds the output for the boids that are found.
		\param a_exclure_boid An optional boid to ignore if in the range.
	*/
	void search(const aabb & a_range, std::vector<boid*>& a_found_out, 
		const boid* a_exclude_boid = nullptr) const;

	/*!	\brief Search for all of the boids in a area.
		\param a_range The area that you are searching for the boids in.
		\param a_found_out The vector that holds the output for the boids that are found.
		\param a_exclure_boid An optional boid to ignore if in the range.
	*/
	void search(const circle & a_range, std::vector<boid*>& a_found_out, 
		const boid* a_exclude_boid = nullptr) const;

	// Deletes all sub quad_trees and deletes all stored boids.
	void clear();

	// Clears all stored boids.
	void clear_boids();

	// Deletes all empty quad trees.
	void remove_empty_trees();

	// Function to draw the quad tree.
	void draw(aie::Renderer2D* a_renerer) const;

private:
	// If the tree has been split.
	bool m_is_divided;
	// How many boid* can be in the tree before it sub-divides.
	short m_capacity;

	// The area that the quad tree is in.
	aabb m_boundry;

	// The vector of the boids stored in this quad tree.
	std::vector<boid*> m_boids;

	// The sub-trees
	quad_tree* m_north_east;
	quad_tree* m_north_west;
	quad_tree* m_south_east;
	quad_tree* m_south_west;

	// Function to divide the tree.
	void sub_divide();

	// Checkers to check if a boid could/should be in a tree.
	bool contains(const aabb & a_range, const boid* a_boid) const;
	bool contains(const circle & a_range, const boid* a_boid) const;

};

#endif // !QUAD_TREE_H
