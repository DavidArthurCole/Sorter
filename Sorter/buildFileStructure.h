#pragma once
#include <string>
#include <fstream>
#include <Windows.h>
#include <iostream>
#include <filesystem>

#include "populateAllTypesArray.h"
#include "globalVars.h"

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
	//  |__ Sorter.exe (Self)
	//=========================

	populateAllTypesArray();

	//All folders and subfolders that need to be created
	const int folderStructCount = 6;
	const char* baseFolderStructure[folderStructCount] =
	{ "Documents\\", "Audio\\", "Pictures\\", "Videos\\", "Source\\", "SourceUnhandled\\" };

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


	for (size_t i = 0; i < allFileTypes->size(); i++) {
		//Grabs a file extension from the list
		std::string fileType = allFileTypes->at(i);
		//Determines which subcategory the extension fits
		if (vidFileTypes->find(fileType) != std::string::npos) fileType = "Videos\\" + vidFileTypes[i];
		else if (picFileTypes->find(fileType) != std::string::npos) fileType = "Pictures\\" + picFileTypes[i];
		else if (audioFileTypes->find(fileType) != std::string::npos) fileType = "Audio\\" + audioFileTypes[i];
		else if (docFileTypes->find(fileType) != std::string::npos) fileType = "Documents\\" + docFileTypes[i];

		//If the folder doesn't exist, create it
		if (!exists(fileType)) create_directory(fileType);
	}

}