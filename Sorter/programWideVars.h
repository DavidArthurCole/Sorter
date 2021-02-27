#pragma once
#include <string>
#include <Windows.h>
#include <boost/filesystem.hpp>
#include <pathcch.h>

//Namespace to use for the file adding iteration
namespace fs = boost::filesystem;

//Size used to create an array (aka maximum amount of files that can be handled in one iteration)
const int MAX_SIZE = 16384;

//THESE WILL NEED TO BE EDITED EVERYTIME A NEW FILETYPE IS ADDED
//===========================================================================================================
const int PIC_FILE_TYPES = 5;
const int VID_FILE_TYPES = 8;
const int DOC_FILE_TYPES = 8;
const int AUDIO_FILE_TYPES = 4;

const int DIF_FILE_TYPES = 25;

const std::string picFileTypes[PIC_FILE_TYPES] = { "BMP","JFIF","JPEG","JPG","PNG" };
const std::string vidFileTypes[VID_FILE_TYPES] = { "AVI", "FLV","GIF","MKV","MOV","MP4","MPG", "WEBM" };
const std::string docFileTypes[DOC_FILE_TYPES] = { "DOC", "DOCX", "PDF", "PPT", "PPTX","PST","XLS","XLSX" };
const std::string audioFileTypes[AUDIO_FILE_TYPES] = { "FLAC", "M4A", "MP3", "WAV" };
//===========================================================================================================

std::vector<std::string> allFileTypes[DIF_FILE_TYPES];
std::vector<int> allFileTypesContainers[DIF_FILE_TYPES];

void populateAllTypesArray()
{

	//Adds picture file types to the 'all' array
	for (int i = 0; i < PIC_FILE_TYPES; i++)
	{
		allFileTypes->push_back(picFileTypes[i]);
		allFileTypesContainers->push_back(2);
	}
	//Adds video file types to the 'all' array
	for (int i = 0; i < VID_FILE_TYPES; i++)
	{
		allFileTypes->push_back(vidFileTypes[i]);
		allFileTypesContainers->push_back(3);
	}
	//Adds document file types to the 'all' array
	for (int i = 0; i < DOC_FILE_TYPES; i++)
	{
		allFileTypes->push_back(docFileTypes[i]);
		allFileTypesContainers->push_back(0);
	}
	//Adds audio file types to the 'all' array
	for (int i =0 ; i < AUDIO_FILE_TYPES; i++)
	{
		allFileTypes->push_back(audioFileTypes[i]);
		allFileTypesContainers->push_back(1);
	}
}

std::string getExePath()
{
	//Gets the full path, including the executable name
	std::string path = fs::system_complete(fs::path(__argv[0])).string();
	//Replaces \ with / in the path, needed for boost
	std::replace(path.begin(), path.end(), '\\', '/');
	//Returns the path without the .exe
	return(path.substr(0, path.find_last_of("/") + 1));
}

//Working directory
std::string basePath = getExePath();

//Files that need to be sorted
std::string sourcePath = basePath + "Source/";

//Path to log files
std::string logsPath = basePath + "Logs/";

//Stores all files that need to be sorted as a path
std::vector<std::string> sourcePathFilesFullPath;

//Stores all files that need to be sorted as their file name
std::vector<std::string> sourcePathFileNames;

//Counts how many files are in sourcePath
int sourcePathCount = 0;

//Random boolean logic to prevent removing a freshly generated sourcedir
bool freshSource = false;

//Size_T for source folder size
size_t sourceSize;