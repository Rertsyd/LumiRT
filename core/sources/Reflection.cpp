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

Vector	reflect(const Vector& incident, const Vector& normal)
{
	return incident - (normal * (incident.Dot(normal) * 2.));
}


RGBColor   Reflection(const LumiBox& lb, const Ray& r, Info& info, const unsigned depth)
{
	info.AddBias();

	Ray refl;
	refl.Origin = info.HP.Intersection;
	refl.Direction = reflect(r.Direction, info.HP.Normal).Normalize();

	return Cast(lb, refl, depth + 1) * info.Object->MatPtr->kReflection;
}
