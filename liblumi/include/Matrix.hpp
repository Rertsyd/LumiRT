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

#include "Vector.hpp"

class Matrix
{
	Vector	_mat[3];

	static Matrix	InitMatRotX(const double rotX);
	static Matrix	InitMatRotY(const double rotY);
	static Matrix	InitMatRotZ(const double rotZ);

public:
	Matrix();
	~Matrix() = default;

	void	InitRotation(const Vector rot);

	Matrix&	operator=(const Matrix& m);

	Vector& operator [](const uint8_t i);
	const Vector& operator [](const uint8_t i) const;

	Vector	operator*(const Vector& v) const;
	Matrix	operator*(const Matrix& m) const;
	//Matrix&	operator*=(const Matrix& m);
};
