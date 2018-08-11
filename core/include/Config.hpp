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

#include "Shape.hpp"

class Config
{
	Config() = delete;
	Config(Config&) = delete;
	~Config() = delete;

public:
	static unsigned	Width, Height;

	static unsigned	NbThread;
	static unsigned	AntiAliasing;
	static double	Bias;
	
	static RGBColor	Ambient;
};

struct LumiBox
{
	LumiBox();
	~LumiBox() = default;

	Bmp			Img;
	Camera		Cam;
	ShapeList	ShpList;
	LightList	LgtList;
	MatList		MatList;
};

struct Info
{
	Info();
	~Info() = default;

	HitPoint		HP;
	double			Distance;
	const Shape*	Object;

	void	Reset();
	void	AddBias();
};
