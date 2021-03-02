#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "programWideVars.h"
#include "fillSourceArray.h"
#include "FileHandler.h"

//Void for sorting files
void sortFiles(std::vector<std::string> fileFullPath, std::vector<std::string> fileFileNames, std::string fileType, int currentMaxPic, int picCount, int type);

int totalSorts = 0;

void sortAll(std::vector<FileHandler> fileHandlers)
{
	
	for (int i = 0; i < DIF_FILE_TYPES; i++) {
		if (fileHandlers.at(i).count > 0) {
			sortFiles(fileHandlers.at(i).fullPath, fileHandlers.at(i).fileNames, fileHandlers.at(i).fileType, fileHandlers.at(i).currentMax + 1, fileHandlers.at(i).count, fileHandlers.at(i).container);
		}
	}
}

void sortFiles(std::vector<std::string> fileFullPath, std::vector<std::string> fileFileNames, std::string fileType, int currentMax, int count, int type)
{
	//Type usage;
	// 0 - pictures
	// 1 - videos
	// 2 - documents
	// 3 - music/audio

	//Stores the current <type> log in a string so it can be
	//appended instead of overwritten
	std::ifstream inLogFile(logsPath + fileType + "_log.txt");
	std::string logFileStore((std::istreambuf_iterator<char>(inLogFile)), (std::istreambuf_iterator<char>()));
	inLogFile.close();

	//Differentiation between array index and current max number
	//Use h for referencing the array(s).
	int h = 0;
	std::cout << "Sorted 0 " << fileType << "s.";
	for (int i = currentMax; i < (currentMax + count); i++, h++)
	{
		//Creates two directories to be used in copying
		std::string sourceDir = fileFullPath.at(h);
		std::string fileTypeUpper = boost::to_upper_copy<std::string>(fileType);

		std::string destDir;
		switch (type)
		{
		case 0:
			destDir = basePath + "Documents/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;	
			break;
		case 1:
			destDir = basePath + "Audio/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		case 2:
			destDir = basePath + "Pictures/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		case 3:
			destDir = basePath + "Videos/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		}

		//The input file
		std::ifstream src(sourceDir, std::ios::binary);
		//The output file
		std::ofstream dst(destDir, std::ios::binary);

		//Copies input to output
		dst << src.rdbuf();

		//Precaution to avoid mem overflow
		dst.close();
		src.close();

		logFileStore += fileFileNames.at(h) + " was renamed to " + fileTypeUpper + std::to_string(i) + "\n";
		totalSorts++;
		std::cout << "\rSorted " << h + 1 << " " << fileType << "s. " << "(" << totalSorts << " total)";
	}

	//Rewrites log file
	std::ofstream outLogFile(logsPath + fileType + "_log.txt");
	outLogFile << logFileStore;
	outLogFile.close();
	std::cout << "\n";
}