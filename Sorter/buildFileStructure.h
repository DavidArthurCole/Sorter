#pragma once
#include <string>
#include <fstream>
#include <Windows.h>
#include <iostream>
#include <filesystem>

#include "populateAllTypesArray.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void buildFileStructure()
{
	using namespace std::filesystem;

	// VISUAL FILE STRUCTURE 
	//=========================
	//  |
	//  |__ Documents
	//	|	  |__ DOC
	//	|	  |__ DOCX
	//	|	  |__ PDF
	//	|	  |__ PPT
	//	|	  |__ PPTX
	//	|	  |__ PST
	//  |     |__ TXT
	//	|	  |__ XLS
	//	|	  |__ XLSX
	//  |
	//  |__ Audio
	//  |     |__ FLAC
	//	|	  |__ M4A
	//	|	  |__ MP3
	//	|	  |__ WAV
	//  |
	//	|__ Pictures
	//	|	  |__ BMP
	//	|	  |__ JFIF
	//	|	  |__ JPEG
	//	|	  |__ JPG
	//	|	  |__ PNG
	//  |
	//  |__ Source
	//  |
	//  |__ SourceUnhandled
	//  |
	//  |__ Videos
	//	|	  |__ AVI
	//	|	  |__ FLV
	//	|	  |__ GIF
	//	|	  |__ MKV
	//	|	  |__ MOV
	//	|	  |__ MP4
	//	|	  |__ MPG
	//	|	  |__ WEBM
	//  |
	//  |__ Sorter.exe (Me)
	//=========================

	populateAllTypesArray();

	//All folders and subfolders that need to be created
	const int folderStructCount = 6;
	const char *baseFolderStructure[folderStructCount] = 
	{ "Documents\\", "Audio\\", "Pictures\\", "Videos\\", "Source\\", "SourceUnhandled\\"};

	if (!exists("Source\\")) {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Source folder did not exist, and was created at the beginning of this run.\nPlease add all files that need to be sorted to 'Source,' and run the program again.\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		freshSource = true;
	}
		
	//Creates base folders
	for (int i = 0; i < folderStructCount; i++) {
		// If the folder doesn't exist
		if (!exists(baseFolderStructure[i])) create_directory(baseFolderStructure[i]);
	}

	//Creates video sub folders
	for (int i = 0; i < VID_FILE_TYPES; i++) {
		std::string folderPath = "Videos\\" + vidFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}
	//Creates picture sub folders
	for (int i = 0; i < PIC_FILE_TYPES; i++) {
		std::string folderPath = "Pictures\\" + picFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}
	//Creates audio sub folders
	for (int i = 0; i < AUDIO_FILE_TYPES; i++) {
		std::string folderPath = "Audio\\" + audioFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}
	//Creates document sub folders
	for (int i = 0; i < DOC_FILE_TYPES; i++) {
		std::string folderPath = "Documents\\" + docFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}
}