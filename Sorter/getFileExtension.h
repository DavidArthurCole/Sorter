#pragma once
#include <string>

// (This will return an empty string on a "no-type-file", which is intentional
std::string getFileExtension(const std::string& FileName){
	if (FileName.find_last_of(".") != std::string::npos) {
		//Gets the supposed file type
		std::string posFileType = FileName.substr(FileName.find_last_of(".") + 1);
		//Will not return file types longer than 6 chars (to account for type-less-files with periods in them)
		if (posFileType.length() <= 6) return posFileType; //Returns every char in the string after the last '.'
	}	
	return "";
}