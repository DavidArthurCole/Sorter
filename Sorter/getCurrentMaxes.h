#pragma once
#include "programWideVars.h"
#include <string>
#include <iostream>

void getCurrentMaxes(int argc, char* argv[])
{
	bool maxesDone = false;
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-nomaxes")
		{
			// All maxes are already initialized as -1, meaning the first
			// file will be 0.
			maxesDone = true;
		}
	}
	if (maxesDone == false)
	{
		// What to append to basePath to point to
			// where the filetype is found
		std::string pathAppend;

		//3 COUNT FILE EXTENSIONS
		for (int i = 0; i <= 17; i++)
		{
			int store = -1, compare = 0;
			switch (i)
			{
			case 0:
				pathAppend = "Videos/GIF/";
				break;
			case 1:
				pathAppend = "Pictures/BMP/";
				break;
			case 2:
				pathAppend = "Pictures/JPG/";
				break;
			case 3:
				pathAppend = "Pictures/PNG/";
				break;
			case 4:
				pathAppend = "Videos/AVI/";
				break;
			case 5:
				pathAppend = "Videos/FLV/";
				break;
			case 6:
				pathAppend = "Videos/MKV/";
				break;
			case 7:
				pathAppend = "Videos/MOV/";
				break;
			case 8:
				pathAppend = "Videos/MP4/";
				break;
			case 9:
				pathAppend = "Videos/MPG/";
				break;
			case 10:
				pathAppend = "Documents/DOC/";
				break;
			case 11:
				pathAppend = "Documents/PDF/";
				break;
			case 12:
				pathAppend = "Documents/PPT/";
				break;
			case 13:
				pathAppend = "Documents/PST/";
				break;
			case 14:
				pathAppend = "Documents/XLS";
				break;
			case 15:
				pathAppend = "Audio/M4A";
				break;
			case 16:
				pathAppend = "Audio/MP3";
				break;
			case 17:
				pathAppend = "Audio/WAV";
				break;
			}

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
					compare = stoi(filePath.substr(3, (filePath.length() - 3)));

					// If the current filename is larger than store, replace store
					if (compare > store)
					{
						store = compare;
					}
				}
			}
			// Put store into the array to be used later
			currentMaxes[i] = store;
		}
		//4 COUNT FILE EXTENSIONS
		for (int i = 18; i <= 24; i++)
		{
			int store = -1, compare = 0;
			switch (i)
			{
			case 18:
				pathAppend = "Pictures/JFIF/";
				break;
			case 19:
				pathAppend = "Pictures/JPEG/";
				break;
			case 20:
				pathAppend = "Videos/WEBM/";
				break;
			case 21:
				pathAppend = "Documents/DOCX/";
				break;
			case 22:
				pathAppend = "Documents/PPTX";
				break;
			case 23:
				pathAppend = "Documents/XLSX";
				break;
			case 24:
				pathAppend = "Audio/FLAC";
				break;
			}
			for (const auto& entry : fs::directory_iterator(basePath + pathAppend))
			{
				// Does not look through names of pre-existing folders
				// Without this check, the program will violently crash
				// every time it comes across a folder in a source dir

				if (!fs::is_directory(entry))
				{
					//Gets the name of a file (ex: "WEBM1234")
					std::string filePath = entry.path().filename().string();

					//Gets only the numerical value from the name (ex: 1234)
					compare = stoi(filePath.substr(4, (filePath.length() - 4)));

					// If the current filename is larger than store, replace store
					if (compare > store)
					{
						store = compare;
					}
				}
			}
			// Put store into the array to be used later
			currentMaxes[i] = store;
		}

		// Sets the max of certain filetypes to their respective
		// place inside of the defined array

		// TODO: THINK OF A BETTER WAY TO DO THIS;
		// AKA: GET RID OF THIS FUCKING SHIT
		currentMaxGif = currentMaxes[0] + 1;
		currentMaxBmp = currentMaxes[1] + 1;
		currentMaxJpg = currentMaxes[2] + 1;
		currentMaxPng = currentMaxes[3] + 1;
		currentMaxAvi = currentMaxes[4] + 1;
		currentMaxFlv = currentMaxes[5] + 1;
		currentMaxMkv = currentMaxes[6] + 1;
		currentMaxMov = currentMaxes[7] + 1;
		currentMaxMp4 = currentMaxes[8] + 1;
		currentMaxMpg = currentMaxes[9] + 1;
		currentMaxDoc = currentMaxes[10] + 1;
		currentMaxPdf = currentMaxes[11] + 1;
		currentMaxPpt = currentMaxes[12] + 1;
		currentMaxPst = currentMaxes[13] + 1;
		currentMaxXls = currentMaxes[14] + 1;
		currentMaxM4a = currentMaxes[15] + 1;
		currentMaxMp3 = currentMaxes[16] + 1;
		currentMaxWav = currentMaxes[17] + 1;

		currentMaxJfif = currentMaxes[18] + 1;
		currentMaxJpeg = currentMaxes[19] + 1;
		currentMaxWebm = currentMaxes[20] + 1;
		currentMaxDocx = currentMaxes[21] + 1;
		currentMaxPptx = currentMaxes[22] + 1;
		currentMaxXlsx = currentMaxes[23] + 1;
		currentMaxFlac = currentMaxes[24] + 1;
	}
}