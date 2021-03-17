#pragma once
#include <vector>
#include <string>
#include <filesystem>

#include "globalVars.h"

using namespace std::filesystem;

void fillSourceArray(std::string path) {

    startArrayTimer = std::chrono::steady_clock::now();

    // Get recursive list of files in source dir
    for (const auto& entry : directory_iterator(path)) {
        if (is_directory(entry)) {
            fillSourceArray(entry.path().string());
        }
        //Fills the source arrays (paths, filenames) with all files found in source
        else {
            std::string str = entry.path().string();
            //Stores full path for the file
            sourcePathFilesFullPath.push_back(str);

            //Stores just the file name
            sourcePathFileNames.push_back(str.substr(int((str.find_last_of("\\")) + 1), str.length() - int((str.find_last_of("\\")) + 1)));

            //Increments number of source files
            sourcePathCount++;
        }
    }
}