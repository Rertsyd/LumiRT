/* ************************************************************************** */
/*                                             ,,                             */
/*   `7MMF'                                    db  `7MM"""Mq. MMP""MM""YMM    */
/*     MM                                            MM   `MM.P'   MM   `7    */
/*     MM      `7MM  `7MM  `7MMpMMMb.pMMMb.  `7MM    MM   ,M9      MM         */
/*     MM        MM    MM    MM    MM    MM    MM    MMmmdM9       MM         */
/*     MM      , MM    MM    MM    MM    MM    MM    MM  YM.       MM         */
/*     MM     ,M MM    MM    MM    MM    MM    MM    MM   `Mb.     MM         */
/*   .JMMmmmmMMM `Mbod"YML..JMML  JMML  JMML..JMML..JMML. .JMM.  .JMML.       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "RGB.hpp"

template <typename T>
struct TVec2
{
	TVec2() : x(0.), y(0.) {}
	TVec2(T _x, T _y) : x(_x), y(_y) {}
	~TVec2() = default;

	T	x, y;
};

using Vec2 = TVec2<double>;
using uVec2	= TVec2<unsigned>;

struct Vector
{
	double			x, y, z;

	Vector();
	Vector(Vector&& v);
	Vector(double _x, double _y, double _z);

	Vector(const Vector& v);
	~Vector() = default;

	Vector&	operator=(const Vector& v);
	bool	operator==(const Vector& v) const;

	double& operator[](const uint8_t i);
	const double& operator[](const uint8_t i) const;

	Vector	operator*(const Vector& v) const;
	Vector	operator*(const double d) const;
	Vector&	operator*=(const Vector& v);
	Vector&	operator*=(const double d);

	Vector	operator+(const Vector& v) const;
	Vector	operator+(const double d) const;
	Vector&	operator+=(const Vector& v);
	Vector&	operator+=(const double d);

	Vector	operator-(const Vector& v) const;
	Vector	operator-(const double d) const;
	Vector&	operator-=(const Vector& v);
	Vector&	operator-=(const double d);

	double	Dot(const Vector& v) const;
	double	SquareLength() const;
	double	Length() const;
	Vector&	Normalize();
};
