#pragma once
#include <string>

// Returns the characters after the last '.' in a filename, giving the filetype (this will fail with empty filetypes,
// or folders, however this is handled with other code)
std::string getFileExtension(const std::string& FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	return "";
}