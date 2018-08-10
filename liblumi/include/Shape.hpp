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

#include "Light.hpp"

class Shape
{
	Shape() = delete;

public:
	Shape(Vector pos, const uPtrMaterial& mat);
	virtual ~Shape() = default;

	virtual bool	Intersect(const Ray& r, HitPoint& hp) const = 0;

	Vector				Position;
	const uPtrMaterial&	MatPtr;
};

class Plane : public Shape
{
	Plane() = delete;

public:
	Plane(Vector pos, const uPtrMaterial& mat);
	virtual ~Plane() = default;

	virtual bool	Intersect(const Ray& r, HitPoint& hp) const;

	Vector	Normal;
	Vector	Rotation;
};

class Sphere : public Shape
{
	Sphere() = delete;

public:
	Sphere(Vector pos, const uPtrMaterial& mat);
	virtual ~Sphere() = default;

	virtual bool	Intersect(const Ray& r, HitPoint& hp) const;

	double	Radius;
};

using uPtrShape = std::unique_ptr<Shape>;
using ShapeList = std::vector<uPtrShape>;
