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

#include <functional>
#include <sstream>
#include <map>

#include "TinyParser.hpp"

XMLNode* TinyParser::Root = nullptr;

static void	trim(std::string& str)
{
	static const std::function<bool(int)>
		IsWhiteSpace = [](int c) -> bool { return !std::isspace(c); };

	str.erase(str.begin(), std::find_if(str.begin(), str.end(), IsWhiteSpace));
	str.erase(str.find_last_not_of(" \t\n") + 1);
}

static void split(std::string& str, std::vector<double>& v)
{
	std::stringstream	ss(str);

	for (std::string s = ""; std::getline(ss, s, ' ');)
		v.push_back(std::stod(s));
}

void	TinyParser::ReadConfig(Camera& cam)
{
	XMLDocument conf;
	conf.LoadFile("config.xml");

	Root = conf.FirstChild()->FirstChildElement("config");

	XMLElement* pXml = Root->FirstChildElement("resolution");
	pXml->FirstChildElement("width")->QueryUnsignedText(&Config::Width);
	pXml->FirstChildElement("height")->QueryUnsignedText(&Config::Height);

	Root->FirstChildElement("nb_thread")->QueryUnsignedText(&Config::NbThread);
	Root->FirstChildElement("antialiasing")->QueryUnsignedText(&Config::AntiAliasing);
	
	Root->FirstChildElement("ray_depth")->QueryUnsignedText(&Ray::MaxDepth);
	Root->FirstChildElement("bias")->QueryDoubleText(&Config::Bias);

	GetColor("ambient", Config::Ambient);

	pXml = Root->FirstChildElement("viewplane");
	pXml->FirstChildElement("width")->QueryDoubleText(&cam.ViewPlane.Width);
	pXml->FirstChildElement("height")->QueryDoubleText(&cam.ViewPlane.Height);
	pXml->FirstChildElement("distance")->QueryDoubleText(&cam.ViewPlane.Distance);

	Material::Path = Root->FirstChildElement("materials")->GetText();
	trim(Material::Path);
}

void	TinyParser::ReadMaterials(MatList& list)
{
	static const std::map<std::string, Material::Types> mapMaterialTypes
	{{
		{ "phong", Material::Types::Phong },
		{ "reflection", Material::Types::Reflection },
		{ "refraction", Material::Types::Refraction }
	}};

	XMLDocument file;
	file.LoadFile(Material::Path.c_str());

	Root = file.FirstChild()->FirstChildElement("materials")->FirstChild();
	
	for (uPtrMaterial mat; Root; (Root = Root->NextSibling()))
	{
		mat.reset(new Material);
		mat->Name = Root->Value();
		std::string str(Root->FirstChildElement("type")->GetText());
		trim(str);
		mat->Type = mapMaterialTypes.at(str);

		GetColor("albedo", mat->Albedo);

		if (mat->Type == Material::Types::Phong)
		{
			Root->FirstChildElement("kdiffuse")->QueryDoubleText(&mat->kDiffuse);
			Root->FirstChildElement("kspecular")->QueryDoubleText(&mat->kSpecular);
			Root->FirstChildElement("ks_exp")->QueryDoubleText(&mat->ksExp);
		}
		else
		{
			Root->FirstChildElement("kreflection")->QueryDoubleText(&mat->kReflection);
			if (mat->Type == Material::Types::Refraction)
			{
				Root->FirstChildElement("krefraction")->QueryDoubleText(&mat->kRefraction);
				Root->FirstChildElement("transparency")->QueryDoubleText(&mat->Transparency);
			}
		}

		list.push_back(std::move(mat));
	}
}

