#ifndef FileHandler_HEADER
#define FileHandler_HEADER

#include <string>
#include <C:/Users/david/Documents/SDKS/boost_1_75_0/boost/algorithm/string.hpp>
#include <C:/Users/david/Documents/SDKS/boost_1_75_0/boost/filesystem.hpp>
#include <Windows.h>
#include <iostream>

class FileHandler {	

	public:

		std::string fileType;
		//Container points to which folder will contain the file type;
			// 0 is documents
			// 1 is audio
			// 2 is pictures
			// 3 is videos
		int container;
		//Current max number of the stored file
		int currentMax;
		//How many files with this type have been found
		int count;

		std::vector<std::string> fullPath { }, fileNames { };

		FileHandler(std::string passedFileType, int passedContainer) {
			//Sets the filetype
			fileType = passedFileType;

			//Sets the container
			container = passedContainer;

			//How many of this file have been found
			this->count = 0;

			//Initializes the currentMax as a 0
			this->currentMax = 0;
			//Calculates the maximum value
			this->calcMax();
		}

		void calcMax() {

			namespace fs = boost::filesystem;

			//For use in the file searching
			int amtToSubtract = static_cast<int>(this->fileType.length());

			//Appends the correct container name given the container var
			std::string pathAppend = "";
			switch (this->container) {
				case 0:
					pathAppend = "Documents/";
					break;
				case 1:
					pathAppend = "Audio/";
					break;
				case 2:
					pathAppend = "Pictures/";
					break;
				case 3:
					pathAppend = "Videos/";
					break;
			}
			//Appends the fileType var
			std::string upperType = boost::to_upper_copy(this->fileType);
			pathAppend += upperType;
			//Gets the base path
			std::string basePath = getExePath();

			int store = -1, compare = 0;

			for (const auto& entry : fs::directory_iterator(basePath + pathAppend))
			{
				// Does not look through names of pre-existing folders
				// Without this check, the program will violently crash
				// every time it comes across a folder in a source dir
				if (!fs::is_directory(entry))
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

			//Stores the currentMax in the var
			this->currentMax = store;
		}

		void incrementCount() {
			this->count++;
		}

		std::string getExePath()
		{
			namespace fs = boost::filesystem;
			//Gets the full path, including the executable name
			std::string path = fs::system_complete(fs::path(__argv[0])).string();
			//Replaces \ with / in the path, needed for boost
			std::replace(path.begin(), path.end(), '\\', '/');
			//Returns the path without the .exe
			return(path.substr(0, path.find_last_of("/") + 1));
		}
};

#endif