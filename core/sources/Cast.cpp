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

RGBColor	Cast(const LumiBox& lb, const Ray& r, const unsigned depth)
{
	RGBColor HitColor = { 0.128, 0.128, 0.128 };

	if (depth < Ray::MaxDepth)
	{
		Info info;
		info.Reset();
		if (Trace(lb.ShpList, r, info))
		{
			info.HP.Albedo = info.Object->MatPtr->Albedo;

			switch (info.Object->MatPtr->Type)
			{
			case Material::Types::Phong:
				HitColor = Phong(lb, r, info);
				break;
			case Material::Types::Reflection:
				HitColor = Reflection(lb, r, info, depth);
				break;
			case Material::Types::Refraction:
				HitColor = Refraction(lb, r, info, depth);
				break;
			default:
				break;
			}
		}
	}

	return HitColor;
}
