#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <filesystem>

#include "globalVars.h"
#include "getFileExtension.h"
#include "sortArrays.h"

using namespace boost::system;
#ifndef USING_BOOST
#define USING_BOOST
#endif
/*
 * Get the list of all files in given directory and its sub directories.
 *
 * Arguments
 *     dirPath : Path of directory to be traversed
 *     dirSkipList : List of folder names to be skipped
 *
 * Returns:
 *     vector containing paths of all the files in given directory and its sub directories
 *
 */
std::vector<std::string> getAllFilesInDir(const std::string& dirPath, const std::vector<std::string> dirSkipList = { })
{
    // Create a vector of string
    std::vector<std::string> listOfFiles;
    try {
        // Check if given path exists and points to a directory
        if (fs::exists(dirPath) && fs::is_directory(dirPath))
        {
            // Create a Recursive Directory Iterator object and points to the starting of directory
            fs::recursive_directory_iterator iter(dirPath);
            // Create a Recursive Directory Iterator object pointing to end.
            fs::recursive_directory_iterator end;
            // Iterate till end
            while (iter != end)
            {
                // Check if current entry is a directory and if exists in skip list
                if (fs::is_directory(iter->path()) &&
                    (std::find(dirSkipList.begin(), dirSkipList.end(), iter->path().filename()) != dirSkipList.end()))
                {
                    // Skip the iteration of current directory pointed by iterator
#ifdef USING_BOOST
                    // Boost Fileystsem  API to skip current directory iteration
                    iter.no_push();
#else
                    // c++17 Filesystem API to skip current directory iteration
                    iter.disable_recursion_pending();
#endif
                }
                else
                {
                    // Add the name in vector
                    listOfFiles.push_back(iter->path().string());
                }
                error_code ec;
                // Increment the iterator to point to next entry in recursive iteration
                iter.increment(ec);
                if (ec) {
                    std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
                }
            }
        }
    }
    catch (std::system_error& e)
    {
        std::cerr << "Exception :: " << e.what();
    }
    return listOfFiles;
}

//Fills the source arrays (paths, filenames) with all files found in source
void fillSourceArray(std::vector<FileHandler> fileHandlers)
{
    namespace fs = boost::filesystem;
    int k = 0;

    std::string dirPath = sourcePath;
    // Get recursive list of files in given directory and its sub directories
    std::vector<std::string> listOfFiles = getAllFilesInDir(dirPath);
    // Iterate over the vector and print all files
    for (auto &str : listOfFiles)
    {

        if (!fs::is_directory(str))
        {
            //Stores full path for the file
            sourcePathFilesFullPath.push_back(str);

            //Stores just the file name
            int indexOfSlash = int(str.find_last_of("\\")) + 1;
            std::string fileName = str.substr(indexOfSlash, str.length() - indexOfSlash);
            sourcePathFileNames.push_back(fileName);
            sourcePathCount++;          
        }
    }
}