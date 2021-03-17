#pragma once
#include <vector>
#include "FileHandler.h"
#include "globalVars.h"

void buildFileHandlersVector(std::vector<FileHandler>& fileHandlers) {
	//Fills the vector with FileHandlers of each supported type
	for (int i = 0; i < DIF_FILE_TYPES; i++) {
		fileHandlers.push_back(FileHandler(allFileTypes->at(i), allFileTypesContainers->at(i), basePath, noMaxes));
	}
}