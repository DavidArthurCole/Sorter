#pragma once
#include <string>
#include "programWideVars.h"
#include "getFileExtension.h"
#include "FileHandler.h"
#include <iostream>

//String to hold filetype before the file is sorted into its array
std::string fileExt;

int getTypeIndex(std::vector<std::string> v, std::string K) {
	{
		auto it = find(v.begin(), v.end(), K);

		// If element was found
		if (it != v.end())
		{
			// calculating the index
			// of K
			int index = it - v.begin();
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

		std::string fileExtUpper = boost::to_upper_copy(fileExt);
		

		int fileExtIndex = std::find(allFileTypes->begin(), allFileTypes->end(), fileExtUpper) - allFileTypes->begin();

		if (fileExtIndex != -1){

			fileHandlers.at(fileExtIndex).fullPath.push_back(sourcePathFilesFullPath.at(i));
			fileHandlers.at(fileExtIndex).fileNames.push_back(sourcePathFileNames.at(i));
			fileHandlers.at(fileExtIndex).incrementCount();
		}
		else
		{
			//Deals with nested folders or otherwise broken files,
			//will dump them into SourceUnhandled

			//Creates two directories to be used in copying
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
	}
	
}
