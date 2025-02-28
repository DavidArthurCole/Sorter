#include <chrono>
#include <thread>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <Windows.h>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "fileHandler.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
const int VID_FILE_TYPES = 10;
const std::string vidFileTypes[VID_FILE_TYPES] = { "AVI", "FLV","GIF","M4V","MKV","MOV","MP4","MPG", "WEBM", "WMV" };
//===========================================================================================================
// IF YOU ARE ADDING A NEW DOCUMENT FILE TYPE:
const int DOC_FILE_TYPES = 9;
const std::string docFileTypes[DOC_FILE_TYPES] = { "DOC", "DOCX", "PDF", "PPT", "PPTX","PST","TXT","XLS","XLSX" };
//===========================================================================================================
// IF YOU ARE ADDING A NEW AUDIO FILE TYPE:
const int AUDIO_FILE_TYPES = 4;
const std::string audioFileTypes[AUDIO_FILE_TYPES] = { "FLAC", "M4A", "MP3", "WAV" };
//===========================================================================================================

const int DIF_FILE_TYPES = PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES + AUDIO_FILE_TYPES;
std::vector<std::string> allFileTypes[DIF_FILE_TYPES];
std::vector <std::string> pathAppends[DIF_FILE_TYPES];

//Vector of fileHandlers
std::vector<fileHandler> fileHandlers;

//Total execution timer
auto startExec = std::chrono::steady_clock::now();
auto startArrayTimer = std::chrono::steady_clock::now();

// Global vector to hold file types to sort (if empty, sort all)
static std::vector<std::string> onlySortTypes;

// Helper to trim whitespace from a string
static std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t");
    auto end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

static std::string replace(std::string str, const std::string& from, const std::string& to) {
    // Creates a copy of the string to manipulate
    std::string strCopy = str;
    // Gets the position of the first string
    size_t start_pos = strCopy.find(from);
    // If the string to be replaced doesn't exist, return the original string
    if (start_pos == std::string::npos)
        return str;
    // Replace from the start position until the end with "to"
    strCopy.replace(start_pos, from.length(), to);
    // Return the string
    return strCopy;
}

static std::string getExePath() {
    //Gets the full path, including the executable name
    std::string path = __argv[0];
    //Replaces \ with / in the path
    std::replace(path.begin(), path.end(), '\\', '/');
    //Returns the path without the .exe
    return(path.substr(0, path.find_last_of("/") + 1));
}

std::string basePath = getExePath(); //Working directory
std::string sourcePath = basePath + "Source"; //Files that need to be sorted
std::vector<std::string> sourcePathFilesFullPath; //Stores all files that need to be sorted as a path
std::vector<std::string> sourcePathFileNames; //Stores all files that need to be sorted as their file name
int sourcePathCount = 0; //Counts how many files are in sourcePath
int totalSorts = 0; //Counts total sorted files
bool freshSource = false; //Random boolean logic to prevent removing a freshly generated sourcedir

bool postClean = false; //Flags that can be set, default is false
const std::string replaceReg = "%FILL_INT_HERE%"; //Used in duplicateDetector
std::mutex mtx = std::mutex();

