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

#include "Ray.hpp"

unsigned Ray::MaxDepth = 5u;

Ray::Ray() : Type(Primary), Origin(), Direction()
{}

void	Ray::SetDir(Camera& cam, const uVec2 pxCoord, const uVec2 res)
{
	const Vec2	indent = {
		cam.ViewPlane.Width / res.x,
		cam.ViewPlane.Height / res.y
	};

	const Vector	vRight = cam.Right * indent.x;
	const Vector	vUp = cam.Up * indent.y;

	Direction =	(cam.ViewPlane.UpLeft +
		vRight * pxCoord.x -
		vUp * pxCoord.y - cam.Position).Normalize();
};
