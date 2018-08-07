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

static RGB	AA(LumiBox& lb, uVec2 coord)
{
	static const unsigned	a2 = Config::AntiAliasing * Config::AntiAliasing;
	RGB	pxColor;

	for (unsigned offY = 0u; offY < Config::AntiAliasing; ++offY)
	{
		for (unsigned offX = 0u; offX < Config::AntiAliasing; ++offX)
		{
			Ray r;
			r.Origin = lb.Cam.Position;
			r.SetDir(lb.Cam,
				{ coord.x * Config::AntiAliasing + offX,
					coord.y * Config::AntiAliasing + offY },
				{ Config::Width * Config::AntiAliasing,
					Config::Height * Config::AntiAliasing }
			);
			pxColor += Cast(lb, r, 0u);
		}
	}

	pxColor *= (1. / static_cast<double>(a2));
	pxColor *= 255.;

	return pxColor;
}

void		Task(LumiBox& lb, unsigned threadId)
{
	const unsigned	init_x = Config::Width / Config::NbThread * threadId;
	const unsigned	cond_x = Config::Width / Config::NbThread * (threadId + 1);

	for (unsigned y = 0u; y < Config::Height; ++y)
		for (unsigned x = init_x; x < cond_x; ++x)
		{
			lb.Img.PutPixel({ x, y }, AA(lb, { x, y }));
		}
}