static void buildFileStructure() {
    using namespace std::filesystem;

    // VISUAL FILE STRUCTURE 
    //=========================
    //  |
    //  |__ Documents
    //  |     |__ DOC
    //  |     |__ DOCX
    //  |     |__ PDF
    //  |     |__ PPT
    //  |     |__ PPTX
    //  |     |__ PST
    //  |     |__ TXT
    //  |     |__ XLS
    //  |     |__ XLSX
    //  |
    //  |__ Audio
    //  |     |__ FLAC
    //  |     |__ M4A
    //  |     |__ MP3
    //  |     |__ WAV
    //  |
    //  |__ Pictures
    //  |     |__ BMP
    //  |     |__ JFIF
    //  |     |__ JPEG
    //  |     |__ JPG
    //  |     |__ PNG
    //  |
    //  |__ Source
    //  |
    //  |__ SourceUnhandled
    //  |
    //  |__ Videos
    //  |     |__ AVI
    //  |     |__ FLV
    //  |     |__ GIF
    //  |     |__ MKV
    //  |     |__ MOV
    //  |     |__ MP4
    //  |     |__ MPG
    //  |     |__ WEBM
    //  |
    //  |__ Sorter.exe (Self)
    //=========================

    // All folders and subfolders that need to be created
    const int folderStructCount = 6;
    const char* baseFolderStructure[folderStructCount] =
    { "Documents\\", "Audio\\", "Pictures\\", "Videos\\", "Source\\", "SourceUnhandled\\" };

    if (!exists("Source\\")) {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Source folder did not exist, and was created at the beginning of this run.\nPlease add all files that need to be sorted to 'Source,' and run the program again.\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        freshSource = true;
    }

    // Creates base folders
    for (int i = 0; i < folderStructCount; i++) {
        // If the folder doesn't exist
        if (!exists(baseFolderStructure[i])) create_directory(baseFolderStructure[i]);
    }

    std::string typeArray[] = { "Pictures", "Videos", "Documents", "Audio" };
    std::string allTypeArray[PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES + AUDIO_FILE_TYPES];

    std::copy(picFileTypes, picFileTypes + PIC_FILE_TYPES, allTypeArray);
    std::copy(vidFileTypes, vidFileTypes + VID_FILE_TYPES, allTypeArray + PIC_FILE_TYPES);
    std::copy(docFileTypes, docFileTypes + DOC_FILE_TYPES, allTypeArray + PIC_FILE_TYPES + VID_FILE_TYPES);
    std::copy(audioFileTypes, audioFileTypes + AUDIO_FILE_TYPES, allTypeArray + PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES);

    int currentIndex = 0;

    for (int i = 0; i < (PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES + AUDIO_FILE_TYPES); i++) {

        // Get the count of the current type
        int correlatedCount = 0;
        if (i < PIC_FILE_TYPES) correlatedCount = PIC_FILE_TYPES;
        else if (i < PIC_FILE_TYPES + VID_FILE_TYPES) correlatedCount = VID_FILE_TYPES;
        else if (i < PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES) correlatedCount = DOC_FILE_TYPES;
        else correlatedCount = AUDIO_FILE_TYPES;

        // Get the current folder name
        std::string folderName = typeArray[currentIndex];

        // Create the folder if it doesn't exist
        if (!exists(folderName)) create_directory(folderName);

        for (int j = 0; j < correlatedCount; j++) {

            allFileTypes->push_back(allTypeArray[i]);
            pathAppends->push_back(folderName);

            std::string folderPath = folderName + "\\" + allTypeArray[i];
            if (!exists(folderPath)) create_directory(folderPath);
        }

        if (i == PIC_FILE_TYPES - 1 || i == PIC_FILE_TYPES + VID_FILE_TYPES - 1 || i == PIC_FILE_TYPES + VID_FILE_TYPES + DOC_FILE_TYPES - 1) {
            currentIndex++;
        }
    }
}

static void cleanSource() {
    using namespace std::filesystem;

    if (postClean && !freshSource) {
        // Starts the removal of the source directory
        auto startClean = std::chrono::steady_clock::now();
        std::cout << "\nStarting clean-up process, please do not close the program or press any buttons.\n";

        try {
            // Remove the source directory and its contents
            remove_all(sourcePath);

            // Loop ensures that the program does not continue until source is deleted
            while (exists(sourcePath)) {
                // Wait until the directory is deleted
            }

            // Creates the source directory again
            create_directory(sourcePath);

            // Last clock ends
            auto cleanDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startClean);
            std::cout << "Clean-up and rebuild finished in " << float(cleanDuration.count() / 1000.0) << " seconds.\n";
        }
        catch (const std::exception& ex) {
            std::cerr << "Error during clean-up: " << ex.what() << std::endl;
        }
    }
    else if (postClean && freshSource) {
        std::cout << "\nSkipping post-clean as the source was freshly built\n";
    }

    // Total timer ended
    auto durationExec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startExec);
    std::cout << "Sorting program completed in " << float(durationExec.count() / 1000.0) << " seconds.\n";
}

