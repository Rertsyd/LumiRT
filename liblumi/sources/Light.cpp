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

Light::Light() : Color(), Intensity(100.)
{}

Light::Light(RGB clr, double it) : Color(clr), Intensity(it)
{}

/* ************** */

Point::Point() : Light(), Position()
{}

Point::Point(RGB clr, double it, Vector pos) : Light(clr, it), Position(pos)
{}

RGB	Point::Illuminate(RGB& diffuse, HitPoint& hp) const
{
	Vector vlight = Position - hp.Intersection;
	const double r2 = vlight.SquareLength();
	vlight *= (1. / sqrt(r2));

	RGB il;
	const double angle = hp.Normal.Dot(vlight);
	if (angle > 0.)
	{
		il = Color * Intensity * (1. / (4. * Pi * r2));
		diffuse += (il * hp.Albedo) * angle;
	}
 
	return (il);
}

Vector	Point::GetPosition(const Vector&) const
{
	return Position;
}

Vector	Point::GetDirection(const Vector& intersection) const
{
	return std::move((Position - intersection).Normalize());
}

/* ************** */

Directional::Directional() : Light(), Direction()
{}

Directional::Directional(RGB clr, double it, Vector dir) : Light(clr, it), Direction(dir)
{}

RGB	Directional::Illuminate(RGB& diffuse, HitPoint& hp) const
{
	if (const double angle = hp.Normal.Dot(Direction * -1.);
		angle > 0.)
	{
		diffuse += hp.Albedo * Color * angle;
	}

	return (Color * Intensity);
}

Vector	Directional::GetPosition(const Vector& intersection) const
{
	return std::move(intersection + (Direction * -1. * 999.));
}

Vector	Directional::GetDirection(const Vector&) const
{
	return Direction;
}
