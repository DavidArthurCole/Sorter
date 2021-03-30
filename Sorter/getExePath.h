#pragma once
#include <string>
#include <filesystem>
using namespace std::filesystem;
std::string getExePath() {
	//Gets the full path, including the executable name
	std::string path = __argv[0];
	//Replaces \ with / in the path
	std::replace(path.begin(), path.end(), '\\', '/');
	//Returns the path without the .exe
	return(path.substr(0, path.find_last_of("/") + 1));
}