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

#include "LumiRT.hpp"

static double	stFresnel(const Vector incident, const Vector normal, const double ior)
{
	double cosi = std::clamp(incident.Dot(normal), -1., 1.);
	double etai = 1, etat = ior;
	if (cosi > 0)
	{
		std::swap(etai, etat);
	}

	// Snell's law
	const double sint = etai / etat * sqrt(std::max(0., 1. - cosi * cosi));

	// Total internal reflection
	double kr = 1.;
	if (sint < 1.)
	{
		const double cost = sqrt(std::max(0., 1. - sint * sint));
		cosi = fabs(cosi);
		const double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		const double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) * 0.5;
	}
	return (kr);
}

static Vector	stRefract(const Vector incident, Vector normal, const double ior)
{
	double cosIncident = std::clamp(incident.Dot(normal), -1., 1.);
	double etai = 1, etat = ior;

	if (cosIncident < 0.)
		cosIncident *= -1.;
	else
	{
		std::swap(etai, etat);
		normal *= -1.;
	}
	const double eta = etai / etat;
	const double k = 1 - eta * eta * (1. - cosIncident * cosIncident);

	return (k < 0.) ? Vector() : (incident * eta) + (normal * (eta * cosIncident - sqrt(k)));
}

static RGB		stGetRefractColor(LumiBox& lb, Ray& r, Info& info, ReFracTools& tools)
{
	RGB	color;

	if (tools.kr < 1)
	{
		Ray refr;
		refr.Direction = (info.Object ) ? (r.Direction - tools.vbias) :
			stRefract(r.Direction , info.HP.Normal, tools.ior).Normalize();

		refr.Origin = (tools.isOutside) ?
			(info.HP.Intersection - tools.vbias) : info.HP.Intersection;

		color = info.HP.Albedo * Cast(lb, refr, tools.depth + 1u) * info.Object->MatPtr->Transparency;
	}

	return (color);
}

static RGB		stGetReflectColor(LumiBox& lb, Ray& r, Info& info, ReFracTools& tools)
{
	Ray refl;
	refl.Direction = reflect(r.Direction, info.HP.Normal).Normalize();

	refl.Origin = (tools.isOutside) ?
		info.HP.Intersection + tools.vbias :
		info.HP.Intersection - tools.vbias;

	return ((info.HP.Albedo * Cast(lb, refl, tools.depth + 1u)));
}

RGB   Refraction(LumiBox& lb, Ray& r, Info& info, unsigned depth)
{
	ReFracTools tools;
	tools.ior	= info.Object->MatPtr->kRefraction;
	tools.kr	= stFresnel(r.Direction, info.HP.Normal, tools.ior);
	tools.vbias	= info.HP.Normal * Config::Bias;
	tools.isOutside = (r.Direction.Dot(info.HP.Normal) < 0.) ? true : false;
	tools.depth = depth;

	const RGB	refractColor = stGetRefractColor(lb, r, info, tools);
	const RGB	reflectColor = stGetReflectColor(lb, r, info, tools);

	const RGB	color = (reflectColor * tools.kr) + (refractColor * (1. - tools.kr));

	return	(Config::Ambient * info.HP.Albedo * color + color);
}
