#include "Vector3.h"

Vector3::Vector3(const float a_x /*= 0.0f*/, const float a_y /*= 0.0f*/, const float a_z /*= 0.0f*/) :
	data { a_x, a_y, a_z }
{}

float& Vector3::operator[] (const size_t a_index)
{
	_STL_ASSERT((a_index < 3), "Vector 3 index out of range");
	return data[a_index];
}

Vector3::operator float* ()
{
	return data;
}

Vector3::operator const float* () const
{
	return data;
}

Vector3 Vector3::operator + (const Vector3& a_rhs) const
{
	return { x + a_rhs.x, y + a_rhs.y, z + a_rhs.z };
}

Vector3& Vector3::operator += (const Vector3 a_rhs)
{
	x += a_rhs.x;
	y += a_rhs.y;
	z += a_rhs.z;
	return *this;
}

Vector3 Vector3::operator - (const Vector3& a_rhs) const
{
	return { x - a_rhs.x, y - a_rhs.y, z - a_rhs.z };
}

Vector3& Vector3::operator -= (const Vector3& a_rhs)
{
	x -= a_rhs.x;
	y -= a_rhs.y;
	z -= a_rhs.z;
	return *this;
}

Vector3 Vector3::operator * (const float scalar) const
{
	return { x * scalar, y * scalar, z * scalar };
}

Vector3 Vector3::operator * (const Vector3 a_rhs) const
{
	return { x * a_rhs.x, y * a_rhs.y, z * a_rhs.z };
}

Vector3 & Vector3::operator *= (const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3 & Vector3::operator *= (const Vector3 a_rhs)
{
	x *= a_rhs.x;
	y *= a_rhs.y;
	z *= a_rhs.z;
	return *this;
}

Vector3 Vector3::operator / (float scalar) const
{
	return { x / scalar, y / scalar, z / scalar };
}

Vector3& Vector3::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vector3& Vector3::operator = (const Vector3& a_rhs)
{
	x = a_rhs.x;
	y = a_rhs.y;
	z = a_rhs.z;
	return *this;
}

float Vector3::square_magnitude() const
{
	return x * x + y * y + z * z;
}

float Vector3::magnitude() const
{
	return std::sqrt(square_magnitude());
}

Vector3 Vector3::normalised() const
{
	float temp_mag = magnitude();
	return (*this / temp_mag);
}

Vector3& Vector3::normalise()
{
	*this = this->normalised();
	return *this;
}

float Vector3::dot(const Vector3& a_vector3) const
{
	return ((x * a_vector3.x) + (y * a_vector3.y) + (z * a_vector3.z));
}

float Vector3::dot(const Vector3& a_vector_a, const Vector3& a_vector_b)
{
	return a_vector_a.dot(a_vector_b);
}

Vector3 Vector3::cross(const Vector3& a_vector3) const
{
	return {
		y * a_vector3.z - z * a_vector3.y,
		z * a_vector3.x - x * a_vector3.z,
		x * a_vector3.y - y * a_vector3.x 
	};
}

Vector3 Vector3::cross(const Vector3& a_vector_a, const Vector3& a_vector_b)
{
	return a_vector_a.cross(a_vector_b);
}

Vector3 operator*(const float & a_lhs, const Vector3 & a_rhs)
{
	return a_rhs * a_lhs;
}
