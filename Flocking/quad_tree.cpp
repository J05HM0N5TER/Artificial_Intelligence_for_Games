#include "quad_tree.h"
#include "boid.h"


quad_tree::quad_tree(aabb & a_boundry/* = aabb()*/, const int & a_capacity/* = 4*/) :
	m_boundry(a_boundry), m_capacity(a_capacity), m_north_east(nullptr),
	m_north_west(nullptr), m_south_east(nullptr), m_south_west(nullptr),
	m_is_divided(false)
{ }

quad_tree::~quad_tree()
{
	this->clear();
}

void quad_tree::restart(aabb & a_boundry, const int & a_capacity/* = 4*/)
{
	this->clear();

	m_capacity = a_capacity;

	m_boundry = a_boundry;
}

void quad_tree::restart(aabb & a_boundry, std::vector<boid*> a_boids, const int & a_capacity/* = 4*/)
{
	this->clear();

	m_capacity = a_capacity;
	m_boundry = a_boundry;

	for (boid* a_boid : m_boids)
	{
		this->insert(a_boid);
	}
}

void quad_tree::update(std::vector<boid*> a_boids)
{
	this->clear_boids();

	for (boid* a_boid : a_boids)
	{
		this->insert(a_boid);
	}

	this->remove_empty_trees();
}

bool quad_tree::insert(boid * a_boid)
{
	// Check if the point should be in this quad tree.
	if (!this->contains(this->m_boundry, a_boid))
	{
		return false;
	}

	// If it has not reached capacity.
	else if (this->m_boids.size() < this->m_capacity)
	{
		// insert into the boids.
		m_boids.push_back(a_boid);
		return true;
	}

	// If it has reached capacity.
	else
	{
		// divide if necessary.
		if (!m_is_divided)
		{
			sub_divide();
		}
		bool has_inserted = false;

		// Insert into the correct quad tree.
		if (this->m_north_west->insert(a_boid))
			has_inserted = true;

		else if (this->m_north_east->insert(a_boid))
			has_inserted = true;

		else if (this->m_south_east->insert(a_boid))
			has_inserted = true;

		else if (this->m_south_west->insert(a_boid))
			has_inserted = true;

		return has_inserted;
	}
}

void quad_tree::search(const aabb & a_range, std::vector<boid*>& a_found_out, const boid* a_exclude_boid/* = nullptr*/) const
{
	if (!collision_manager::aabb_to_aabb(this->m_boundry, a_range))
	{
		return;
	}

	for (boid* a_boid : m_boids)
	{
		if (a_boid == a_exclude_boid)
			continue;

		if (contains(a_range, a_boid))
		{
			a_found_out.push_back(a_boid);
		}
	}
	if (this->m_is_divided)
	{
		this->m_north_east->search(a_range, a_found_out, a_exclude_boid);
		this->m_north_west->search(a_range, a_found_out, a_exclude_boid);
		this->m_south_east->search(a_range, a_found_out, a_exclude_boid);
		this->m_south_west->search(a_range, a_found_out, a_exclude_boid);
	}
}

void quad_tree::search(const circle & a_range, std::vector<boid*>& a_found_out, const boid* a_exclude_boid/* = nullptr*/) const
{
	if (!collision_manager::aabb_to_circle(this->m_boundry, a_range))
	{
		return;
	}
	for (boid* a_boid : m_boids)
	{
		if (a_boid == a_exclude_boid)
			continue;

		if (contains(a_range, a_boid))
		{
			a_found_out.push_back(a_boid);
		}
	}
	if (this->m_is_divided)
	{
		this->m_north_east->search(a_range, a_found_out, a_exclude_boid);
		this->m_north_west->search(a_range, a_found_out, a_exclude_boid);
		this->m_south_east->search(a_range, a_found_out, a_exclude_boid);
		this->m_south_west->search(a_range, a_found_out, a_exclude_boid);
	}
}

