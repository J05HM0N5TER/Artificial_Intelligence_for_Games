#pragma once
#ifndef MATRIX4_TEMPLATE_H
#define MATRIX4_TEMPLATE_H

#include "Vector4(template).h"

// UNTESTED!

template <typename T>
class Matrix4
{
public:

	// --- Data definitions ---
	union
	{
		struct
		{
			T x_axis[4];
			T y_axis[4];
			T z_axis[4];
			T w_axis[4];
		};
		struct
		{
			Vector4<T> right;
			Vector4<T> up;
			Vector4<T> forwards;
			Vector4<T> position;
		};
		T _1D[16];
		T _2D[4][4];
		Vector4<T> axes[4];
	};


	// --- Constructors ---
	Matrix4<T>(const T a_m00 = 1.0f, const T a_m01 = 0.0f, const T a_m02 = 0.0f, const T a_m03 = 0.0f,	 // Column1
		const T a_m10 = 0.0f, const T a_m11 = 1.0f, const T a_m12 = 0.0f, const T a_m13 = 0.0f,		// Column2
		const T a_m20 = 0.0f, const T a_m21 = 0.0f, const T a_m22 = 1.0f, const T a_m23 = 0.0f,		// Column 3
		const T a_m30 = 0.0f, const T a_m31 = 0.0f, const T a_m32 = 0.0f, const T a_m33 = 1.0f) :	// Column4
		_1D{ a_m00, a_m01, a_m02, a_m03, a_m10, a_m11, a_m12, a_m13, a_m20, a_m21, a_m22, a_m23, a_m30, a_m31, a_m32, a_m33 }

	Matrix4<T>(const Vector4<T>& a_right, const Vector4<T>& a_up, const Vector4<T>& a_forwards, const Vector4<T>& a_position) :
		axes{ a_right , a_up , a_forwards, a_position }
	{}

	Matrix4<T>(const Matrix4<T>& a_matrix)
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
	Vector4<T>& operator [] (const int a_index)
	{
		return axes[a_index];
	}

	const Vector4<T>& operator [] (const int a_index) const
	{
		return axes[a_index];
	}

	Matrix4<T> operator * (const Matrix4<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] * a_rhs._2D[0][0] + _2D[1][0] * a_rhs._2D[0][1] + _2D[2][0] * a_rhs._2D[0][2] + _2D[3][0] * a_rhs._2D[0][3],
			_2D[0][1] * a_rhs._2D[0][0] + _2D[1][1] * a_rhs._2D[0][1] + _2D[2][1] * a_rhs._2D[0][2] + _2D[3][1] * a_rhs._2D[0][3],
			_2D[0][2] * a_rhs._2D[0][0] + _2D[1][2] * a_rhs._2D[0][1] + _2D[2][2] * a_rhs._2D[0][2] + _2D[3][2] * a_rhs._2D[0][3],
			_2D[0][3] * a_rhs._2D[0][0] + _2D[1][3] * a_rhs._2D[0][1] + _2D[2][3] * a_rhs._2D[0][2] + _2D[3][3] * a_rhs._2D[0][3],

			_2D[0][0] * a_rhs._2D[1][0] + _2D[1][0] * a_rhs._2D[1][1] + _2D[2][0] * a_rhs._2D[1][2] + _2D[3][0] * a_rhs._2D[1][3],
			_2D[0][1] * a_rhs._2D[1][0] + _2D[1][1] * a_rhs._2D[1][1] + _2D[2][1] * a_rhs._2D[1][2] + _2D[3][1] * a_rhs._2D[1][3],
			_2D[0][2] * a_rhs._2D[1][0] + _2D[1][2] * a_rhs._2D[1][1] + _2D[2][2] * a_rhs._2D[1][2] + _2D[3][2] * a_rhs._2D[1][3],
			_2D[0][3] * a_rhs._2D[1][0] + _2D[1][3] * a_rhs._2D[1][1] + _2D[2][3] * a_rhs._2D[1][2] + _2D[3][3] * a_rhs._2D[1][3],

			_2D[0][0] * a_rhs._2D[2][0] + _2D[1][0] * a_rhs._2D[2][1] + _2D[2][0] * a_rhs._2D[2][2] + _2D[3][0] * a_rhs._2D[2][3],
			_2D[0][1] * a_rhs._2D[2][0] + _2D[1][1] * a_rhs._2D[2][1] + _2D[2][1] * a_rhs._2D[2][2] + _2D[3][1] * a_rhs._2D[2][3],
			_2D[0][2] * a_rhs._2D[2][0] + _2D[1][2] * a_rhs._2D[2][1] + _2D[2][2] * a_rhs._2D[2][2] + _2D[3][2] * a_rhs._2D[2][3],
			_2D[0][3] * a_rhs._2D[2][0] + _2D[1][3] * a_rhs._2D[2][1] + _2D[2][3] * a_rhs._2D[2][2] + _2D[3][3] * a_rhs._2D[2][3],

