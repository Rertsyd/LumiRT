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

#include "Material.hpp"

struct Light
{
	Light();
	Light(RGB, double);
	virtual ~Light() = default;

	virtual RGB		Illuminate(RGB& diffuse, HitPoint& hp) const = 0;
	virtual Vector	GetPosition(const Vector& intersection) const = 0;
	virtual Vector	GetDirection(const Vector& intersection) const = 0;

	RGB		Color;
	double	Intensity;
};

using uPtrLight = std::unique_ptr<Light>;
using LightList = std::vector<uPtrLight>;

class Point : public Light
{
	Vector	Position;

public:
	Point();
	Point(RGB clr, double it, Vector pos);
	virtual ~Point() = default;

	virtual RGB		Illuminate(RGB& diffuse, HitPoint& hp) const;
	virtual Vector	GetPosition(const Vector& intersection) const;
	virtual Vector	GetDirection(const Vector& intersection) const;
};

//struct Spot : public Point {};

class Directional : public Light
{
	Vector	Direction;

public:
	Directional();
	Directional(RGB clr, double it, Vector dir);
	virtual ~Directional() = default;

	virtual RGB		Illuminate(RGB& diffuse, HitPoint& hp) const;
	virtual Vector	GetPosition(const Vector& intersection) const;
	virtual Vector	GetDirection(const Vector& intersection) const;
};
