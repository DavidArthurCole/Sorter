#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "globalVars.h"
#include "fillSourceArray.h"
#include "FileHandler.h"
#include "getFileName.h"

void sort(fileHandler fileHandler) {

	//If there are files of that type, sort them
	if (fileHandler.count > 0) {
		//Initial print
		std::cout << "Starting to sort " << fileHandler.count << " " << fileHandler.fileType << "s.\n";
		for (int i = 0; i < (fileHandler.count); i++)
		{	
			//The input file
			std::ifstream src(fileHandler.fullPath.at(i), std::ios::binary);

			std::string fileName = getFileName(fileHandler.fileNames.at(i), fileHandler.fileType);
			std::string checkPath = fileHandler.pathAppendFileType + fileHandler.fileType + "/" + fileName + "." + fileHandler.fileType;
			std::string newName = "";

			boolean renamed = false;
			int holdJ = 0;

			if (!std::filesystem::exists(checkPath)) {
				newName = checkPath;
			}
			else {
				for (int j = 1; j < MAX_SIZE; j++) {
					std::string testPath = fileHandler.pathAppendFileType + fileHandler.fileType + "/" + fileName + " (" + std::to_string(j) + ")" + "." + fileHandler.fileType;
					if (!std::filesystem::exists(testPath)) {
						newName = testPath;
						holdJ = j;
						renamed = true;
						j = MAX_SIZE + 1;
					}
				}
			}

			//The output file
			std::ofstream dst(newName, std::ios::binary);

			//Copies input to output
			dst << src.rdbuf();

			//Precaution to avoid mem overflow
			dst.close();
			src.close();
		}
		std::cout << "Finished sorting " << fileHandler.count << " " << fileHandler.fileType << "s.\n";
	}
}

void sortAll()
{
	//Timer
	auto startSortAll = std::chrono::steady_clock::now();

	//Holds the threads for each type
	std::vector<std::thread> sorterThreads;

	//For all different file types, create a new thread
	for (fileHandler fileHandler : fileHandlers) {
		sorterThreads.push_back(std::thread(sort, fileHandler));
	}

	//Run the threads
	for (auto& thread : sorterThreads) {
		thread.join();
	}

	//Timer ended
	auto durationSortAll = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startSortAll);
	std::cout << "Sorted " << sourcePathCount << " files/folders in " << float(durationSortAll.count() / 1000.00) << " seconds.\n";
}