void quad_tree::clear()
{
	m_boids.clear();

	if (m_is_divided)
	{
		delete this->m_north_east;
		this->m_north_east = nullptr;

		delete this->m_north_west;
		this->m_north_west = nullptr;

		delete this->m_south_east;
		this->m_south_east = nullptr;

		delete this->m_south_west;
		this->m_south_west = nullptr;

		this->m_is_divided = false;
	}
}

void quad_tree::clear_boids()
{
	this->m_boids.clear();

	if (this->m_is_divided)
	{
		this->m_north_east->clear_boids();
		this->m_north_west->clear_boids();
		this->m_south_east->clear_boids();
		this->m_south_west->clear_boids();
	}
}

void quad_tree::remove_empty_trees()
{
	if (!m_is_divided)
	{
		return;
	}

	else if (m_north_east->m_boids.size() == 0 &&
		m_north_west->m_boids.size() == 0 &&
		m_south_east->m_boids.size() == 0 &&
		m_south_west->m_boids.size() == 0)
	{
		delete this->m_north_east;
		this->m_north_east = nullptr;

		delete this->m_north_west;
		this->m_north_west = nullptr;

		delete this->m_south_east;
		this->m_south_east = nullptr;

		delete this->m_south_west;
		this->m_south_west = nullptr;

		this->m_is_divided = false;
	}

	else
	{
		m_north_east->remove_empty_trees();
		m_north_west->remove_empty_trees();
		m_south_east->remove_empty_trees();
		m_south_west->remove_empty_trees();
	}
}

void quad_tree::draw(aie::Renderer2D* a_renderer) const
{
	// Draw this quad tree.
	//Vector2 min = this->m_boundry.get_min();
	//Vector2 max = this->m_boundry.get_max();

	//a_renderer->drawLine(min.x, min.y, min.x, max.y);
	//a_renderer->drawLine(min.x, min.y, max.x, min.y);
	//a_renderer->drawLine(max.x, max.y, max.x, min.y);
	//a_renderer->drawLine(max.x, max.y, min.x, max.y);

	if (m_is_divided)
	{

		// Draw this quad tree.
		Vector2 min = this->m_boundry.get_min();
		Vector2 max = this->m_boundry.get_max();

		a_renderer->drawLine(min.x, (max.y + min.y) / 2, max.x, (max.y + min.y) / 2);
		a_renderer->drawLine((max.x + min.x) / 2, min.y, (max.x + min.x) / 2, max.y);

		// Draw the sub-trees.
		this->m_north_east->draw(a_renderer);
		this->m_north_west->draw(a_renderer);
		this->m_south_east->draw(a_renderer);
		this->m_south_west->draw(a_renderer);
	}
}

void quad_tree::sub_divide()
{
	float x = this->m_boundry.get_position().x;
	float y = this->m_boundry.get_position().y;
	float width = this->m_boundry.get_width();
	float height = this->m_boundry.get_height();

	Vector2 half_extents = this->m_boundry.get_extents() / 2;

	// Create the new quad trees.
	this->m_north_east = new quad_tree(aabb({ x + (width / 4), y + (height / 4) },
		half_extents), this->m_capacity);
	this->m_north_west = new quad_tree(aabb({ x - (width / 4), y + (height / 4) },
		half_extents), this->m_capacity);
	this->m_south_east = new quad_tree(aabb({ x + (width / 4), y - (height / 4) },
		half_extents), this->m_capacity);
	this->m_south_west = new quad_tree(aabb({ x - (width / 4), y - (height / 4) },
		half_extents), this->m_capacity);

	m_is_divided = true;
}

bool quad_tree::contains(const aabb & a_range, const boid * a_boid) const
{
	return !(a_boid->get_position().x <= a_range.get_min().x ||
		a_boid->get_position().x > a_range.get_max().x ||
		a_boid->get_position().y <= a_range.get_min().y ||
		a_boid->get_position().y > a_range.get_max().y);
}

bool quad_tree::contains(const circle & a_range, const boid * a_boid) const
{
	return (a_boid->m_position - a_range.get_position()).square_magnitude() < a_range.get_radus() * a_range.get_radus();
}
