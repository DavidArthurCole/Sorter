#ifndef FileHandler_HEADER
#define FileHandler_HEADER

#include <string>
#include <filesystem>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std::filesystem;

class fileHandler {

public:

	//Store the fileType (TXT, JPG, etc.)
	std::string fileType;
	//Stores the base path of the program "C:/Path/To/Executable/...(Sorter.exe)" without the executable name
	std::string basePath;
	//Essentially the same thing as fileType, but capital
	std::string pathAppendFileType;
	//Container points to which folder will contain the file type:
		// 0 is documents
		// 1 is audio
		// 2 is pictures
		// 3 is videos
	int container;
	//Current max number of the stored file
	int currentMax;
	//How many files with this type have been found
	int count;

	std::vector<std::string> fullPath{ }, fileNames{ };

	fileHandler(std::string passedFileType, int passedContainer, std::string passedBasePath, bool noMaxes) {
		//Sets the filetype
		this->fileType = passedFileType;

		//Sets the container
		this->container = passedContainer;
		switch (this->container) {
		case 0:
			this->pathAppendFileType = "Documents/";
			break;
		case 1:
			this->pathAppendFileType = "Audio/";
			break;
		case 2:
			this->pathAppendFileType = "Pictures/";
			break;
		case 3:
			this->pathAppendFileType = "Videos/";
			break;
		}

		this->basePath = passedBasePath;

		//How many of this file have been found
		this->count = 0;

		//Initializes the currentMax as a 0
		this->currentMax = 0;
		//Calculates the maximum value
		this->calcMax(noMaxes);
	}

	void calcMax(bool noMaxes) {

		int store = 0, compare = 0;

		if (!noMaxes) {
			//Appends the correct container name given the container var
			std::string pathAppend = this->pathAppendFileType + this->fileType;

			for (const auto& entry : directory_iterator(this->basePath + pathAppend))
			{
				// Does not look through names of pre-existing folders
				// Without this check, the program will violently crash
				// every time it comes across a folder in a source dir
				if (!is_directory(entry)) this->currentMax++;
			}
		}
		//Stores the currentMax in the var
		this->currentMax = store;
	}

	void incrementCount() {
		this->count++;
	}
};

#endif