static std::optional<std::string> duplicateDetector(const std::string& filePath, const std::string& alternatePath) {
    // If the file doesn't exist, return it as a valid new path
    if (!std::filesystem::exists(filePath)) return filePath;

    // If the file does exist, iterate through until it doesn't
    for (int j = 1; j < MAX_SIZE; j++) {
        // Creates a new string for the file, "Demo.txt" would become "Demo (1).txt"
        std::string newPath = replace(alternatePath, replaceReg, std::to_string(j));
        // If the edited file path doesn't exist, it is valid; return it
        if (!std::filesystem::exists(newPath)) return newPath;
    }

    // If no valid path is found, return std::nullopt
    return std::nullopt;
}

static void copyHelper(const std::string& source, const std::string& fileName, const std::string& checkPath, const std::string& alternatePath) {
    if (!std::filesystem::exists(source)) return;
    std::optional<std::string> newPathOpt = duplicateDetector(checkPath, alternatePath);
    if (!newPathOpt) return;

    try {
        std::filesystem::copy_file(source, *newPathOpt);
    }
    catch (const std::exception& ex) {
        std::cerr << "Error copying file: " << ex.what() << std::endl;
    }
}

static std::string getFileName(std::string fileWithExt, std::string fileExt) {
    //If there is no file extension, there will not be a "." in the filename
    int mod = 0;
    if (fileExt.length() != 0) { mod = 1; }
    return(fileWithExt.substr(0, fileWithExt.length() - (fileExt.length() + mod)));
}

static void getFolderSize() {
    using namespace std::filesystem;

    // Size_T for source folder size
    size_t size = 0;

    // Timer
    auto folderSizeStart = std::chrono::steady_clock::now();

    try {
        // Iterates over every file - adds its size
        for (const auto& entry : recursive_directory_iterator(sourcePath)) {
            if (is_regular_file(entry)) {
                size += file_size(entry);
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Print the size in GB with 2 decimal places
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Source folder contains " << static_cast<double>(size) / 1024 / 1024 / 1024 << " GB of data.\n";

    auto folderSizeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - folderSizeStart);
    std::cout << "Calculated source folder size in " << folderSizeDuration.count() / 1000.0 << " seconds.\n";
}

static void sort(fileHandler fileHandler) {
    if (fileHandler.count > 0) {
        for (int i = 0; i < fileHandler.count; i++) {
            std::string fileName = getFileName(fileHandler.fileNames.at(i), fileHandler.fileType);
            copyHelper(fileHandler.fullPath.at(i), fileName,
                fileHandler.pathAppendFileType + "/" + fileHandler.fileType + "/" + fileName + "." + fileHandler.fileType,
                fileHandler.pathAppendFileType + "/" + fileHandler.fileType + "/" + fileName + " (%FILL_INT_HERE%)" + "." + fileHandler.fileType);
            totalSorts++;
            mtx.lock();
            std::cout << "\r\rSorting... (" << totalSorts << " / " << sourcePathCount << ")";
            mtx.unlock();
        }
    }
}

static void sortAll() {
    auto startSortAll = std::chrono::steady_clock::now();
    std::vector<std::thread> sorterThreads;

    // Copying each fileHandler for each thread
    for (fileHandler fh : fileHandlers) {
        sorterThreads.push_back(std::thread(sort, fh));
    }

    for (auto& thread : sorterThreads) {
        thread.join();
    }

    auto durationSortAll = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - startSortAll);
    std::cout << "\nSorted " << sourcePathCount << " files/folders in "
        << float(durationSortAll.count() / 1000.00) << " seconds.\n";
}


static void sortArrays() {
    // Var for the index of the filetype in the 'all-types' array
    int fileExtIndex;
    // Intra-loop vars
    std::string lastFileExt;
    int lastIndex = 0;

    // For every file that was added to the sourceArray
    for (int i = 0; i < sourcePathCount; ++i) {
        // Grab the current full file path
        const std::string& currentFileSource = sourcePathFilesFullPath[i];

        // String to hold filetype before the file is sorted into its array
        std::string fileExt;
        if (auto pos = currentFileSource.find_last_of('.'); pos != std::string::npos) {
            // Gets the supposed file type
            std::string posFileType = currentFileSource.substr(pos + 1);
            // Will not return file types longer than 6 chars
            if (posFileType.length() <= 6) fileExt = std::move(posFileType);
        }

        // Convert fileExt to uppercase
        std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::toupper);

        // Don't sort DLL files or SYS files
        if (fileExt == "DLL" || fileExt == "SYS" || fileExt == "BIN") continue;

        // Only sort file if no onlySortTypes specified or if the file extension is in the list
        if (!onlySortTypes.empty() &&
            std::find(onlySortTypes.begin(), onlySortTypes.end(), fileExt) == onlySortTypes.end()) {
            continue; // Skip this file if its type is not in onlySortTypes
        }

        // Saves calculation time if multiple files in a row have the same file type
        if (fileExt == lastFileExt) {
            fileExtIndex = lastIndex;
        }
        else {
            // Finds the index of the filetype in the map
            auto it = std::find(allFileTypes->begin(), allFileTypes->end(), fileExt);
            fileExtIndex = static_cast<int>(std::distance(allFileTypes->begin(), it));
            lastFileExt = fileExt;
            lastIndex = fileExtIndex;
        }

        // If the file type is not in the list, it will be put into SourceUnhandled
        if (fileExtIndex == DIF_FILE_TYPES) {
            // Don't include folders
            if (!std::filesystem::is_directory(currentFileSource)) {
                // Grabs the filename
                std::string fileName = getFileName(currentFileSource, fileExt);

                // Copies the file
                copyHelper(currentFileSource, fileName,
                    basePath + "\\SourceUnhandled\\" + currentFileSource,
                    basePath + "\\SourceUnhandled\\" + fileName + " (%FILL_INT_HERE%)" + "." + fileExt);

                // Increments
                ++totalSorts;
                std::cout << "\rSorted " << totalSorts << " unsupported files. (" << totalSorts << " total)";
            }
        }
        else {
            fileHandlers[fileExtIndex].fullPath.push_back(currentFileSource);
            fileHandlers[fileExtIndex].fileNames.push_back(sourcePathFileNames[i]);
            fileHandlers[fileExtIndex].incrementCount();
        }
    }

    if (totalSorts > 0) std::cout << "\n";

    auto arrayTimerDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startArrayTimer);
    std::cout << "Added " << sourcePathCount << " files to internal array in " << float(arrayTimerDuration.count() / 1000.0) << " seconds.\n";
}

