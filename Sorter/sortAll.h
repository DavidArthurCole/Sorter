#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "globalVars.h"
#include "fillSourceArray.h"
#include "FileHandler.h"

void sortAll()
{
	//Timer
	auto startSortAll = std::chrono::steady_clock::now();

	//For all different file types
	for (fileHandler fileHandler : fileHandlers) {
		//If there are files of that type, sort them
		if (fileHandler.count > 0) {
			//Stores the current <type> log in a string so it can be appended instead of overwritten
			std::ifstream inLogFile(logsPath + fileHandler.fileType + "_log.txt");
			std::string logFileStore((std::istreambuf_iterator<char>(inLogFile)), (std::istreambuf_iterator<char>()));
			inLogFile.close();

			//Differentiation between array index and current max number
			//Use h for referencing the array(s).
			int h = 0;
			std::cout << "Sorted 0 " << fileHandler.fileType << "s.";
			for (int i = fileHandler.currentMax; i < (fileHandler.currentMax + fileHandler.count); i++, h++)
			{
				//The input file
				std::ifstream src(fileHandler.fullPath.at(h), std::ios::binary);
				//The output file
				std::ofstream dst(fileHandler.pathAppendFileType + fileHandler.fileType + "/" + fileHandler.fileType + std::to_string(i) + "." + fileHandler.fileType, std::ios::binary);

				//Copies input to output
				dst << src.rdbuf();

				//Precaution to avoid mem overflow
				dst.close();
				src.close();

				logFileStore += fileHandler.fileNames.at(h) + " was renamed to " + fileHandler.fileType + std::to_string(i) + "\n";
				totalSorts++;
				std::cout << "\rSorted " << h + 1 << " " << fileHandler.fileType << "s. " << "(" << totalSorts << " total)";
			}

			//Rewrites log file
			std::ofstream outLogFile(logsPath + fileHandler.fileType + "_log.txt");
			outLogFile << logFileStore;
			outLogFile.close();
			std::cout << "\n";
		}
	}

	//Timer ended
	auto durationSortAll = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startSortAll);
	std::cout << "Sorted " << sourcePathCount << " files/folders in " << float(durationSortAll.count() / 1000.00) << " seconds.\n";
}