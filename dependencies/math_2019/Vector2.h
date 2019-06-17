#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H

#include <cassert>
#include <cmath>

class Vector2
{
public:
	Vector2(float a_x = 0.0f, float a_y = 0.0f);

	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};

	/*!	\brief Subscript operator overload, used for direct access.
		\param a_index [in] The index that the user is trying to access.
	*/
	float& operator[] (const size_t a_index);

	//! \brief Casting mutable float* operator overloading.
	operator float* ();
	//! \brief Casting read only float* operator overloading.
	operator const float* () const;

	/*!	\brief Addition operator overload.
		\param The vector that your plussing to this one.
		\return A vector with the sum of both vectors being added together.
	*/
	Vector2 operator + (const Vector2& a_rhs) const;

	/*!	\brief Addition and equality overload.
		\param a_rhs [in] The vector that is being added.
		\return The pointer to the current vector.
	*/
	Vector2& operator += (const Vector2 a_rhs);

	/*!	\brief Subtraction operator overload.
		\param a_rhs [in] The vector that is being subtracted.
		\return A vector with the results.
	*/
	Vector2 operator - (const Vector2& a_rhs) const;

	/*!	\brief Subtraction and equality operator overloader.
		\param The vector that your plussing to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector2& operator -= (const Vector2& a_rhs);

	/*!	\brief Multiplication operator overloader.
		\param scalar [in] The amount that you are multiplying vector by.
		\return A vector with the completed multiplication.
	*/
	Vector2 operator * (const float scalar) const;

	/*!	\brief Multiplication operator.
		\param a_rhs [in] The vector that is being used to multiply this vector.
		\return A vector with the results.
	*/
	Vector2 operator * (const Vector2 a_rhs) const;

	/*!	\brief Multiplication operator overload.
		\param scalar [in] The variable that the vector is being multiplied by.
		\return The current vector by reference.
	*/
	Vector2 & operator * (const float scalar);

	Vector2 & operator *= (const Vector2 a_rhs);

	/*!	\brief Division operator overloader.
		\param The amount that you are dividing vector by.
		\return A vector with the completed division.
	*/
	Vector2 operator / (float scalar) const;

	/*!	\brief Division and equality operator overloader.
		\param The vector that your plussing to this one.
		\return The pointer to the current vector that your subtracting from.
	*/
	Vector2& operator /= (float scalar);

	/*!	\brief Equality operator overloader.
		\param The vector that are copying over the top of the current one.
		\return The pointer to the current vector.
	*/
	Vector2& operator = (const Vector2& a_rhs);

	//! \brief Returns squared magnitude.
	float square_magnitude() const;

	//! \brief Returns the distance between 0,0,0 and the coordinate.
	float magnitude() const;

	//! \brief Returns the normalised vector.
	Vector2 normalised() const;

	//! \brief Normalised the vector.
	Vector2& normalise();

	/*!	\brief Returns the dot product of two vectors.
		\param a_vector2 [in] The second angle that is being compared.
		\return The dot product (ratio) of the difference in two vector angles.
		\warning Use normalised vectors otherwise product will be incorrect.
	*/
	float dot(const Vector2& a_vector2) const;

	/*!	\brief Returns the dot product of two vectors.
		\param a_vector_a [in] The first angle that is being compared.
		\param a_vector_b [in] The first angle that is being compared.
		\return The dot product (ratio) of the difference in two vector angles.
		\warning Use normalised vectors otherwise product will be incorrect.
	*/
	static float dot(const Vector2 a_vector_a, const Vector2 a_vector_b);

	/*! \brief Turns the angle 90 degrees to the right.
		\return A Vector2 with the angle off to the right by 90 degrees.
	*/
	Vector2 right() const;
};

Vector2 operator * (const float& a_lhs, const Vector2& a_rhs);

#endif // !VECTOR2_H
