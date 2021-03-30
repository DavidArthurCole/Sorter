//Include statments
#include <iostream>
#include <string>
#include <chrono>

//Custom header files
#include "sortAll.h"
#include "sortArrays.h"
#include "buildFileStructure.h"
#include "buildFileHandlersVector.h"
#include "cleanSource.h"
#include "getFolderSize.h"
#include "fileHandler.h"
#include "handleFlags.h"

int main(int argc, char* argv[])
{
	//Will handle any input flags
	handleFlags(argc, argv);

	//Will build the folder structure that the program uses
	buildFileStructure();

	//Fills the fileHandlers vector with new instances
	buildFileHandlersVector();

	//Adds files into arrays to be sorted
	fillSourceArray(sourcePath);
	sortArrays();

	//Calculates size of the source folder
	//getFolderSize();

	//Sorts all files (including folders)
	sortAll();

	//Cleans source if the flag was passed
	cleanSource();

	//Exit sequence
	std::cout << "\nPress any key to exit...";
	char storeExitChar = getchar();
}