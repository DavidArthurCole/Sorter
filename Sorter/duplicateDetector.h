#pragma once
#include "globalVars.h"

std::string replace(std::string str, const std::string& from, const std::string& to) {
	//Creates a copy of the string to manipulate
	std::string strCopy = str;
	//Gets the position of the first string
	size_t start_pos = strCopy.find(from);
	//If the string to be replaced doesn't exist, return empty
	if (start_pos == std::string::npos)
		return std::string();
	//Replace from the start position until the end with "to"
	strCopy.replace(start_pos, from.length(), to);
	//Return the string
	return strCopy;
}

std::string duplicateDetector (std::string filePath, std::string alternatePath) {
	//If the file doesn't exist, return it as a valid new path
	if (!std::filesystem::exists(filePath)) return(filePath);
	else {
		//If the files does exist, iterate through until it doesn't
		for (int j = 1; j < MAX_SIZE; j++) {
			//Creates a new string for the file, "Demo.txt" would become "Demo (1).txt"
			std::string newPath = replace(alternatePath, replaceReg, std::to_string(j));
			//If the edited file path doesn't exist, it is valid; return it
			if (!std::filesystem::exists(newPath)) return(newPath);
		}
		return std::string();
	}
}