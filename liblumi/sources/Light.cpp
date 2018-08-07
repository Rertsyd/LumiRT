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

Light::Light() : Position(), Color(), Intensity(100.)
{}

Light::Light(Vector pos, RGB clr, float i) :
	Position(pos), Color(clr), Intensity(i)
{}

RGB	Light::Illuminate(RGB& diffuse, HitPoint& hp) const
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
