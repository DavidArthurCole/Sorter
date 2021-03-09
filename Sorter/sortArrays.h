#pragma once
#include <string>
#include "globalVars.h"
#include "getFileExtension.h"
#include "FileHandler.h"
#include <iostream>

void sortArrays(std::vector<FileHandler> &fileHandlers)
{
	//Var for the index of the filetype in the 'all-types' array
	int fileExtIndex;
	//Intra-loop vars
	std::string lastFileExt = "";
	int lastIndex = 0;

	// For every file that was added to the sourceArray
	// (every file that existed in ../Source/
	for (int i = 0; i < sourcePathCount; i++)
	{
		//String to hold filetype before the file is sorted into its array
		std::string fileExt = getFileExtension(sourcePathFilesFullPath.at(i));

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
		
		//If the file type is not in the list, it will be put into SourceUnhandled
		if (fileExtIndex == (DIF_FILE_TYPES)) {

			//Deals with nested folders or otherwise unsorted files
			//will dump them into SourceUnhandled

			//Creates two directory strings to be used in copying
			std::string sourceDir = sourcePathFilesFullPath.at(i);
			std::string destDir = basePath + "SourceUnhandled/" + sourcePathFileNames.at(i);
			//The input file
			std::ifstream src(sourceDir, std::ios::binary);
			//The output file
			std::ofstream dst(destDir, std::ios::binary);

			//Copies input to output
			dst << src.rdbuf();
			src.close();
			dst.close();
			totalSorts++;
			std::cout << "\rSorted " << totalSorts << " unsupported files. " << "(" << totalSorts << " total)";
		}
		else {
			fileHandlers.at(fileExtIndex).fullPath.push_back(sourcePathFilesFullPath.at(i));
			fileHandlers.at(fileExtIndex).fileNames.push_back(sourcePathFileNames.at(i));
			fileHandlers.at(fileExtIndex).incrementCount();
		}

		//intra-loop code
		lastFileExt = fileExt;
		lastIndex = fileExtIndex;
	}
	if(totalSorts > 0) std::cout << "\n";
}
