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

#include "Matrix.hpp"

Matrix::Matrix() {}

/* ************** */

Matrix	Matrix::InitMatRotX(const double rotX)
{
	Matrix	mRotX;
	const double cosX = cos(rotX * Rad);
	const double sinX = sin(rotX * Rad);

	mRotX[0].x = 1.;
	mRotX[1].y = cosX;
	mRotX[1].z = -sinX;
	mRotX[2].y = sinX;
	mRotX[2].z = cosX;
	return mRotX;
}

Matrix	Matrix::InitMatRotY(const double rotY)
{
	Matrix	mRotY;
	const double cosY = cos(rotY * Rad);
	const double sinY = sin(rotY * Rad);

	mRotY[0].x = cosY;
	mRotY[0].z = sinY;
	mRotY[1].y = 1.;
	mRotY[2].x = -sinY;
	mRotY[2].z = cosY;
	return mRotY;
}

Matrix	Matrix::InitMatRotZ(const double rotZ)
{
	Matrix mRotZ;
	const double cosZ = cos(rotZ * Rad);
	const double sinZ = sin(rotZ * Rad);

	mRotZ[0].x = cosZ;
	mRotZ[0].y = -sinZ;
	mRotZ[1].x = sinZ;
	mRotZ[1].y = cosZ;
	mRotZ[2].z = 1.;
	return mRotZ;
}

/* ************** */

void	Matrix::InitRotation(Vector rot)
{
	*this = InitMatRotX(rot.x) * InitMatRotY(rot.y) * InitMatRotZ(rot.z);
}

Matrix&	Matrix::operator=(const Matrix& m)
{
	_mat[0] = m[0];
	_mat[1] = m[1];
	_mat[2] = m[2];
	return *this;
}

Vector&	Matrix::operator[](const uint8_t i)
{
	return _mat[i];
}

const Vector&	Matrix::operator[](const uint8_t i) const
{
	return _mat[i];
}

Vector	Matrix::operator*(const Vector& v) const
{
	return Vector(
		_mat[0].x * v.x + _mat[0].y * v.y + _mat[0].z * v.z,
		_mat[1].x * v.x + _mat[1].y * v.y + _mat[1].z * v.z,
		_mat[2].x * v.x + _mat[2].y * v.y + _mat[2].z * v.z);

}

Matrix	Matrix::operator*(const Matrix& m) const
{
	Matrix	mRet;

	for (uint8_t i = 0u; i < 3u; ++i)
		for (uint8_t j = 0u; j < 3u; ++j)
			for (uint8_t k = 0u; k < 3u; ++k)
			{
				mRet[i][j] += _mat[i][k] * m[k][j];
			}

	return mRet;
}
