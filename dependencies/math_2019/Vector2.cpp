#include "Vector2.h"

Vector2::Vector2(float a_x /*= 0.0f*/, float a_y /*= 0.0f*/) : data{ a_x, a_y }
{
}

float& Vector2::operator[] (const size_t a_index)
{
	_STL_ASSERT((a_index < 2), "Vector 2 index out of range");
	return data[a_index];
}

Vector2::operator float*()
{
	return data;
}

Vector2::operator const float*() const
{
	return data;
}


Vector2 Vector2::operator + (const Vector2& a_rhs) const
{
	return { x + a_rhs.x, y + a_rhs.y };
}

Vector2& Vector2::operator += (const Vector2 a_rhs)
{
	x += a_rhs.x;
	y += a_rhs.y;
	return *this;
}

Vector2 Vector2::operator - (const Vector2& a_rhs) const
{
	return { x - a_rhs.x, y - a_rhs.y };
}

Vector2& Vector2::operator -= (const Vector2& a_rhs)
{
	x -= a_rhs.x;
	y -= a_rhs.y;
	return *this;
}

Vector2 Vector2::operator * (const float scalar) const
{
	return { x * scalar, y * scalar };
}

Vector2 Vector2::operator * (const Vector2 a_rhs) const
{
	return { x * a_rhs.x, y * a_rhs.y };
}

Vector2 & Vector2::operator * (const float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 & Vector2::operator *= (const Vector2 a_rhs)
{
	x *= a_rhs.x;
	y *= a_rhs.y;
	return *this;
}

Vector2 Vector2::operator / (float scalar) const
{
	return { x / scalar, y / scalar };
}

Vector2& Vector2::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& a_rhs)
{
	x = a_rhs.x;
	y = a_rhs.y;
	return *this;
}

float Vector2::square_magnitude() const
{
	return ((x * x) + (y * y));
}

float Vector2::magnitude() const
{
	return std::sqrt(square_magnitude());
}

Vector2 Vector2::normalised() const
{
	float temp_mag = magnitude();
	return (*this / temp_mag);
}

Vector2& Vector2::normalise()
{
	*this = this->normalised();
	return *this;
}

float Vector2::dot(const Vector2& a_vector2) const
{
	return (x * a_vector2.x) + (y * a_vector2.y);
}

float Vector2::dot(const Vector2 a_vector_a, const Vector2 a_vector_b)
{
	return a_vector_a.dot(a_vector_b);
}

Vector2 Vector2::right() const
{
	return Vector2(-y, x);
}

Vector2 operator*(const float & a_lhs, const Vector2 & a_rhs)
{
	return a_rhs * a_lhs;
}