static void fillSourceArray(const std::string& path) {
    startArrayTimer = std::chrono::steady_clock::now();

    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (!entry.is_regular_file()) continue;
            std::string fullPath = entry.path().string();
            sourcePathFilesFullPath.push_back(std::move(fullPath));
            sourcePathFileNames.push_back(entry.path().filename().string());
            ++sourcePathCount;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

static void handleConsoleParam(const std::string param) {
    if (param == "-postclean") {
        postClean = true;
    }
    else if (param.rfind("-onlysort", 0) == 0) {  // if param starts with "-onlysort"
        std::string fileTypesStr;
        // Check if the argument includes an equals sign
        if (param.length() > 9 && param[9] == '=') {
            fileTypesStr = param.substr(10);  // get substring after "-onlysort="
        }
        else {
            // Alternatively, you might decide to get the next argv[] element.
            // For now, if not provided, leave fileTypesStr empty or handle an error.
        }

        // Split the comma-separated list
        std::istringstream ss(fileTypesStr);
        std::string token;
        while (std::getline(ss, token, ',')) {
            token = trim(token);
            // Convert token to uppercase
            std::transform(token.begin(), token.end(), token.begin(), ::toupper);
            if (!token.empty()) {
                onlySortTypes.push_back(token);
            }
        }
    }
    else {
		std::cerr << "Unknown parameter: " << param << std::endl;
		std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
	SetConsoleTitleA("Sorter");

	//Handles flag(s)
	for (int i = 1; i < argc; ++i) {
		handleConsoleParam(argv[i]);
	}

	//Will build the folder structure that the program uses
	buildFileStructure();

	//Fills the vector with FileHandlers of each supported type
	for (int i = 0; i < DIF_FILE_TYPES; i++) {
		fileHandlers.push_back(fileHandler(allFileTypes->at(i), pathAppends->at(i), basePath));
	}

	//Adds files into arrays to be sorted
	fillSourceArray(sourcePath);

	sortArrays();

	//Calculates size of the source folder
	getFolderSize();

	//Sorts all files (including folders)
	sortAll();

	//Cleans source if the flag was passed
	cleanSource();

	//Exit sequence
	std::cout << "\nPress any key to exit...";
	char storeExitChar = getchar();
}