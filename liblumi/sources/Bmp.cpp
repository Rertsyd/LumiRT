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
	memset(Data.get(), 0x00u, IHeader.SizeImage);

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
	std::ofstream ofs(path, std::ios::binary);
	ofs.write(reinterpret_cast<char*>(FHeader), sizeof(FHeader));
	ofs.write(reinterpret_cast<char*>(&IHeader), sizeof(InfoHeader));

	const uint32_t	bytesPerPixel = IHeader.BitCount / 8u;
	const uint32_t	sizeLine = IHeader.Width * bytesPerPixel;

	const uint32_t	padding = (4u - ((3u * IHeader.Width) % 4u)) % 4u;
	const char paddingData[4] = { 0x00, 0x00, 0x00, 0x00 };

	for (uint32_t i = 0; i < IHeader.Height; ++i)
	{
		const uint8_t* ptr = &(Data.get()[(sizeLine * (IHeader.Height - i - 1u))]);

		ofs.write(reinterpret_cast<const char*>(ptr), sizeof(uint8_t) * sizeLine);
		ofs.write(paddingData, padding);
	}

	ofs.close();
}

void	Bmp::PutPixel(const uVec2 coord, const RGBColor clr) const
{
	const uint32_t	bytesPerPixel = IHeader.BitCount / 8u;
	const uint32_t	sizeLine = IHeader.Width * bytesPerPixel;

	const uint32_t	id = ((coord.y * sizeLine) + coord.x * bytesPerPixel);
	
	Data.get()[id + 2] = (clr.red >= 255.) ? 255u : static_cast<uint8_t>(clr.red);
	Data.get()[id + 1] = (clr.green >= 255.) ? 255u : static_cast<uint8_t>(clr.green);
	Data.get()[id] = (clr.blue >= 255.) ? 255u : static_cast<uint8_t>(clr.blue);
}
