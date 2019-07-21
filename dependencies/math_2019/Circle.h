#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include "Vector2.h"
#include "collider.h"
class circle : public collider
{
public:

	static const float DEFAULT_RADUS;

	circle(const Vector2 & a_position = Vector2(), const float a_radus = DEFAULT_RADUS);

	/*	\brief Sets the radius to the absolute value of the argument.
		\param The new radius as a float
	*/
	void set_radus(const float a_radus);
	const float get_radus() const;


	const Vector2 get_position() const;
	void set_position(const Vector2 & a_position);

	circle & operator = (const circle & a_rhs);
	bool operator == (const circle & a_rhs);
	bool operator != (const circle & a_rhs);

private:
	float m_radus = 0.0f;
	// Position is centre of circle.
	Vector2 m_position;
};

#endif // !CIRCLE_H

