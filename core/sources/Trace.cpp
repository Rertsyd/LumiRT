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

static void	stCheckDist(uPtrShape& shape, Ray& r, Info& info, Info& tmp)
{
	tmp.Distance = (tmp.HP.Intersection - r.Origin).SquareLength();

	if (tmp.Distance < info.Distance)
	{
		info.Distance = tmp.Distance;
		info.HP.Intersection = tmp.HP.Intersection;
		info.HP.Normal = tmp.HP.Normal;
		info.Object = shape.get();
		tmp.Reset();
	}
}

static void	stPrimary(ShapeList& shpl, Ray& rPrimary, Info& info)
{
	Info	tmp;

	tmp.Reset();
	for (auto& shape : shpl)
	{
		if (shape->Intersect(rPrimary, tmp.HP))
			stCheckDist(shape, rPrimary, info, tmp);
	}
}

static void	stShadow(ShapeList& shpl, Ray& rShadow, Info& info)
{
	Info			tmp;
	const Shape*	ptr = info.Object;

	tmp.Reset();
	info.Object = nullptr;
	for (auto it = shpl.begin();
		(!info.Object || info.Object->MatPtr->Type == Material::Types::Refraction) &&
		it != shpl.end();
		it++)
	{
		if (it->get() != ptr)
		{
			if ((*it)->Intersect(rShadow, tmp.HP))
				stCheckDist(*it, rShadow, info, tmp);
		}
	}
}

bool	Trace(ShapeList& shpl, Ray& r, Info& info)
{
	if (r.Type == Ray::Types::Primary)
		stPrimary(shpl, r, info);
	else if (r.Type == Ray::Types::Shadow)
		stShadow(shpl, r, info);

	return (info.Object != nullptr);
}
