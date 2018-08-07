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

static RGB	stSpecular(uPtrLight& point, Ray r, RGB li, Info& info)
{
	const Vector	lightDir = (info.HP.Intersection - point->Position).Normalize();
	const Vector	refl = reflect(lightDir, info.HP.Normal);
	const double	angle = refl.Dot(r.Direction * -1);

	return li * std::pow(std::max(0., angle), info.Object->MatPtr->ksExp);
}

RGB		Phong(LumiBox& lb, Ray& rPrimary, Info& info)
{
	RGB		diffuse, specular;
	
	info.AddBias();

	Ray rShadow;
	rShadow.Type = Ray::Types::Shadow;
	rShadow.Origin = info.HP.Intersection;

	for (auto& light : lb.LgtList)
	{
		rShadow.Direction = light->Position - info.HP.Intersection;

		Info	iShadow;
		iShadow.Distance = rShadow.Direction.SquareLength();
		iShadow.Object = info.Object;

		rShadow.Direction *= (1. / sqrt(iShadow.Distance));

		if (!Trace(lb.ShpList, rShadow, iShadow))
		{
			const RGB li = light->Illuminate(diffuse, info.HP);

			//specular += stSpecular(light, rPrimary, li, info);
		}
		else if (iShadow.Object->MatPtr->Type == Material::Types::Refraction)
		{
			const RGB li = light->Illuminate(diffuse, info.HP);
			diffuse = (diffuse * iShadow.Object->MatPtr->Albedo *
				iShadow.Object->MatPtr->Transparency).Normalize();
		}
	}

	return (Config::Ambient * info.HP.Albedo) +
		(diffuse * info.Object->MatPtr->kDiffuse +
		specular * info.Object->MatPtr->kSpecular);
}
