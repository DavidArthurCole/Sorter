#ifndef FileHandler_HEADER
#define FileHandler_HEADER

#include <string>
#include <filesystem>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std::filesystem;

class FileHandler {	

	public:

		std::string fileType;
		//Container points to which folder will contain the file type;
			// 0 is documents
			// 1 is audio
			// 2 is pictures
			// 3 is videos

		std::string basePath;
		std::string pathAppendFileType;

		int container;
		//Current max number of the stored file
		int currentMax;
		//How many files with this type have been found
		int count;

		std::vector<std::string> fullPath { }, fileNames { };

		FileHandler(std::string passedFileType, int passedContainer, std::string passedBasePath, bool noMaxes) {
			//Sets the filetype
			fileType = passedFileType;

			//Sets the container
			container = passedContainer;
			switch (container) {
			case 0:
				pathAppendFileType = "Documents/";
				break;
			case 1:
				pathAppendFileType = "Audio/";
				break;
			case 2:
				pathAppendFileType = "Pictures/";
				break;
			case 3:
				pathAppendFileType = "Videos/";
				break;
			}

			this->basePath = passedBasePath;

			//How many of this file have been found
			this->count = 0;

			//Initializes the currentMax as a 0
			this->currentMax = 0;
			//Calculates the maximum value
			this->calcMax(noMaxes);
		}

		void calcMax(bool noMaxes) {

			int store = -1, compare = 0;

			if (!noMaxes) {
				//For use in the file searching
				int amtToSubtract = static_cast<int>(this->fileType.length());

				//Appends the correct container name given the container var
				std::string pathAppend = this->pathAppendFileType + this->fileType;



				for (const auto& entry : directory_iterator(this->basePath + pathAppend))
				{
					// Does not look through names of pre-existing folders
					// Without this check, the program will violently crash
					// every time it comes across a folder in a source dir
					if (!is_directory(entry))
					{
						//Gets the name of a file (ex: "PNG1234")
						std::string filePath = entry.path().filename().string();

						//Gets only the numerical value from the name (ex: 1234)
						compare = std::stoi(filePath.substr(amtToSubtract, (filePath.length() - amtToSubtract)));

						// If the current filename is larger than store, replace store
						if (compare > store)
						{
							store = compare;
						}
					}
				}
			}
			//Stores the currentMax in the var
			this->currentMax = store;
		}

		void incrementCount() {
			this->count++;
		}
};

#endif