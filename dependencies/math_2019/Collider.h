#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

class collider
{
public:
	// Disable default constructor.
	collider() = delete;

	enum class shape : char
	{
		none = 0,
		circle,
		aabb,
		line,
	};

	const shape get_shape() const;

protected:

	shape m_shape = shape::none;
	collider(shape a_shape);
};

#endif // !COLLIDER_H
