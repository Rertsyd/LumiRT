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

#include "Vector.hpp"

Vector::Vector() : x(0.), y(0.), z(0.)
{}

Vector::Vector(Vector&& v) :
	x(std::move(v.x)),
	y(std::move(v.y)),
	z(std::move(v.z))
{}

Vector::Vector(double _x, double _y, double _z) :
	x(_x), y(_y), z(_z)
{}

Vector::Vector(const Vector& v)
{
	*this = v;
}

/* *********************************** */

Vector&	Vector::operator=(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

/* *********************************** */

double&			Vector::operator[](const uint8_t i)
{
	return (!i) ? x : ((i == 1u) ? y : z);
}

const double&	Vector::operator[](const uint8_t i) const
{
	return (!i) ? x : ((i == 1u) ? y : z);
}

/* *********************************** */

Vector	Vector::operator*(const Vector& v) const
{
	return Vector(
		(y * v.z) - (z * v.y),
		(z * v.x) - (x * v.z),
		(x * v.y) - (y * v.x));
}

Vector	Vector::operator*(const double d) const
{
	return Vector(x * d, y * d, z * d);
}

Vector&	Vector::operator*=(const Vector& v)
{
	const Vector tmp(*this);

	x = (tmp.y * v.z) - (tmp.z * v.y);
	y = (tmp.z * v.x) - (tmp.x * v.z);
	z = (tmp.x * v.y) - (tmp.y * v.x);
	return *this;
}

Vector&	Vector::operator*=(const double d)
{
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

/* *********************************** */

Vector	Vector::operator+(const Vector& v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector	Vector::operator+(const double d) const
{
	return Vector(x + d, y + d, z + d);
}

Vector&	Vector::operator+=(const Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector&	Vector::operator+=(const double d)
{
	x += d;
	y += d;
	z += d;
	return *this;
}

/* *********************************** */

Vector	Vector::operator-(const Vector& v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector	Vector::operator-(const double d) const
{
	return Vector(x - d, y - d, z - d);
}

Vector&	Vector::operator-=(const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector&	Vector::operator-=(const double d)
{
	x -= d;
	y -= d;
	z -= d;
	return *this;
}

/* *********************************** */

double	Vector::Dot(const Vector& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

double	Vector::SquareLength() const
{
	return x * x + y * y + z * z;
}

double	Vector::Length() const
{
	return std::sqrt(SquareLength());
}

Vector&	Vector::Normalize()
{
	const double len = Length();
	*this *= (1. / ((!len) ? 1 : len));

	return *this;
}
