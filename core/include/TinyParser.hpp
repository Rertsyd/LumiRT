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

#include <iostream>
#include "tinyxml2.h"
#include "Config.hpp"

using namespace tinyxml2;

class TinyParser
{
	TinyParser() = delete;
	TinyParser(TinyParser&) = delete;
	~TinyParser() = delete;

public:
	static XMLNode*	Root;

	static void	ReadConfig(Camera& cam);
	static void	ReadMaterials(MatList& list);
	static void	ReadScene(std::string file, LumiBox& lb);

	static void	GetVector(std::string n, Vector& v);
	static void	GetColor(std::string n, RGB& c);

	static void	GetNormal(Vector& v);
	static void	GetRotation(Plane& p);

	static void	GetCamera(Camera& cam);
	static void	GetPlane(ShapeList& list, MatList& mlist);
	static void	GetSphere(ShapeList& list, MatList& mlist);
	static void	GetPoint(LightList& list);
	static void	GetDirectional(LightList& list);
	static const uPtrMaterial& GetMaterial(std::string mName, MatList& mlist);
};
