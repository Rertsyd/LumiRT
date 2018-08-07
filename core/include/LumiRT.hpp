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

#pragma once

#include "TinyParser.hpp"

void	Task(LumiBox& lb, unsigned threadId);
RGB		Cast(LumiBox& lb, Ray& r, unsigned depth);
bool	Trace(ShapeList& shpl, Ray& r, Info &info);

Vector	reflect(const Vector& incident, const Vector& normal);

RGB		Phong(LumiBox& lb, Ray& r, Info& info);
RGB		Reflection(LumiBox& lb, Ray& r, Info& info, unsigned depth);
RGB		Refraction(LumiBox& lb, Ray& r, Info& info, unsigned depth);

struct ReFracTools
{
	double		ior, kr;
	Vector		vbias;
	bool		isOutside;
	unsigned	depth;
};