void	TinyParser::ReadScene(std::string file, LumiBox& lb)
{
	XMLDocument scene;
	scene.LoadFile(file.c_str());

	Root = scene.FirstChild()->FirstChildElement("camera");
	GetCamera(lb.Cam);

	XMLNode* tmp = Root = scene.FirstChild()->FirstChildElement("scene");

	for (auto objsPtr = Root->FirstChildElement("objects")->FirstChild();
		objsPtr; (objsPtr = objsPtr->NextSibling()))
	{
		Root = objsPtr;
		if (std::string str(objsPtr->Value()); str == "plane")
		{
			GetPlane(lb.ShpList, lb.MatList);
		}
		else if (str == "sphere")
		{
			GetSphere(lb.ShpList, lb.MatList);
		}
	}

	Root = tmp;
	for (auto lightsPtr = Root->FirstChildElement("lights")->FirstChild();
		lightsPtr; (lightsPtr = lightsPtr->NextSibling()))
	{
		Root = lightsPtr;
		if (std::string str(lightsPtr->Value()); str == "point")
		{
			GetPoint(lb.LgtList);
		}
		else if (str == "directional")
		{
			GetDirectional(lb.LgtList);
		}
	}
}

void	TinyParser::GetVector(std::string name, Vector& vec)
{
	std::string	str(Root->FirstChildElement(name.c_str())->GetText());
	std::vector<double> v;
	trim(str);
	split(str, v);
	vec.x = v.at(0);
	vec.y = v.at(1);
	vec.z = v.at(2);
}

void	TinyParser::GetColor(std::string name, RGBColor& clr)
{
	std::string	str(Root->FirstChildElement(name.c_str())->GetText());
	std::vector<double> v;
	trim(str);
	split(str, v);
	clr.red = v.at(0);
	clr.green = v.at(1);
	clr.blue = v.at(2);
}

void	TinyParser::GetCamera(Camera& cam)
{
	GetVector("position", cam.Position);
	GetVector("look_at", cam.LookAt);
}

void	TinyParser::GetNormal(Vector& v)
{
	GetVector("normal", v);
	v.Normalize();
}

void	TinyParser::GetRotation(Plane& p)
{
	GetVector("rotation", p.Rotation);

	Matrix	mRotate;
	mRotate.InitRotation(p.Rotation);
	p.Normal = mRotate * p.Normal;
}

void	TinyParser::GetPlane(ShapeList& list, MatList& mlist)
{
	Vector pos;
	GetVector("position", pos);

	std::string mName = Root->FirstChildElement("material")->GetText();
	trim(mName);

	Plane p(pos, GetMaterial(mName, mlist));
	GetNormal(p.Normal);

	if (auto ptr = Root->FirstChildElement("rotation"); ptr)
		GetRotation(p);

	list.push_back(std::move(uPtrShape(new Plane(p))));
}

void	TinyParser::GetSphere(ShapeList& list, MatList& mlist)
{
	Vector pos;
	GetVector("position", pos);
	
	std::string mName = Root->FirstChildElement("material")->GetText();
	trim(mName);

	Sphere s(pos, GetMaterial(mName, mlist));
	Root->FirstChildElement("radius")->QueryDoubleText(&s.Radius);

	list.push_back(std::move(uPtrShape(new Sphere(s))));
}

void	TinyParser::GetPoint(LightList& list)
{
	Vector pos;
	GetVector("position", pos);

	RGBColor clr;
	GetColor("color", clr);

	double it = 75.;
	if (auto ptr = Root->FirstChildElement("intensity"); ptr)
		ptr->QueryDoubleText(&it);

	list.push_back(std::move(uPtrLight(new Point(clr, it, pos))));
}

void	TinyParser::GetDirectional(LightList& list)
{
	Vector dir;
	GetVector("direction", dir);
	dir.Normalize();

	RGBColor clr;
	GetColor("color", clr);

	double it = 75.;
	if (auto ptr = Root->FirstChildElement("intensity"); ptr)
		ptr->QueryDoubleText(&it);

	list.push_back(std::move(uPtrLight(new Directional(clr, it, dir))));
}

const uPtrMaterial&	TinyParser::GetMaterial(std::string mName, MatList& mlist)
{
	auto it = mlist.begin();
	for (; it != mlist.end(); ++it)
		if ((*it)->Name == mName) break;
	return *it;
}
