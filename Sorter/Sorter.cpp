//Include statments
#include <chrono>

//Custom header files
#include "sortAll.h"
#include "sortArrays.h"
#include "buildFileStructure.h"
#include "cleanSource.h"
#include "getFolderSize.h"
#include "fileHandler.h"
#include "getFileName.h"

int main(int argc, char* argv[])
{
	//Will handle any input flags
	for (int i = 0; i < argc; i++) {
		if (argv[i] == "-postclean") postClean = true;
	}

	//Will build the folder structure that the program uses
	buildFileStructure();

	//Fills the vector with FileHandlers of each supported type
	for (int i = 0; i < DIF_FILE_TYPES; i++) {
		fileHandlers.push_back(fileHandler(allFileTypes->at(i), allFileTypesContainers->at(i), basePath));
	}

	//Adds files into arrays to be sorted
	fillSourceArray(sourcePath);

	sortArrays();

	//Calculates size of the source folder
	getFolderSize();

	//Sorts all files (including folders)
	sortAll();

	//Cleans source if the flag was passed
	cleanSource();

	//Exit sequence
	std::cout << "\nPress any key to exit...";
	char storeExitChar = getchar();
}