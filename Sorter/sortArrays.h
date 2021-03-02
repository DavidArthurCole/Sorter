#pragma once
#include <string>
#include "globalVars.h"
#include "getFileExtension.h"
#include "FileHandler.h"
#include <iostream>

int getTypeIndex(std::vector<std::string> v, std::string K) {
	{
		auto it = find(v.begin(), v.end(), K);

		// If element was found
		if (it != v.end())
		{
			// calculating the index
			// of K
			int index = static_cast<int>(it - v.begin());
			return(index);
		}
		else {
			// If the element is not
			// present in the vector
			return(-1);
		}
	}
}

void sortArrays(std::vector<FileHandler> &fileHandlers)
{
	//String to hold filetype before the file is sorted into its array
	std::string fileExt;
	//Var for the index of the filetype in the 'all-types' array
	int fileExtIndex;
	//Intra-loop vars
	std::string lastFileExt = "";
	int lastIndex = 0;

	// For every file that was added to the sourceArray
	// (every file that existed in ../Source/
	for (int i = 0; i < sourcePathCount; i++)
	{
		//Get the file extension of the file
		fileExt = getFileExtension(sourcePathFilesFullPath.at(i));

		// Given the filetype, find which array it should be put in
		// (if any), add it, then +1 to the count of that filetype

		// fileExt is uppered and lowered to account for certain
		// programs writing the files as such (mostly seen in JPG,
		// PNG), included for all to be safe

		std::string fileExtUpper;
		for (auto elem : fileExt) fileExtUpper += std::toupper(elem);

		//Saves calculation time if multiple files in a row have the same file type
		if (fileExt == lastFileExt) {
			fileExtIndex = lastIndex;
		}
		else {
			//Finds the index of the filetype in the vector
			fileExtIndex = static_cast<int>(std::find(allFileTypes->begin(), allFileTypes->end(), fileExtUpper) - allFileTypes->begin());
		}

		//-1 will be returned if the filetype is not sorted
		if (fileExtIndex != -1){

			fileHandlers.at(fileExtIndex).fullPath.push_back(sourcePathFilesFullPath.at(i));
			fileHandlers.at(fileExtIndex).fileNames.push_back(sourcePathFileNames.at(i));
			fileHandlers.at(fileExtIndex).incrementCount();
		}
		else
		{
			//Deals with nested folders or otherwise unsorted files
			//will dump them into SourceUnhandled

			//Creates two directory strings to be used in copying
			std::string sourceDir = sourcePathFilesFullPath.at(i);
			std::string destDir = basePath + "SourceUnhandled/"+ sourcePathFileNames.at(i);
			//The input file
			std::ifstream src(sourceDir, std::ios::binary);
			//The output file
			std::ofstream dst(destDir, std::ios::binary);

			//Copies input to output
			dst << src.rdbuf();
			src.close();
			dst.close();
		}

		//intra-loop code
		lastFileExt = fileExt;
		lastIndex = fileExtIndex;
	}
	
}
