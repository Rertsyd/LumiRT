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

#include <vector>
#include "Ray.hpp"

struct Material
{
	enum Types
	{
		Phong = 0,
		Reflection,
		Refraction
	};

	Material();
	~Material() = default;

	std::string	Name;

	Types		Type;
	RGBColor	Albedo;
	double		kDiffuse;
	double		kSpecular;
	double		ksExp;
	double		kReflection;
	double		kRefraction;
	double		Transparency;

	static std::string	Path;
};

using uPtrMaterial = std::unique_ptr<Material>;
using MatList = std::vector<uPtrMaterial>;
