#pragma once
#include <chrono>
#include <iostream>
#include "globalVars.h"
#include <string>
#include <stdlib.h>
#include <filesystem>

void cleanSource(int argc, char* argv[])
{
	using namespace std::filesystem;

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-postclean" && freshSource == false)
		{
			//Starts the removal of the source directory
			auto start5 = std::chrono::steady_clock::now();
			std::cout << "\nStarting clean-up process, please do not close the program or press any buttons.\n";

			std::string rmdirString = "rmdir /s /q \"" + sourcePath + "\"";
			system(rmdirString.c_str());

			//Loop ensures that the program does not continue until source is deleted
			bool sourceDeleted = false;
			while (sourceDeleted == false)
			{
				if (!exists(sourcePath))
				{
					sourceDeleted = true;
				}
			}
			//Creates the source directory again
			create_directory(sourcePath);

			//Last clock ends
			auto end5 = std::chrono::steady_clock::now();
			auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
			std::cout << "Clean-up and rebuild finished in " << float(duration5.count() / 1000.00) << " seconds.\n";
		}
		else if (std::string(argv[i]) == "-postclean" && freshSource == true)
		{
			std::cout << "\nSkipping post-clean as the source was freshly built\n";
		}
	}
}