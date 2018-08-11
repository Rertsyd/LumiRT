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

#include "Config.hpp"

unsigned Config::Width = 1920u;
unsigned Config::Height = 1080u;
unsigned Config::NbThread = 4u;
unsigned Config::AntiAliasing = 2u;
double Config::Bias = 0.001;
RGBColor Config::Ambient = { 0.12, 0.12, 0.12 };

/* ************** */

LumiBox::LumiBox() : Cam(), MatList(), ShpList()
{}

/* ************** */

Info::Info() :
	HP(), Distance(std::numeric_limits<double>::max()), Object(nullptr)
{}

void	Info::Reset()
{
	HP.Intersection = Vector();
	HP.Normal = Vector();
	HP.Albedo = RGBColor();
	Distance = std::numeric_limits<double>::max();
	Object = nullptr;
}

void	Info::AddBias()
{
	HP.Intersection += HP.Normal * Config::Bias;
}
