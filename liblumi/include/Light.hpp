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

static constexpr double FarFarAway = 999.;

class Light
{
	Light() = delete;

protected:
	const RGBColor		Color;
	const double	Intensity;

public:
	Light(RGBColor clr, double it);
	virtual ~Light() = default;

	virtual RGBColor		Illuminate(RGBColor& diffuse, const HitPoint& hp) const = 0;
	virtual Vector	GetDiffPos(const Vector& intersection) const = 0;
};

using uPtrLight = std::unique_ptr<Light>;
using LightList = std::vector<uPtrLight>;

class Point : public Light
{
	Point() = delete;

	const Vector	Position;

public:
	Point(RGBColor clr, double it, Vector pos);
	virtual ~Point() = default;

	virtual RGBColor		Illuminate(RGBColor& diffuse, const HitPoint& hp) const;
	virtual Vector	GetDiffPos(const Vector& intersection) const;
};

class Directional : public Light
{
	Directional() = delete;

	const Vector	Direction;

public:
	Directional(RGBColor clr, double it, Vector dir);
	virtual ~Directional() = default;

	virtual RGBColor		Illuminate(RGBColor& diffuse, const HitPoint& hp) const;
	virtual Vector	GetDiffPos(const Vector& intersection) const;
};
