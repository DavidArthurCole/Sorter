#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include "globalVars.h"

std::string replace(std::string str, const std::string& from, const std::string& to);

std::string duplicateDetector (std::string filePath, std::string alternatePath) {
	if (!std::filesystem::exists(filePath)) {
		//If the file doesn't exist, return it as a valid new path
		return(filePath);
	}
	else {
		//If the files does exist, iterate through until it doesn't
		for (int j = 1; j < MAX_SIZE; j++) {
			//Creates a new string for the file, "Demo.txt" would become "Demo (1).txt"
			std::string newPath = replace(alternatePath, replaceReg, std::to_string(j));
			if (!std::filesystem::exists(newPath)) {
				//If the edited file path doesn't exist, it is valid; return it
				return(newPath);
			}
		}
		return std::string();
	}
}

std::string replace(std::string str, const std::string& from, const std::string& to) {
	std::string strCopy = str;
	size_t start_pos = strCopy.find(from);
	if (start_pos == std::string::npos)
		return std::string();
	strCopy.replace(start_pos, from.length(), to);
	return strCopy;
}