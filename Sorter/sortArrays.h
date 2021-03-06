#pragma once
#include "fillSourceArray.h"
#include "getFileName.h"
#include "FileHandler.h"
#include "globalVars.h"
#include "copyHelper.h"

void sortArrays()
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
		std::string fileExt = "";
		if (sourcePathFilesFullPath.at(i).find_last_of(".") != std::string::npos) {
			//Gets the supposed file type
			std::string posFileType = sourcePathFilesFullPath.at(i).substr(sourcePathFilesFullPath.at(i).find_last_of(".") + 1);
			//Will not return file types longer than 6 chars (to account for type-less-files with periods in them)
			if (posFileType.length() <= 6) fileExt = posFileType; //Returns every char in the string after the last '.'
			else fileExt = "";
		}
		else fileExt = "";

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

				//Grabs the filename
				std::string fileName = getFileName(sourcePathFileNames.at(i), fileExtUpper);

				//Copies the file
				copyHelper(sourcePathFilesFullPath.at(i), fileName,
					basePath + "\\SourceUnhandled\\" + sourcePathFileNames.at(i), //Possible path if there are no duplicates
					basePath + "\\SourceUnhandled\\" + fileName + " (%FILL_INT_HERE%)" + "." + fileExt); //Path if there are dupes

				//Increments
				totalSorts++;
				//NEEDS A \r AT THE BEGINNING to overwrite the last print, extra spaces are to deal with all of the threads running at once
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

	if (totalSorts > 0) std::cout << "\n";

	auto arrayTimerDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startArrayTimer);
	std::cout << "Added " << sourcePathCount << " files to internal array " << float(arrayTimerDuration.count() / 1000.00) << " seconds.\n";
}