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

#include <algorithm>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <memory>
#include <string>

static constexpr double Zero = 1e-6;
static constexpr double Pi = 3.141592653589793;
static constexpr double Rad = Pi / 180.;

struct RGBColor
{	
	RGBColor();
	RGBColor(const RGBColor& rgb);
	RGBColor(double r, double g, double b);
	~RGBColor() = default;

	double	red, green, blue;

	RGBColor&	operator=(const RGBColor& c);

	RGBColor	operator/(const double d) const;

	RGBColor	operator*(const RGBColor& c) const;
	RGBColor	operator*(const double d) const;
	RGBColor&	operator*=(const RGBColor& c);
	RGBColor&	operator*=(const double d);

	RGBColor	operator+(const RGBColor& c) const;
	RGBColor	operator+(const double d) const;
	RGBColor&	operator+=(const RGBColor& c);
	RGBColor&	operator+=(const double d);

	RGBColor	operator-(const RGBColor& c) const;
	RGBColor	operator-(const double d) const;
	RGBColor&	operator-=(const RGBColor& c);
	RGBColor&	operator-=(const double d);
	RGBColor&	Normalize();
};
