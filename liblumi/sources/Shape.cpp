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

#include <limits>
#include "Shape.hpp"

Shape::Shape(Vector pos, const uPtrMaterial& mat) : Position(pos), MatPtr(mat)
{}

/* ************** */

Plane::Plane(Vector pos, const uPtrMaterial& mat) :
	Shape(pos, mat), Normal(), Rotation()
{}

bool	Plane::Intersect(const Ray& r, HitPoint& hp) const
{
	bool			err = false;
	const double	dv = Normal.Dot(r.Direction);

	if (dv > Zero || dv < -Zero)
	{
		const double t = (Position - r.Origin).Dot(Normal) / dv;
		if (t > Zero)
		{
			err = true;
			hp.Intersection = r.Origin + r.Direction * t;
			hp.Normal = (dv > Zero) ? Normal * (-1.) : Normal;
		}
	}
	return (err);
}

/* ************** */

Sphere::Sphere(Vector pos, const uPtrMaterial& mat) :
	Shape(pos, mat), Radius(0.)
{}

bool	Sphere::Intersect(const Ray& r, HitPoint& hp) const
{
	bool	err = false;

	const Vector	X = r.Origin - Position;
	const double	b = X.Dot(r.Direction);
	const double	delta = (b * b) - (X.SquareLength() - Radius * Radius);

	if (delta >= 0.)
	{
		double t = -b;	// one solution

		if (delta)	// two solutions
		{
			const double root = sqrt(delta);
			auto p = std::make_pair(-b + root, -b - root);
			
			if (p.first > p.second)
				std::swap(p.first, p.second);

			t = p.first;
		}

		if (t > 0.)
		{
			err = true;
			hp.Intersection = r.Origin + r.Direction * t;
			hp.Normal = ((hp.Intersection - Position) * (1. / Radius)).Normalize();
		}
	}
	return (err);
}
