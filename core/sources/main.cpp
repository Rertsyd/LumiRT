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

#include <thread>
#include <exception>
#include <ctime>
#include "LumiRT.hpp"

static std::string	BuildImgTitle()
{
	const time_t raw = std::time(0);
	struct tm dt;

#ifdef _WIN32
	localtime_s(&dt, &raw);
#else
	dt = localtime(&raw);
#endif // WIN32

	char timeStr[32];

	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d_%Hh%Mm%Ss", &dt);

	return std::string("out_") + std::string(timeStr) + std::string(".bmp");
}

int		main(int ac, char** av)
{
	if (ac == 1)
		std::cerr << "LumiRT need a xml scene file." << std::endl;
	else
	{
		try
		{
			LumiBox lb;

			TinyParser::ReadConfig(lb.Cam);
			lb.Img.InitHeader(Config::Width, Config::Height);

			TinyParser::ReadMaterials(lb.MatList);
			TinyParser::ReadScene(av[1], lb);
			lb.Cam.Init();

			std::unique_ptr<std::thread>*
				tab  = new std::unique_ptr<std::thread>[Config::NbThread];
			
			for (unsigned threadId = 0u; threadId < Config::NbThread; ++threadId)
			{
				tab[threadId].reset(new std::thread(Task, std::ref(lb), threadId));
			}
			for (unsigned i = 0u; i < Config::NbThread; ++i)
			{
				tab[i]->join();
			}

			delete[] tab;

			lb.Img.Save(BuildImgTitle().c_str());
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}
	return EXIT_SUCCESS;
}
