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

#include "Camera.hpp"

Camera::Camera() : Position(), Direction(), Up(), Right(), LookAt(),
	ViewPlane({ 0., 0., 0., Vector()})
{}

void	Camera::Init()
{
	Direction = (LookAt - Position).Normalize();
	Right = Vector(0., 1., 0.) * Direction;
	Up = Direction * Right;
	ViewPlane.UpLeft = 
		(Position +
		(Direction * ViewPlane.Distance) + Up * (ViewPlane.Height * 0.5)) -
		Right * (ViewPlane.Width * 0.5);
}
