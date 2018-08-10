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

void	Task(LumiBox& lb, const unsigned threadId);
RGB		Cast(const LumiBox& lb, const Ray& r, const unsigned depth);
bool	Trace(const ShapeList& shpl, const Ray& r, Info &info);

Vector	reflect(const Vector& incident, const Vector& normal);

RGB		Phong(const LumiBox& lb, const Ray& r, Info& info);
RGB		Reflection(const LumiBox& lb, const Ray& r, Info& info, const unsigned depth);
RGB		Refraction(const LumiBox& lb, const Ray& r, Info& info, const unsigned depth);

struct ReFracTools
{
	double		ior, kr;
	Vector		vbias;
	bool		isOutside;
	unsigned	depth;
};
