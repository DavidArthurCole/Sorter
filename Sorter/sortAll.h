#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "globalVars.h"
#include "fillSourceArray.h"
#include "FileHandler.h"

//Void for sorting files
void sortFiles(FileHandler fileHandler);

int totalSorts = 0;

void sortAll(std::vector<FileHandler> fileHandlers)
{
	//For all different file types
	for (int i = 0; i < DIF_FILE_TYPES; i++) {
		//Creates a new editable fileHandler instance
		FileHandler fileHandler = fileHandlers.at(i);
		//If there are files of that type, sort them
		if (fileHandler.count > 0) {
			sortFiles(fileHandler);
		}
		//Sets the fileHandler in the vector to the changed one
		fileHandlers.at(i) = fileHandler;
	}
}

void sortFiles(FileHandler fileHandler)
{
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

		//Creates two directories to be used in copying
		std::string sourceDir = fileHandler.fullPath.at(h);
		std::string destDir = fileHandler.pathAppendFileType + fileHandler.fileType + "/" + fileHandler.fileType + std::to_string(i) + "." + fileHandler.fileType;;

		//The input file
		std::ifstream src(sourceDir, std::ios::binary);
		//The output file
		std::ofstream dst(destDir, std::ios::binary);

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