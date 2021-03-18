#pragma once
#ifndef GLOBAL_VARS_HEADER
#define GLOBAL_VARS_HEADER
#ifndef INCLUDES
	#include <Windows.h>
	#include <iostream>
	#include "getExePath.h"
	#include "fileHandler.h"
#endif

//Size used to create an array (aka maximum amount of each file type that can be handled in one iteration)
const int MAX_SIZE = 16384;

// A SET OF THESE WILL NEED TO BE EDITED EVERYTIME A NEW FILETYPE IS ADDED
// THE CONSTANT INT SHOULD ALWAYS BE EQUAL TO THE AMOUNT OF FILE TYPES IN THE ARRAY
// PLEASE ALSO EDIT THE 'Visual File Structure' INSIDE OF buildFileStructure.h TO REFLECT CHANGES MADE
//===========================================================================================================
// IF YOU ARE ADDING A NEW PICTURE FILE TYPE:
const int PIC_FILE_TYPES = 5;
const std::string picFileTypes[] = { "BMP","JFIF","JPEG","JPG","PNG" };
//===========================================================================================================
// IF YOU ARE ADDING A NEW VIDEO FILE TYPE:
const int VID_FILE_TYPES = 8;
const std::string vidFileTypes[VID_FILE_TYPES] = { "AVI", "FLV","GIF","MKV","MOV","MP4","MPG", "WEBM" };
//===========================================================================================================
// IF YOU ARE ADDING A NEW DOCUMENT FILE TYPE:
const int DOC_FILE_TYPES = 8;
const std::string docFileTypes[DOC_FILE_TYPES] = { "DOC", "DOCX", "PDF", "PPT", "PPTX","PST","XLS","XLSX" };
//===========================================================================================================
// IF YOU ARE ADDING A NEW AUDIO FILE TYPE:
const int AUDIO_FILE_TYPES = 4;
const std::string audioFileTypes[AUDIO_FILE_TYPES] = { "FLAC", "M4A", "MP3", "WAV" };
//===========================================================================================================

const int DIF_FILE_TYPES = PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES + AUDIO_FILE_TYPES;
std::vector<std::string> allFileTypes[DIF_FILE_TYPES];
std::vector<int> allFileTypesContainers[DIF_FILE_TYPES];

//Vector of fileHandlers
std::vector<fileHandler> fileHandlers;

//Total execution timer
auto startExec = std::chrono::steady_clock::now();
auto startArrayTimer = std::chrono::steady_clock::now();

//Working directory
std::string basePath = getExePath();

//Files that need to be sorted
std::string sourcePath = basePath + "Source";

//Path to log files
std::string logsPath = basePath + "Logs/";

//Stores all files that need to be sorted as a path
std::vector<std::string> sourcePathFilesFullPath;

//Stores all files that need to be sorted as their file name
std::vector<std::string> sourcePathFileNames;

//Counts how many files are in sourcePath
int sourcePathCount = 0;

//Counts total sorted files
int totalSorts = 0;

//Random boolean logic to prevent removing a freshly generated sourcedir
bool freshSource = false;

bool postClean = false;
bool noMaxes = false;

//Size_T for source folder size
size_t sourceSize;

#endif