			_2D[0][0] * a_rhs._2D[3][0] + _2D[1][0] * a_rhs._2D[3][1] + _2D[2][0] * a_rhs._2D[3][2] + _2D[3][0] * a_rhs._2D[3][3],
			_2D[0][1] * a_rhs._2D[3][0] + _2D[1][1] * a_rhs._2D[3][1] + _2D[2][1] * a_rhs._2D[3][2] + _2D[3][1] * a_rhs._2D[3][3],
			_2D[0][2] * a_rhs._2D[3][0] + _2D[1][2] * a_rhs._2D[3][1] + _2D[2][2] * a_rhs._2D[3][2] + _2D[3][2] * a_rhs._2D[3][3],
			_2D[0][3] * a_rhs._2D[3][0] + _2D[1][3] * a_rhs._2D[3][1] + _2D[2][3] * a_rhs._2D[3][2] + _2D[3][3] * a_rhs._2D[3][3]
		};
	}

	Vector4<T> operator * (const Vector4<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] * a_rhs[0] + _2D[1][0] * a_rhs[1] + _2D[2][0] * a_rhs[2] + _2D[3][0] * a_rhs[3],
			_2D[0][1] * a_rhs[0] + _2D[1][1] * a_rhs[1] + _2D[2][1] * a_rhs[2] + _2D[3][1] * a_rhs[3],
			_2D[0][2] * a_rhs[0] + _2D[1][2] * a_rhs[1] + _2D[2][2] * a_rhs[2] + _2D[3][2] * a_rhs[3],
			_2D[0][3] * a_rhs[0] + _2D[1][3] * a_rhs[1] + _2D[2][3] * a_rhs[2] + _2D[3][3] * a_rhs[3]
		};
	}

	// NOT FINISHED
	Matrix4<T>& operator *= (const Matrix4<T>& a_rhs)
	{
		*this = *this * a_rhs;

		return *this;
	}

	Matrix4<T> operator + (const Matrix4<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] + a_rhs._2D[0][0], _2D[0][1] + a_rhs._2D[0][1], _2D[0][2] + a_rhs._2D[0][2], _2D[0][3] + a_rhs._2D[0][3],
			_2D[1][0] + a_rhs._2D[1][0], _2D[1][1] + a_rhs._2D[1][1], _2D[1][2] + a_rhs._2D[1][2], _2D[1][3] + a_rhs._2D[1][3],
			_2D[2][0] + a_rhs._2D[2][0], _2D[2][1] + a_rhs._2D[2][1], _2D[2][2] + a_rhs._2D[2][2], _2D[2][3] + a_rhs._2D[2][3],
			_2D[3][0] + a_rhs._2D[3][0], _2D[3][1] + a_rhs._2D[3][1], _2D[3][2] + a_rhs._2D[3][2], _2D[3][3] + a_rhs._2D[3][3]
		};
	}

	Matrix4<T>& operator += (const Matrix4<T>& a_rhs)
	{
		*this = *this - a_rhs;

		return *this;
	}

	Matrix4<T> operator - (const Matrix4<T>& a_rhs) const
	{
		return
		{
			_2D[0][0] - a_rhs._2D[0][0], _2D[0][1] - a_rhs._2D[0][1], _2D[0][2] - a_rhs._2D[0][2], _2D[0][3] - a_rhs._2D[0][3],
			_2D[1][0] - a_rhs._2D[1][0], _2D[1][1] - a_rhs._2D[1][1], _2D[1][2] - a_rhs._2D[1][2], _2D[1][3] - a_rhs._2D[1][3],
			_2D[2][0] - a_rhs._2D[2][0], _2D[2][1] - a_rhs._2D[2][1], _2D[2][2] - a_rhs._2D[2][2], _2D[2][3] - a_rhs._2D[2][3],
			_2D[3][0] - a_rhs._2D[3][0], _2D[3][1] - a_rhs._2D[3][1], _2D[3][2] - a_rhs._2D[3][2], _2D[3][3] - a_rhs._2D[3][3]
		};
	}

	Matrix4<T>& operator -= (const Matrix4<T>& a_rhs)
	{
		*this = *this - a_rhs;

		return *this;
	}

	Matrix4<T>& operator = (const Matrix4<T>& a_rhs)
	{
		axes[0] = a_rhs.axes[0];
		axes[1] = a_rhs.axes[1];
		axes[2] = a_rhs.axes[2];
		axes[3] = a_rhs.axes[3];

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

#endif // !MATRIX4_TEMPLATE_H

