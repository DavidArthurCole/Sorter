#pragma once
#include <string>

std::string getFileName(std::string fileWithExt, std::string fileExt) {
	return(fileWithExt.substr(0, fileWithExt.length() - (fileExt.length() + 1)));
}