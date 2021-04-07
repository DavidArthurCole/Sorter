#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include "globalVars.h"

std::string replace(std::string str, const std::string& from, const std::string& to) {
	std::string strCopy = str;
	size_t start_pos = strCopy.find(from);
	if (start_pos == std::string::npos)
		return std::string();
	strCopy.replace(start_pos, from.length(), to);
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