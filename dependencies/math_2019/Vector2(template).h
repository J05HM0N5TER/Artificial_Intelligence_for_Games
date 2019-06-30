#pragma once
#ifndef VECTOR2_TEMPLATE_H
#define VECTOR2_TEMPLATE_2

#include <cassert>
#include <cmath>

template <typename T>
class Vector2
{
public:
	Vector2<T>() {};
	Vector2<T>(const T a_x, const T a_y) : x(a_x), y(a_y) {}

	union
	{
		struct
		{
			T x;
			T y;
		};
		T data[2];
	};

	/*!	\brief Subscript operator overload, used for direct access.
		\param a_index [in] The index that the user is trying to access.
	*/
	T& operator[] (const size_t a_index)
	{
		_STL_ASSERT((a_index < 2), "Vector 2 index out of range");
		return data[a_index];
	}

	//! \brief Casting mutable float* operator overloading.
	operator T* ()
	{
		return data;
	}
	//! \brief Casting read only float* operator overloading.
	operator const T* () const
	{
		return data;
	}

	/*!	\brief Addition operator overload.
		\param The vector that your adding to this one.
		\return A vector with the sum of both vectors being added together.
	*/
	Vector2<T> operator + (const Vector2<T>& a_rhs) const
	{
		return Vector2<T>(x + a_rhs.x, y + a_rhs.y);
	}

	/*!	\brief Addition and equality overload.
		\param a_rhs [in] The vector that is being added.
		\return The pointer to the current vector.
	*/
	Vector2<T>& operator += (const Vector2<T> a_rhs)
	{
		x += a_rhs.x;
		y += a_rhs.y;
		return *this;
	}

	/*!	\brief Subtraction operator overload.
		\param a_rhs [in] The vector that is being subtracted.
		\return A vector with the results.
	*/
	Vector2<T> operator - (const Vector2<T>& a_rhs) const
	{
		return Vector2<T>(x - a_rhs.x, y - a_rhs.y);
	}

	/*!	\brief Subtraction and equality operator over-loader.
		\param The vector that your adding to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector2<T>& operator -= (const Vector2<T>& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		return *this;
	}

	/*!	\brief Multiplication operator over-loader.
		\param scalar [in] The amount that you are multiplying vector by.
		\return A vector with the completed multiplication.
	*/
	Vector2<T> operator * (const float scalar) const
	{
		return Vector2<T>(x * scalar, y * scalar);
	}

	/*!	\brief Multiplication operator.
		\param a_rhs [in] The vector that is being used to multiply this vector.
		\return A vector with the results.
	*/
	Vector2<T> operator * (const Vector2<T> a_rhs) const
	{
		return Vector2<T>(x * a_rhs.x, y * a_rhs.y);
	}

	/*!	\brief Multiplication operator overload.
		\param scalar [in] The variable that the vector is being multiplied by.
		\return The current vector by reference.
	*/
	Vector2<T> & operator * (const float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2<T> & operator *= (const Vector2<T> a_rhs)
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		return *this;
	}

	/*!	\brief Division operator over-loader.
		\param The amount that you are dividing vector by.
		\return A vector with the completed division.
	*/
	Vector2<T> operator / (float scalar) const
	{
		return Vector2<T>(x / scalar, y / scalar);
	}

	/*!	\brief Division and equality operator over-loader.
		\param The vector that your adding to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector2<T>& operator /= (float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	/*!	\brief Equality operator over-loader.
		\param The vector that are copying over the top of the current one.
		\return The pointer to the current vector.
	*/
	Vector2<T>& operator = (const Vector2<T>& a_rhs)
	{
		x = a_rhs.x;
		y = a_rhs.y;
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
		return x * x + y * y;
	}

	//! \brief Returns the normalised vector.
	Vector2<T> normalised() const
	{
		float temp_mag = magnitude();
		return (*this / temp_mag);
	}

	//! \brief Normalised the vector.
	Vector2<T>& normalise()
	{
		*this = this->normalized();
		return *this;
	}

	/*!	\brief Returns the dot product of two vectors.
		\param a_vector2 [in] The second angle that is being compared.
		\return The dot product (ratio) of the difference in two vector angles.
		\warning Use normalised vectors otherwise product will be incorrect.
	*/
	float dot(const Vector2<T>& a_vector2) const
	{
		return (x * a_vector2.x) + (y * a_vector2.y);
	}

	/*!	\brief Returns the dot product of two vectors.
		\param a_vector_a [in] The first angle that is being compared.
		\param a_vector_b [in] The first angle that is being compared. 
		\return The dot product (ratio) of the difference in two vector angles.
		\warning Use normalised vectors otherwise product will be incorrect.
	*/
	static float dot(const Vector2<T> a_vector_a, const Vector2<T> a_vector_b)
	{
		return a_vector_a.dot(a_vector_b);
	}

	/*! \brief Turns the angle 90 degrees to the right.
		\return A Vector2 with the angle off to the right by 90 degrees.
	*/
	Vector2<T> right() const
	{
		return Vector2<T>(y, -x);
	}
};

#endif // !VECTOR2_TEMPLATE_H

