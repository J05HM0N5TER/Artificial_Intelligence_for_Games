#include "line.h"
#include <limits>

const Vector2 line::DEFAULT_NORMAL = { 0.0f, 1.0f };

line::line(const Vector2 & a_normal /*= { 0.0f, 1.0f }*/, 
	const float a_distance /*= 0.0f*/) :
	collider(shape::line),
	m_normal(a_normal),
	m_distance(a_distance)
{
	set_normal(m_normal);
}

const Vector2 line::get_normal() const
{
	return m_normal;
}

void line::set_normal(const Vector2 & a_normal)
{
	if (m_normal.magnitude() < std::numeric_limits<float>::min())
	{
		m_normal = DEFAULT_NORMAL;
	}
	else
	{
		m_normal.normalise();
	}
}

const float line::get_distance() const
{
	return m_distance;
}

void line::set_distance(const float a_distance)
{
	m_distance = a_distance;
}
