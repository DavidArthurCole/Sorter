#pragma once
#include "globalVars.h"
#include "duplicateDetector.h"

void copyHelper(std::string source, std::string fileName, std::string checkPath, std::string alternatePath) {
	//Creates a new path, checking for duplicates
	std::string newPath = duplicateDetector(checkPath, alternatePath);
	//Copies the file
	try {
		copy_file(source, newPath);
	}
	catch (std::exception ex) {}
}