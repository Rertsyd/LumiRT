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
static constexpr double Pi = 3.14159265359;
static constexpr double Rad = Pi / 180.;

struct RGB
{	
	RGB();
	RGB(double r, double g, double b);
	~RGB() = default;

	double	red, green, blue;

	RGB&	operator=(const RGB& c);

	RGB	operator/(const double d) const;

	RGB	operator*(const RGB& c) const;
	RGB	operator*(const double d) const;
	RGB&	operator*=(const RGB& c);
	RGB&	operator*=(const double d);

	RGB	operator+(const RGB& c) const;
	RGB	operator+(const double d) const;
	RGB&	operator+=(const RGB& c);
	RGB&	operator+=(const double d);

	RGB	operator-(const RGB& c) const;
	RGB	operator-(const double d) const;
	RGB&	operator-=(const RGB& c);
	RGB&	operator-=(const double d);
	RGB&	Normalize();
};
