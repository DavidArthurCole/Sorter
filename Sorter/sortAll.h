#pragma once
#include <thread>
#include <mutex>

#include "globalVars.h"
#include "fillSourceArray.h"
#include "FileHandler.h"
#include "getFileName.h"
#include "duplicateDetector.h"
#include "copyFile.h"

std::mutex mtx;

void sort(fileHandler fileHandler) {

	//If there are files of that type, sort them
	if (fileHandler.count > 0) {
		//Iterates through the files
		for (int i = 0; i < (fileHandler.count); i++)
		{
			//Grabs the file's name
			std::string fileName = getFileName(fileHandler.fileNames.at(i), fileHandler.fileType);
			//Creates a path for the file
			std::string checkPath = fileHandler.pathAppendFileType + fileHandler.fileType + "/" + fileName + "." + fileHandler.fileType;
			//Creates the alternate path, incase a file with the same name exists
			std::string alternatePath = fileHandler.pathAppendFileType + fileHandler.fileType + "/" + fileName + " (%FILL_INT_HERE%)" + "." + fileHandler.fileType;
			//Function will decide what the file is named
			std::string newPath = duplicateDetector(checkPath, alternatePath);
			
			copyFile(fileHandler.fullPath.at(i), newPath);

			totalSorts++;

			//So that multiple threads dlo not overlap their outputs
			mtx.lock();
			std::cout << "\r\rSorting... (" << std::to_string(totalSorts) << " / " << std::to_string(sourcePathCount) << ")";
			mtx.unlock();
		}
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
	std::cout << "\nSorted " << sourcePathCount << " files/folders in " << float(durationSortAll.count() / 1000.00) << " seconds.\n";
}