#pragma once
#ifndef VECTOR4_TEMPLATE_H
#define VECTOR4_TEMPLATE_H

#include <cassert>
#include <cmath>

// NOT COMPLETE!!!

template <typename T>
class Vector4
{
public:
	Vector4<T>() {};
	Vector4<T>(const T a_x, const T a_y, const T a_z) : x(a_x), y(a_y), z(a_z), w(1.0f) {}

	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		T data[4];
	};

	/*!
		\brief Subscript operator overload, used for direct access.
		\param a_index [in] The index that the user is trying to access.
	*/
	float& operator[] (const size_t a_index)
	{
		_STL_ASSERT((a_index < 4), "Vector 4 index out of range");
		return data[a_index];
	}

	//! \brief Casting mutable float* operator overloading.
	explicit operator T* ()
	{
		return data;
	}
	//! \brief Casting read only float* operator overloading.
	explicit operator const T* () const
	{
		return data;
	}

	/*!
		\brief Addition operator overloader.
		\param The vector that your plussing to this one.
		\return A vector with the sum of both vectors being added together.
	*/
	Vector4<T> operator + (const Vector4<T>& a_rhs) const
	{
		return Vector4<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w);
	}

	/*!
		\brief Subtraction and equality operator overloader.
		\param The vector that your plussing to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector4<T>& operator -= (const Vector4<T>& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		z -= a_rhs.z;
		return *this;
	}

	/*!
		\brief Multiplication operator overloader.
		\param The amount that you are multiplying vector by.
		\return A vector with the completed multiplication.
	*/
	Vector4<T> operator * (float scalar) const
	{
		return Vector4<T>(x * scalar, y * scalar, z * scalar, w);
	}

	/*!
		\brief Division and equality operator overloader.
		\param The vector that your plussing to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector4<T>& operator /= (float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	/*!
		\brief Equality operator overloader.
		\param The vector that are copying over the top of the current one.
		\return The pointer to the current vector.
	*/
	Vector4<T>& operator = (const Vector4<T>& a_rhs)
	{
		x = a_rhs.x;
		y = a_rhs.y;
		z = a_rhs.z;
		return *this;
	}

	//! \brief Returns the distance between 0,0,0 and the coordinate.
	float magnitude() const
	{
		return std::sqrt(square_magnitude());
	}

	//! \brief Returns squared magnitude.
	float square_magnitude() const
	{
		return x * x + y * y + z * z;
	}

	//! \brief Returns the normalised vector.
	Vector4<T> normalized() const
	{
		float temp_mag = magnitude();
		return (*this / temp_mag);
	}

	//! \brief Normalised the vector.
	Vector4<T>& normalize()
	{
		*this = this->normalized();
		return *this;
	}
};

#endif // !VECTOR4_TEMPLATE_H

