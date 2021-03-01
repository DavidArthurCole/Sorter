//Include statments
#include <iostream>
#include <string>
#include <chrono>
#include <io.h>
#include <C:/Users/david/Documents/SDKS/boost_1_75_0/boost/filesystem.hpp>
#include <C:/Users/david/Documents/SDKS/boost_1_75_0/boost/filesystem/path.hpp>

//Custom header files
#include "sortAll.h"
#include "buildFileStructure.h"
#include "cleanSource.h"
#include "getFolderSize.h"

//Class for holding filetype pieces
#include "FileHandler.h"

int main(int argc, char* argv[])
{
	//Will build the folder structure that the program uses
	buildFileStructure();

	//Creates an empty vector for file handlers
	std::vector<FileHandler> fileHandlers;

	for (int i = 0; i < DIF_FILE_TYPES; i++) {
		fileHandlers.push_back(FileHandler(allFileTypes->at(i), allFileTypesContainers->at(i)));
	}

	//Timer started
	auto start = std::chrono::steady_clock::now();

	// Will calculate (if any files already exist) what the max numerical value is
	// so the program can rename accordingly
	//getCurrentMaxes(argc, argv);

	//Timer ended
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Calculated file maxes in " << float(duration.count() / 1000.00) << " seconds.\n";

	//New timer started
	auto start2 = std::chrono::steady_clock::now();

	//Adds files into arrays to be sorted
	fillSourceArray(fileHandlers);
	sortArrays(fileHandlers);

	//Timer ended
	auto end2 = std::chrono::steady_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
	std::cout << "Added " << sourcePathCount << " files to internal array " << float(duration2.count() / 1000.00) << " seconds.\n";

	//New timer started
	auto start5 = std::chrono::steady_clock::now();

	//Calculates size of the source folder
	getFolderSize(sourceSize, sourcePath);
	double sourceSizeDouble = static_cast<double>(sourceSize);
	std::cout << "Source folder contains " << ((double)(int)((sourceSizeDouble / 1000000000) * 100) / 100 ) << " GB of data\n";

	//Timer ended
	auto end5 = std::chrono::steady_clock::now();
	auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
	std::cout << "Calculated source folder size in " << float(duration5.count() / 1000.00) << " seconds.\n";

	//New timer started
	auto start3 = std::chrono::steady_clock::now();

	//Sorts all files (including folders)
	sortAll(fileHandlers);
	//Timer ended
	auto end3 = std::chrono::steady_clock::now();
	auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
	std::cout << "Sorted " << sourcePathCount << " files/folders in " << float(duration3.count() / 1000.00) << " seconds.\n";
	
	//Total timer ended
	auto end4 = std::chrono::steady_clock::now();
	auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(end4 - start);
	std::cout << "Sorting program completed in " << float(duration4.count() / 1000.00) << " seconds.\n";

	cleanSource(argc, argv);

	//Exit sequence
	std::cout << "\nPress any key to exit...";
	std::getchar();
}