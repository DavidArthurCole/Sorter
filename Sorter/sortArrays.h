#pragma once
#include <string>
#include "fillSourceArray.h"
#include "getFileExtension.h"
#include "FileHandler.h"
#include "globalVars.h"
#include <iostream>

void sortArrays()
{
	//Var for the index of the filetype in the 'all-types' array
	int fileExtIndex;
	//Intra-loop vars
	std::string lastFileExt = "";
	int lastIndex = 0;

	std::string unhandledFiles[MAX_SIZE];

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

		//Don't sort DLL files or SYS files
		if (fileExtUpper == "DLL" || fileExtUpper == "SYS" || fileExtUpper == "BIN") break;

		//Saves calculation time if multiple files in a row have the same file type
		if (fileExt == lastFileExt) {
			fileExtIndex = lastIndex;
		}
		else {
			//Finds the index of the filetype in the map
			fileExtIndex = static_cast<int>(std::find(allFileTypes->begin(), allFileTypes->end(), fileExtUpper) - allFileTypes->begin());
		}
		
		//If the file type is not in the list, it will be put into SourceUnhandled
		if (fileExtIndex == (DIF_FILE_TYPES)) {
			//Don't include folders
			if (!std::filesystem::is_directory(sourcePathFilesFullPath.at(i))) {
				//Deals with nested folders or otherwise unsorted files
				//	(Will dump them into SourceUnhandled/)

				//The input file - Any files that are not supported
				std::ifstream src(sourcePathFilesFullPath.at(i), std::ios::binary);

				std::string fileName = sourcePathFileNames.at(i).substr(0, (sourcePathFileNames.at(i).length() - (fileExt.length() + 1)));
				std::string destPath = "";

				//The output file - If there are duplicate file names, they won't be overwritten  (took me way too long to figure this out)
				if (std::filesystem::exists(basePath + "\\SourceUnhandled\\" + sourcePathFileNames.at(i))) {
					for (int i = 1; i < MAX_SIZE; i++) {
						std::string testPath = (basePath + "\\SourceUnhandled\\" + fileName + " (" + std::to_string(i) + ")" + "." + fileExt);
						if (!std::filesystem::exists(testPath)) {
							destPath = testPath;
							break;
						}
					}
				}
				else destPath = (basePath + "\\SourceUnhandled\\" + sourcePathFileNames.at(i));

				std::ofstream dst(destPath, std::ios::binary);

				//Copies input to output
				dst << src.rdbuf();
				src.close();
				dst.close();

				//Increments
				totalSorts++;
				//NEEDS A \r AT THE BEGINNING
				std::cout << "\rSorted " << totalSorts << " unsupported files. " << "(" << totalSorts << " total)";
			}
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

	auto arrayTimerDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startArrayTimer);
	std::cout << "Added " << sourcePathCount << " files to internal array " << float(arrayTimerDuration.count() / 1000.00) << " seconds.\n";
}
