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

#include "RGB.hpp"

RGB::RGB() : red(0.), green(0.), blue(0.)
{}

RGB::RGB(double r, double g, double b) :
	red(r), green(g), blue(b)
{}

RGB&	RGB::operator=(const RGB& c)
{
	red = c.red;
	green = c.green;
	blue = c.blue;
	return *this;
}

/* *********************************** */

/*RGB	RGB::operator/(const RGB& c) const
{
	return RGB(red * c.red, green * c.green, blue * c.blue);
}*/

RGB	RGB::operator/(const double d) const
{
	return RGB(red / d, green / d, blue / d);
}

/* *********************************** */

RGB	RGB::operator*(const RGB& c) const
{
	return RGB(red * c.red, green * c.green, blue * c.blue);
}

RGB	RGB::operator*(const double d) const
{
	return RGB(red * d, green * d, blue * d);
}

RGB&	RGB::operator*=(const RGB& c)
{
	red *= c.red;
	green *= c.green;
	blue *= c.blue;
	return *this;
}

RGB&	RGB::operator*=(const double d)
{
	red *= d;
	green *= d;
	blue *= d;
	return *this;
}

/* *********************************** */

RGB	RGB::operator+(const RGB& c) const
{
	return RGB(red + c.red, green + c.green, blue + c.blue);
}

RGB	RGB::operator+(const double d) const
{
	return RGB(red + d, green + d, blue + d);
}

RGB&	RGB::operator+=(const RGB& c)
{
	red += c.red;
	green += c.green;
	blue += c.blue;
	return *this;
}

RGB&	RGB::operator+=(const double d)
{
	red += d;
	green += d;
	blue += d;
	return *this;
}

/* *********************************** */

RGB	RGB::operator-(const RGB& c) const
{
	return RGB(red - c.red, green - c.green, blue - c.blue);
}

RGB	RGB::operator-(const double d) const
{
	return RGB(red - d, green - d, blue - d);
}

RGB&	RGB::operator-=(const RGB& c)
{
	red -= c.red;
	green -= c.green;
	blue -= c.blue;
	return *this;
}

RGB&	RGB::operator-=(const double d)
{
	red -= d;
	green -= d;
	blue -= d;
	return *this;
}

RGB&	RGB::Normalize()
{
	(red > 1.) ? (red) = 1. : 0;
	(red < 0.) ? (red) = 0. : 0;
	(green > 1.) ? (green) = 1. : 0;
	(green < 0.) ? (green) = 0. : 0;
	(blue > 1.) ? (blue) = 1. : 0;
	(blue < 0.) ? (blue) = 0. : 0;

	return *this;
}