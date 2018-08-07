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

#include "Matrix.hpp"

// Built according to this link :
// https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html

class Bmp
{
	Bmp(Bmp&) = delete;

	/*struct	FileHeader
	{
		uint16_t	Type;
		uint32_t	Size;
		uint16_t	Reserved1;
		uint16_t	Reserved2;
		uint32_t	OffBits;
	}	FHeader;*/

	uint8_t		FHeader[14];

	struct	InfoHeader
	{
		uint32_t	Size;
		uint32_t	Width;
		uint32_t	Height;
		uint16_t	Planes;
		uint16_t	BitCount;
		uint32_t	Compression;
		uint32_t	SizeImage;
		uint32_t	XPelsPerMeter;
		uint32_t	YPelsPerMeter;
		uint32_t	ClrUsed;
		uint32_t	ClrImportant;
	}	IHeader;
	
	std::unique_ptr<uint8_t>	Data;

public:
	Bmp();
	~Bmp() = default;

	void	InitHeader(uint32_t width, uint32_t height);
	void	Save(const char* path);
	void	PutPixel(const uVec2 coord, const RGB clr);

	//static std::string	SavePath;
};
