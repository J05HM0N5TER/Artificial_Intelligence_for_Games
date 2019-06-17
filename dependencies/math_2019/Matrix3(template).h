#pragma once
#ifndef MATRIX3_TEMPLATE_H
#define MATRIX3_TEMPLATE_H

#include "Vector3(template).h"

// UNTESTED!

template <typename T>
class Matrix3
{
public:

	// --- Data definitions ---
	union
	{
		struct
		{
			T x_axis[3];
			T y_axis[3];
			T z_axis[3];
		};
		struct
		{
			Vector3<T> right;
			Vector3<T> forwards;
			Vector3<T> position;
		};
		T _1D[9];
		T _2D[3][3];
		Vector3<T> axes[3];
	};


	// --- Constructors ---
	Matrix3<T>(const T a_m00 = 1.0f, const T a_m01 = 0.0f, const T a_m02 = 0.0f, // Column1
		const T a_m10 = 0.0f, const T a_m11 = 1.0f, const T a_m12 = 0.0f, // Column2
		const T a_m20 = 0.0f, const T a_m21 = 0.0f, const T a_m22 = 1.0f) : // Column3
		_1D{ a_m00, a_m01, a_m02, a_m10, a_m11, a_m12, a_m20, a_m21, a_m22 } 
	{}

	Matrix3<T>(const Vector3<T>& a_right, const Vector3<T>& a_up, const Vector3<T>& a_forwards) :
		axes{ a_right , a_up , a_forwards }
	{}

	Matrix3<T>(const Matrix3<T>& a_matrix)
	{
		*this = a_matrix;
	}


	//! \brief Casting mutable T* operator overloading.
	operator T* ()
	{
		return _1D;
	}
	//! \brief Casting read only T* operator overloading.
	operator const T* () const
	{
		return _1D;
	}

	// --- Operator overloads ---
	Vector3<T>& operator [] (const int a_index)
	{
		return axes[a_index];
	}

	const Vector3<T>& operator [] (const int a_index) const
	{
		return axes[a_index];
	}

	Matrix3<T> operator * (const Matrix3<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] * a_rhs._2D[0][0] + _2D[1][0] * a_rhs._2D[0][1] + _2D[2][0] * a_rhs._2D[0][2], // First line
			_2D[0][1] * a_rhs._2D[0][0] + _2D[1][1] * a_rhs._2D[0][1] + _2D[2][1] * a_rhs._2D[0][2], // Expand to 1 column
			_2D[0][2] * a_rhs._2D[0][0] + _2D[1][2] * a_rhs._2D[0][1] + _2D[2][2] * a_rhs._2D[0][2], // 33%

			_2D[0][0] * a_rhs._2D[1][0] + _2D[1][0] * a_rhs._2D[1][1] + _2D[2][0] * a_rhs._2D[1][2], // Moving access RHS columns
			_2D[0][1] * a_rhs._2D[1][0] + _2D[1][1] * a_rhs._2D[1][1] + _2D[2][1] * a_rhs._2D[1][2],
			_2D[0][2] * a_rhs._2D[1][0] + _2D[1][2] * a_rhs._2D[1][1] + _2D[2][2] * a_rhs._2D[1][2], // 66%

			_2D[0][0] * a_rhs._2D[2][0] + _2D[1][0] * a_rhs._2D[2][1] + _2D[2][0] * a_rhs._2D[2][2], // Moving access RHS columns
			_2D[0][1] * a_rhs._2D[2][0] + _2D[1][1] * a_rhs._2D[2][1] + _2D[2][1] * a_rhs._2D[2][2],
			_2D[0][2] * a_rhs._2D[2][0] + _2D[1][2] * a_rhs._2D[2][1] + _2D[2][2] * a_rhs._2D[2][2], // 100%
		};
	}

	Vector3<T> operator * (const Vector3& a_rhs) const
	{
		return
		{
			_2D[0][0] * a_rhs[0] + _2D[1][0] * a_rhs[1] + _2D[2][0] * a_rhs[2],
			_2D[0][1] * a_rhs[0] + _2D[1][1] * a_rhs[1] + _2D[2][1] * a_rhs[2],
			_2D[0][2] * a_rhs[0] + _2D[1][2] * a_rhs[1] + _2D[2][2] * a_rhs[2],
		};
	}

	Matrix3<T>& operator *= (const Matrix3<T>& a_rhs)
	{
		*this = *this * a_rhs;

		return *this;
	}

	Matrix3<T> operator + (const Matrix3<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] + a_rhs._2D[0][0], _2D[0][1] + a_rhs._2D[0][1], _2D[0][2] + a_rhs._2D[0][2],
			_2D[1][0] + a_rhs._2D[1][0], _2D[1][1] + a_rhs._2D[1][1], _2D[1][2] + a_rhs._2D[1][2],
			_2D[2][0] + a_rhs._2D[2][0], _2D[2][1] + a_rhs._2D[2][1], _2D[2][2] + a_rhs._2D[2][2]
		};
	}

	Matrix3<T>& operator += (const Matrix3<T>& a_rhs)
	{
		*this = *this + a_rhs;

		return *this;
	}

	Matrix3<T> operator - (const Matrix3<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] - a_rhs._2D[0][0], _2D[0][1] - a_rhs._2D[0][1], _2D[0][2] - a_rhs._2D[0][2],
			_2D[1][0] - a_rhs._2D[1][0], _2D[1][1] - a_rhs._2D[1][1], _2D[1][2] - a_rhs._2D[1][2],
			_2D[2][0] - a_rhs._2D[2][0], _2D[2][1] - a_rhs._2D[2][1], _2D[2][2] - a_rhs._2D[2][2]
		};
	}

	Matrix3<T>& operator -= (const Matrix3<T>& a_rhs)
	{
		*this = *this - a_rhs;

		return *this;
	}

	Matrix3<T>& operator = (const Matrix3<T> a_rhs)
	{
		this->axes[0] = a_rhs.axes[0];
		this->axes[1] = a_rhs.axes[1];
		this->axes[2] = a_rhs.axes[2];

		return *this;
	}

	// --- Transform controls ---

	void setRotateX(const T& a_rotation)
	{
		_2D[1][1] = cos(a_rotation);
		_2D[1][2] = sin(a_rotation);
		_2D[2][1] = -sin(a_rotation);
		_2D[2][2] = cos(a_rotation);
	}
	void setRotateY(const T& a_rotation)
	{
		_2D[0][0] = cos(a_rotation);
		_2D[0][2] = -sin(a_rotation);
		_2D[2][0] = sin(a_rotation);
		_2D[2][2] = cos(a_rotation);
	}
	void setRotateZ(const T& a_rotation)
	{
		_2D[0][0] = cos(a_rotation);
		_2D[0][1] = sin(a_rotation);
		_2D[1][0] = -sin(a_rotation);
		_2D[1][1] = cos(a_rotation);
	}

};

#endif // !MATRIX3_TEMPLATE_H
