#ifndef FileHandler_HEADER
#define FileHandler_HEADER

#include <string>
#include <filesystem>
#include <Windows.h>
#include <iostream>
#include <vector>

using namespace std::filesystem;

class fileHandler {

public:

	//Store the fileType (TXT, JPG, etc.)
	std::string fileType;
	//Stores the base path of the program "C:/Path/To/Executable/...(Sorter.exe)" without the executable name
	std::string basePath;
	//Essentially the same thing as fileType, but capital
	std::string pathAppendFileType;
	//How many files with this type have been found
	int count;

	std::vector<std::string> fullPath{ }, fileNames{ };

	fileHandler(std::string passedFileType, std::string pathAppendFileType, std::string passedBasePath) {
		//Sets the filetype
		this->fileType = passedFileType;

		//Sets the append type
		this->pathAppendFileType = pathAppendFileType;

		this->basePath = passedBasePath;

		//How many of this file have been found
		this->count = 0;
	}

	void incrementCount() {
		this->count++;
	}
};

#endif