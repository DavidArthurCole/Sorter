#pragma once
#include <C:/Users/david/Documents/SDKS/boost_1_75_0/boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iostream>

#include "programWideVars.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void buildFileStructure()
{
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
	//	|	  |__ XLS
	//	|	  |__ XLSX
	//  |
	//  |__ Logs (One log file for each file type is generated in this folder)
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
	//  |__ Sorter.exe
	//=========================

	populateAllTypesArray();

	//All folders and subfolders that need to be created
	const char *baseFolderStructure[7] = 
	{ "Documents\\", "Logs\\", "Audio\\", "Pictures\\", "Videos\\", "Source\\", "SourceUnhandled\\"};

	//Creates base folders
	for (int i = 0; i < 7; i++)
	{
		// If the folder doesn't exist
		if (!boost::filesystem::exists(baseFolderStructure[i]))
		{
			//If the source file doesn't exist, tell the user they will need to rerun
			if (baseFolderStructure[i] == "Source\\")
			{
				SetConsoleTextAttribute(hConsole, 12);
				std::cout << "Source folder did not exist, and was created at the beginning of this run.\nPlease add all files that need to be sorted to 'Source,' and run the program again.\n\n";
				SetConsoleTextAttribute(hConsole, 15);
				freshSource = true;
			}
			boost::filesystem::create_directory(baseFolderStructure[i]);
		}
	}

	//Creates video sub folders
	for (int i = 0; i < VID_FILE_TYPES; i++)
	{
		std::string folderPath = "Videos\\" + vidFileTypes[i];
		if (!boost::filesystem::exists(folderPath))
		{
			boost::filesystem::create_directory(folderPath);
		}
	}
	//Creates picture sub folders
	for (int i = 0; i < PIC_FILE_TYPES; i++)
	{
		std::string folderPath = "Pictures\\" + picFileTypes[i];
		if (!boost::filesystem::exists(folderPath))
		{
			boost::filesystem::create_directory(folderPath);
		}
	}
	//Creates audio sub folders
	for (int i = 0; i < AUDIO_FILE_TYPES; i++)
	{
		std::string folderPath = "Audio\\" + audioFileTypes[i];
		if (!boost::filesystem::exists(folderPath))
		{
			boost::filesystem::create_directory(folderPath);
		}
	}
	//Creates document sub folders
	for (int i = 0; i < DOC_FILE_TYPES; i++)
	{
		std::string folderPath = "Documents\\" + docFileTypes[i];
		if (!boost::filesystem::exists(folderPath))
		{
			boost::filesystem::create_directory(folderPath);
		}
	}

	//For each filetype, create its respective log
	for (int i = 0; i < DIF_FILE_TYPES ; i++)
	{
		std::string logPath = "Logs\\" + boost::algorithm::to_lower_copy(allFileTypes->at(i)) + "_log.txt";

		std::fstream fileStream;
		fileStream.open(logPath);
		if (fileStream.fail())
		{
			//Creates the log as an empty file, and closest it
			std::ofstream createLog(logPath);
			createLog << "";
			createLog.close();
		}
		//Reset for next pass
		fileStream.clear();
		fileStream.close();
	}
}