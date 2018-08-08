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

//std::string Bmp::SavePath = "./out/";

Bmp::Bmp() : FHeader(), IHeader(), Data(nullptr)
{
	memset(&FHeader, 0u, sizeof(FHeader));
	memset(&IHeader, 0u, sizeof(InfoHeader));
}

void	Bmp::InitHeader(uint32_t width, uint32_t height)
{
	IHeader.Size = 40u;
	IHeader.Width = width;
	IHeader.Height = height;
	IHeader.Planes = 1u;
	IHeader.BitCount = 24u;
	IHeader.SizeImage = width * height * IHeader.BitCount / 8u;

	Data.reset(new uint8_t[IHeader.SizeImage]);
	memset(Data.get(), 0x80u, IHeader.SizeImage);

	// 'BM'
	FHeader[0] = static_cast<uint8_t>(0x42u);
	FHeader[1] = static_cast<uint8_t>(0x4Du);
	// OffBits
	FHeader[10] = static_cast<uint8_t>(0x36u);
	// Size
	const uint32_t sz = IHeader.SizeImage + FHeader[10];
	FHeader[2] = static_cast<uint8_t>(sz);
	FHeader[3] = static_cast<uint8_t>(sz >> 8u);
	FHeader[4] = static_cast<uint8_t>(sz >> 16u);
	FHeader[5] = static_cast<uint8_t>(sz >> 24u);
}

void	Bmp::Save(const char* path)
{
	std::ofstream ofs(path);
	ofs.write(reinterpret_cast<char*>(FHeader), sizeof(FHeader));
	ofs.write(reinterpret_cast<char*>(&IHeader), sizeof(InfoHeader));
	ofs.write(reinterpret_cast<char*>(Data.get()), IHeader.SizeImage);
	ofs.close();
}

void	Bmp::PutPixel(const uVec2 coord, const RGB clr)
{
	static const uint32_t	bytesPerPixel = IHeader.BitCount / 8u;
	static const uint32_t	sizeLine = IHeader.Width * bytesPerPixel;

	const uint32_t	id =
		IHeader.SizeImage - ((coord.y * sizeLine) + coord.x * bytesPerPixel) -1u;

	Data.get()[id] = static_cast<unsigned>(std::clamp(clr.red, 0., 255.));
	Data.get()[id - 1] = static_cast<unsigned>(std::clamp(clr.green, 0., 255.));
	Data.get()[id - 2] = static_cast<unsigned>(std::clamp(clr.blue, 0., 255.));
}
