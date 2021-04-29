#pragma once
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

	//Adds picture file types to the 'all' array
	for (int i = 0; i < PIC_FILE_TYPES; i++){
		allFileTypes->push_back(picFileTypes[i]);
		allFileTypesContainers->push_back(2);
		//Creates picture sub folders
		std::string folderPath = "Pictures\\" + picFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}

	//Adds video file types to the 'all' array
	//beans
	for (int i = 0; i < VID_FILE_TYPES; i++){
		allFileTypes->push_back(vidFileTypes[i]);
		allFileTypesContainers->push_back(3);
		//Creates video sub folders
		std::string folderPath = "Videos\\" + vidFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}

	//Adds document file types to the 'all' array
	for (int i = 0; i < DOC_FILE_TYPES; i++){
		allFileTypes->push_back(docFileTypes[i]);
		allFileTypesContainers->push_back(0);
		//Creates document sub folders
		std::string folderPath = "Documents\\" + docFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}

	//Adds audio file types to the 'all' array
	for (int i = 0; i < AUDIO_FILE_TYPES; i++){
		allFileTypes->push_back(audioFileTypes[i]);
		allFileTypesContainers->push_back(1);
		//Creates audio sub folders
		std::string folderPath = "Audio\\" + audioFileTypes[i];
		if (!exists(folderPath)) create_directory(folderPath);
	}
}