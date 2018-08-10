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

#include <fstream>

#include "Bmp.hpp"

Bmp::Bmp() : FHeader(), IHeader(), Data(nullptr)
{
	memset(&FHeader, 0u, sizeof(FHeader));
	memset(&IHeader, 0u, sizeof(InfoHeader));
}

void	Bmp::InitHeader(const uint32_t width, const uint32_t height)
{
	IHeader.Size = 40u;
	IHeader.Width = width;
	IHeader.Height = height;
	IHeader.Planes = 1u;
	IHeader.BitCount = 24u;
	IHeader.SizeImage = width * height * (IHeader.BitCount / 8u);

	Data.reset(new uint8_t[IHeader.SizeImage]);
	memset(Data.get(), 0x80u, IHeader.SizeImage);

	FHeader[0] = 'B';
	FHeader[1] = 'M';

	// OffBits
	FHeader[10] = static_cast<uint8_t>(54u);

	// Size
	const uint32_t sz = IHeader.SizeImage + FHeader[10];
	FHeader[2] = sz & 0xFFu;
	FHeader[3] = (sz >> 8u) & 0xFFu;
	FHeader[4] = (sz >> 16u) & 0xFFu;
	FHeader[5] = (sz >> 24u) & 0xFFu;
}

void	Bmp::Save(const char* path)
{
	std::ofstream ofs(path);
	ofs.write(reinterpret_cast<char*>(FHeader), sizeof(FHeader));
	ofs.write(reinterpret_cast<char*>(&IHeader), sizeof(InfoHeader));
	ofs.write(reinterpret_cast<char*>(Data.get()), IHeader.SizeImage);
	ofs.close();
}

void	Bmp::PutPixel(const uVec2 coord, const RGB clr) const
{
	static const uint32_t	bytesPerPixel = IHeader.BitCount / 8u;
	static const uint32_t	sizeLine = IHeader.Width * bytesPerPixel;

	const uint32_t	id =
		IHeader.SizeImage - ((coord.y * sizeLine) + coord.x * bytesPerPixel) -1u;
	
	if (id < IHeader.SizeImage)
	{
		Data.get()[id] = static_cast<uint8_t>((clr.red >= 255.) ? 255. : clr.red);
		Data.get()[id -1] = static_cast<uint8_t>((clr.green >= 255.) ? 255. : clr.green);
		Data.get()[id -2] = static_cast<uint8_t>((clr.blue >= 255.) ? 255. : clr.blue);
	}
}
