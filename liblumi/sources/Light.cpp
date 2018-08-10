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

#include "Light.hpp"

Light::Light(RGB clr, double it) : Color(clr), Intensity(it)
{}

/* ************** */

Point::Point(RGB clr, double it, Vector pos) : Light(clr, it), Position(pos)
{}

RGB	Point::Illuminate(RGB& diffuse, const HitPoint& hp) const
{
	Vector vlight = Position - hp.Intersection;
	const double r2 = vlight.SquareLength();
	vlight *= (1. / sqrt(r2));

	RGB il;
	
	if (const double angle = hp.Normal.Dot(vlight);
		angle > 0.)
	{
		il = Color * Intensity * (1. / (4. * Pi * r2));
		diffuse += il * hp.Albedo * angle;
	}
 
	return (il);
}

Vector	Point::GetDiffPos(const Vector& intersection) const
{
	return intersection - Position;
}

/* ************** */

Directional::Directional(RGB clr, double it, Vector dir) : Light(clr, it), Direction(dir)
{}

RGB	Directional::Illuminate(RGB& diffuse, const HitPoint& hp) const
{
	if (const double angle = hp.Normal.Dot(Direction * -1.);
		angle > 0.)
	{
		diffuse += hp.Albedo * Color * angle;
	}

	return (Color * Intensity);
}

Vector	Directional::GetDiffPos(const Vector& intersection) const
{
	// The return is a reduced version of this calculation :
	// intersection - (intersection + ((Direction * -1.) * FarFarAway));

	return Direction * FarFarAway;
}
