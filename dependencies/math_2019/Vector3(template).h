//! \brief Class for a 2D vector.

#pragma once
#ifndef VECTOR3_TEMPLATE_H
#define VECTOR3_TEMPLATE_H

#include <cassert>
#include <cmath>

template <typename T>
class Vector3
{
public:
	Vector3<T>() {};
	Vector3<T>(const T a_x, const T a_y, const T a_z) : x(a_x), y(a_y), z(a_z) {}

	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		struct
		{
			T r;
			T g;
			T b;
		};
		T data[3];
	};

	/*!	\brief Subscript operator overload, used for direct access.
		\param a_index [in] The index that the user is trying to access.
	*/
	T& operator[] (const size_t a_index)
	{
		_STL_ASSERT((a_index < 3), "Vector 3 index out of range");
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
	Vector3<T> operator + (const Vector3<T>& a_rhs) const
	{
		return Vector3<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z);
	}

	/*!	\brief Addition and equality overload.
		\param a_rhs [in] The vector that is being added.
		\return The pointer to the current vector.
	*/
	Vector3<T>& operator += (const Vector3<T> a_rhs)
	{
		x += a_rhs.x;
		y += a_rhs.y;
		z += a_rhs.z;
		return *this;
	}

	/*!	\brief Subtraction operator overload.
		\param a_rhs [in] The vector that is being subtracted.
		\return A vector with the results.
	*/
	Vector3<T> operator - (const Vector3<T>& a_rhs) const
	{
		return Vector3<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z);
	}

	/*!	\brief Subtraction and equality operator over-loader.
		\param The vector that your adding to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector3<T>& operator -= (const Vector3<T>& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		z -= a_rhs.z;
		return *this;
	}

	/*!	\brief Multiplication operator over-loader.
		\param scalar [in] The amount that you are multiplying vector by.
		\return A vector with the completed multiplication.
	*/
	Vector3<T> operator * (const float scalar) const
	{
		return Vector3<T>(x * scalar, y * scalar, z * scalar);
	}

	/*!	\brief Multiplication operator.
		\param a_rhs [in] The vector that is being used to multiply this vector.
		\return A vector with the results.
	*/
	Vector3<T> operator * (const Vector3<T> a_rhs) const
	{
		return Vector3<T>(x * a_rhs.x, y * a_rhs.y, z * a_rhs.z);
	}

	/*!	\brief Multiplication operator overload.
		\param scalar [in] The variable that the vector is being multiplied by.
		\return The current vector by reference.
	*/
	Vector3<T> & operator * (const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3<T> & operator *= (const Vector3<T> a_rhs)
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		z *= a_rhs.z;
		return *this;
	}

	/*!	\brief Division operator over-loader.
		\param The amount that you are dividing vector by.
		\return A vector with the completed division.
	*/
	Vector3<T> operator / (float scalar) const
	{
		return Vector3<T>(x / scalar, y / scalar, z / scalar);
	}

	/*!	\brief Division and equality operator over-loader.
		\param The vector that your adding to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector3<T>& operator /= (float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	/*!	\brief Equality operator over-loader.
		\param The vector that are copying over the top of the current one.
		\return The pointer to the current vector.
	*/
	Vector3<T>& operator = (const Vector3<T>& a_rhs)
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
	Vector3<T> normalized() const
	{
		float temp_mag = magnitude();
		return (*this / temp_mag);
	}

	//! \brief Normalised the vector.
	Vector3<T>& normalize()
	{
		*this = this->normalized();
		return *this;
	}

	/*!	\brief Returns the dot product of two vectors.
		\param a_vector3 [in] The second angle that is being compared.
		\return The dot product (ratio) of the difference in two vector angles.
		\warning Use normalised vectors otherwise product will be incorrect.
	*/
	float dot(const Vector3<T>& a_vector3) const
	{
		return (x * a_vector3.x) + (y * a_vector3.y) + (z * a_vector3.z);
	}

	/*!	\brief Returns the dot product of two vectors.
		\param a_vector_a [in] The first angle that is being compared.
		\param a_vector_b [in] The first angle that is being compared.
		\return The dot product (ratio) of the difference in two vector angles.
		\warning Use normalised vectors otherwise product will be incorrect.
	*/
	static float dot(const Vector3<T>& a_vector_a, const Vector3<T>& a_vector_b)
	{
		return a_vector_a.dot(a_vector_b);
	}

	/*!	\brief Finds the vector perpendicular to the two angles supplies.
		\param a_vector3 [in] The second angle that is being used to find the perpendicular.
		\return A vector3 with the perpendicular angle.
	*/
	Vector3<T> cross(const Vector3<T>& a_vector3) const
	{
		return Vector3(y * a_vector3.z - z * a_vector3.y,
			z * a_vector3.x - x * a_vector3.z,
			x * a_vector3.y - y * a_vector3.x);
	}

	/*!	\brief Finds the vector perpendicular to the two angles supplies.
		\param a_vector3 [in] The second angle that is being used to find the perpendicular.
		\return A vector3 with the perpendicular angle.
	*/
	static Vector3<T> cross(const Vector3<T>& a_vector_a, const Vector3<T>& a_vector_b)
	{
		return a_vector_a.cross(a_vector_b);
	}
};

#endif // !VECTOR3_TEMPLATE_H
