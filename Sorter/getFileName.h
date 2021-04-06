#pragma once
#include <string>

std::string getFileName(std::string fileWithExt, std::string fileExt) {
	//If there is no file extension, there will not be a "." in the filename
	int mod = 0;
	if (fileExt.length() != 0) { mod = 1; }
	return(fileWithExt.substr(0, fileWithExt.length() - (fileExt.length() + mod)));
}