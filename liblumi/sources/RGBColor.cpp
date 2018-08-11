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

#include "RGBColor.hpp"

RGBColor::RGBColor() : red(0.), green(0.), blue(0.)
{}

RGBColor::RGBColor(const RGBColor& rgb)
{
	*this = rgb;
}

RGBColor::RGBColor(double r, double g, double b) : red(r), green(g), blue(b)
{}

RGBColor&	RGBColor::operator=(const RGBColor& c)
{
	red = c.red;
	green = c.green;
	blue = c.blue;
	return *this;
}

/* *********************************** */

RGBColor	RGBColor::operator/(const double d) const
{
	return RGBColor(red / d, green / d, blue / d);
}

/* *********************************** */

RGBColor	RGBColor::operator*(const RGBColor& c) const
{
	return RGBColor(red * c.red, green * c.green, blue * c.blue);
}

RGBColor	RGBColor::operator*(const double d) const
{
	return RGBColor(red * d, green * d, blue * d);
}

RGBColor&	RGBColor::operator*=(const RGBColor& c)
{
	red *= c.red;
	green *= c.green;
	blue *= c.blue;
	return *this;
}

RGBColor&	RGBColor::operator*=(const double d)
{
	red *= d;
	green *= d;
	blue *= d;
	return *this;
}

/* *********************************** */

RGBColor	RGBColor::operator+(const RGBColor& c) const
{
	return RGBColor(red + c.red, green + c.green, blue + c.blue);
}

RGBColor	RGBColor::operator+(const double d) const
{
	return RGBColor(red + d, green + d, blue + d);
}

RGBColor&	RGBColor::operator+=(const RGBColor& c)
{
	red += c.red;
	green += c.green;
	blue += c.blue;
	return *this;
}

RGBColor&	RGBColor::operator+=(const double d)
{
	red += d;
	green += d;
	blue += d;
	return *this;
}

/* *********************************** */

RGBColor	RGBColor::operator-(const RGBColor& c) const
{
	return RGBColor(red - c.red, green - c.green, blue - c.blue);
}

RGBColor	RGBColor::operator-(const double d) const
{
	return RGBColor(red - d, green - d, blue - d);
}

RGBColor&	RGBColor::operator-=(const RGBColor& c)
{
	red -= c.red;
	green -= c.green;
	blue -= c.blue;
	return *this;
}

RGBColor&	RGBColor::operator-=(const double d)
{
	red -= d;
	green -= d;
	blue -= d;
	return *this;
}

RGBColor&	RGBColor::Normalize()
{
	(red > 1.) ? (red) = 1. : 0.;
	(red < 0.) ? (red) = 0. : 0.;
	(green > 1.) ? (green) = 1. : 0.;
	(green < 0.) ? (green) = 0. : 0.;
	(blue > 1.) ? (blue) = 1. : 0.;
	(blue < 0.) ? (blue) = 0. : 0.;

	return *this;
}
