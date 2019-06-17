#include "aabb.h"
#include <cmath>

const Vector2 aabb::DEFAULT_EXTENTS = { 5.0f, 5.0f };

aabb::aabb(
	const Vector2 & a_position /*= Vector2()*/, 
	const Vector2 & a_extents /*= DEFAULT_EXTENTS*/) :
	collider(shape::aabb),
	m_position(a_position), m_extents(a_extents)
{
}

const Vector2 aabb::get_position() const
{
	return m_position;
}

void aabb::set_position(const Vector2 & a_position)
{
	m_position = a_position;
}

const Vector2 aabb::get_extents() const
{
	return m_extents;
}

void aabb::set_extents(const Vector2 & a_extents)
{
	m_extents = { abs(a_extents.x), abs(a_extents.y) };
}

const float aabb::get_width() const
{
	return m_extents.x;
}

const float aabb::get_height() const
{
	return m_extents.y;
}

const Vector2 aabb::get_max() const
{
	return m_position + 0.5f * m_extents;
}

const Vector2 aabb::get_min() const
{
	return m_position - 0.5f * m_extents;
}

