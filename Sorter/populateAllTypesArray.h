#pragma once
#include "globalVars.h"

void populateAllTypesArray()
{
	int h = 0;

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
	for (int i = 0; i < AUDIO_FILE_TYPES; i++)
	{
		allFileTypes->push_back(audioFileTypes[i]);
		allFileTypesContainers->push_back(1);
	}
}