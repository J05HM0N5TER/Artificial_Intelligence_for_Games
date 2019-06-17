#include "Vector4.h"

Vector4::Vector4(const float a_x /*= 0.0f*/, const float a_y /*= 0.0f*/,
	const float a_z /*= 0.0f*/, const float a_w /*= 0.0f*/) :
	data{ a_x, a_y, a_z, a_w }
{}

float& Vector4::operator[] (const size_t a_index)
{
	_STL_ASSERT((a_index < 4), "Vector 4 index out of range");
	return data[a_index];
}

Vector4::operator float* ()
{
	return data;
}

Vector4::operator const float* () const
{
	return data;
}

Vector4 Vector4::operator + (const Vector4& a_rhs) const
{
	return { x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w };
}

Vector4& Vector4::operator += (const Vector4 a_rhs)
{
	x += a_rhs.x;
	y += a_rhs.y;
	z += a_rhs.z;
	w += a_rhs.w;

	return *this;
}

Vector4 Vector4::operator - (const Vector4& a_rhs) const
{
	return { x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w };
}

Vector4& Vector4::operator -= (const Vector4& a_rhs)
{
	x -= a_rhs.x;
	y -= a_rhs.y;
	z -= a_rhs.z;
	w -= a_rhs.w;
	return *this;
}

Vector4 Vector4::operator * (const float scalar) const
{
	return { x * scalar, y * scalar, z * scalar, w * scalar };
}

Vector4 Vector4::operator * (const Vector4 a_rhs) const
{
	return { x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w };
}

Vector4 & Vector4::operator * (const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector4 & Vector4::operator *= (const Vector4 a_rhs)
{
	x *= a_rhs.x;
	y *= a_rhs.y;
	z *= a_rhs.z;
	w *= a_rhs.w;
	return *this;
}

Vector4 Vector4::operator / (float scalar) const
{
	return { x / scalar, y / scalar, z / scalar, w / scalar };
}

Vector4& Vector4::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4& Vector4::operator = (const Vector4& a_rhs)
{
	x = a_rhs.x;
	y = a_rhs.y;
	z = a_rhs.z;
	w = a_rhs.w;

	return *this;
}

float Vector4::square_magnitude() const
{
	return ((x * x) + (y * y) + (z * z));
}

float Vector4::magnitude() const
{
	return std::sqrt(square_magnitude());
}

Vector4 Vector4::normalised() const
{
	float temp_mag = magnitude();
	return (*this / temp_mag);
}

Vector4& Vector4::normalise()
{
	*this = this->normalised();
	return *this;
}

float Vector4::dot(const Vector4& a_Vector4) const
{
	return (x * a_Vector4.x) + (y * a_Vector4.y) + (z * a_Vector4.z);
}

float Vector4::dot(const Vector4& a_vector_a, const Vector4& a_vector_b)
{
	return a_vector_a.dot(a_vector_b);
}

Vector4 Vector4::cross(const Vector4& a_Vector4) const
{
	return {
		y * a_Vector4.z - z * a_Vector4.y,
		z * a_Vector4.x - x * a_Vector4.z,
		x * a_Vector4.y - y * a_Vector4.x,
		w
	};
}

Vector4 Vector4::cross(const Vector4& a_vector_a, const Vector4& a_vector_b)
{
	return a_vector_a.cross(a_vector_b);
}

Vector4 operator*(const float & a_lhs, const Vector4 & a_rhs)
{
	return a_rhs * a_lhs;
}
