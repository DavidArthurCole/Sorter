#pragma once
#include <string>
#include <Windows.h>
#include <boost/filesystem.hpp>
#include <pathcch.h>

//Namespace to use for the file adding iteration
namespace fs = boost::filesystem;

//Size used to create an array (aka maximum amount of files that can be handled in one iteration)
const int MAX_SIZE = 16384;

//THESE WILL NEED TO BE EDITED EVERYTIME A NEW FILETYPE IS ADDED
//===========================================================================================================
const int PIC_FILE_TYPES = 5;
const int VID_FILE_TYPES = 8;
const int DOC_FILE_TYPES = 8;
const int AUDIO_FILE_TYPES = 4;

const int DIF_FILE_TYPES = 25;

const std::string picFileTypes[PIC_FILE_TYPES] = { "BMP","JFIF","JPEG","JPG","PNG" };
const std::string vidFileTypes[VID_FILE_TYPES] = { "AVI", "FLV","GIF","MKV","MOV","MP4","MPG", "WEBM" };
const std::string docFileTypes[DOC_FILE_TYPES] = { "DOC", "DOCX", "PDF", "PPT", "PPTX","PST","XLS","XLSX" };
const std::string audioFileTypes[AUDIO_FILE_TYPES] = { "FLAC", "M4A", "MP3", "WAV" };
//===========================================================================================================

std::string allFileTypes[DIF_FILE_TYPES];

void populateAllTypesArray()
{
	//Used in cases other than referencing the four arrays
	int h = 0;

	//Adds picture file types to the 'all' array
	for (int i = 0; i < PIC_FILE_TYPES; i++)
	{
		allFileTypes[h] = picFileTypes[i];
		h++;
	}
	//Adds video file types to the 'all' array
	for (int i = 0; i < VID_FILE_TYPES; i++)
	{
		allFileTypes[h] = vidFileTypes[i];
		h++;
	}
	//Adds document file types to the 'all' array
	for (int i = 0; i < DOC_FILE_TYPES; i++)
	{
		allFileTypes[h] = docFileTypes[i];
		h++;
	}
	//Adds audio file types to the 'all' array
	for (int i =0 ; i < AUDIO_FILE_TYPES; i++)
	{
		allFileTypes[h] = audioFileTypes[i];
		h++;
	}
}

std::string getExePath()
{
	//Gets the full path, including the executable name
	std::string path = fs::system_complete(fs::path(__argv[0])).string();
	//Replaces \ with / in the path, needed for boost
	std::replace(path.begin(), path.end(), '\\', '/');
	//Returns the path without the .exe
	return(path.substr(0, path.find_last_of("/") + 1));
}

//Working directory
std::string basePath = getExePath();

//Files that need to be sorted
std::string sourcePath = basePath + "Source/";

//Path to log files
std::string logsPath = basePath + "Logs/";

//INTS TO STORE HOW MANY OF EACH FILE TYPE HAVE BEEN FOUND
int bmpCount = 0, jfifCount = 0, jpegCount = 0, jpgCount = 0, pngCount = 0;

int aviCount = 0, flvCount = 0, mkvCount = 0, movCount = 0, mp4Count = 0, mpgCount = 0, webmCount = 0, gifCount = 0;

int pdfCount = 0, xlsCount = 0, xlsxCount = 0, pptCount = 0, pptxCount = 0, docCount = 0, docxCount = 0, pstCount = 0;

int flacCount = 0, m4aCount = 0, mp3Count = 0, wavCount = 0;

//INTS TO STORE MAX NUMBER IN NAMES OF EACH FILETYPE 
int currentMaxes[DIF_FILE_TYPES];

int currentMaxGif = -1;

int currentMaxBmp = -1, currentMaxJfif = -1, currentMaxJpeg = -1, currentMaxJpg = -1, currentMaxPng = -1;

int currentMaxAvi = -1, currentMaxFlv = -1, currentMaxMkv = -1, currentMaxMov = -1, currentMaxMp4 = -1, currentMaxMpg = -1, currentMaxWebm = -1;

int currentMaxPdf = -1, currentMaxXls = -1, currentMaxXlsx = -1, currentMaxPpt = -1, currentMaxPptx = -1, currentMaxDoc = -1, currentMaxDocx = -1, currentMaxPst = -1;

int currentMaxFlac = -1, currentMaxM4a = -1, currentMaxMp3 = -1, currentMaxWav = -1;

//Stores all files that need to be sorted as a path
std::string sourcePathFilesFullPath[MAX_SIZE * DIF_FILE_TYPES];

//Stores all files that need to be sorted as their file name
std::string sourcePathFileNames[MAX_SIZE * DIF_FILE_TYPES];

//ALL THE ARRAYS TO HOLD DIFFERENT FILETYPES

//Pics
std::string bmpFullPath[MAX_SIZE], bmpFileNames[MAX_SIZE];
std::string jfifFullPath[MAX_SIZE], jfifFileNames[MAX_SIZE];
std::string jpegFullPath[MAX_SIZE], jpegFileNames[MAX_SIZE];
std::string jpgFullPath[MAX_SIZE], jpgFileNames[MAX_SIZE];
std::string pngFullPath[MAX_SIZE], pngFileNames[MAX_SIZE];

//Videos
std::string aviFullPath[MAX_SIZE], aviFileNames[MAX_SIZE];
std::string flvFullPath[MAX_SIZE], flvFileNames[MAX_SIZE];
std::string mkvFullPath[MAX_SIZE], mkvFileNames[MAX_SIZE];
std::string movFullPath[MAX_SIZE], movFileNames[MAX_SIZE];
std::string mp4FullPath[MAX_SIZE], mp4FileNames[MAX_SIZE];
std::string mpgFullPath[MAX_SIZE], mpgFileNames[MAX_SIZE];
std::string webmFullPath[MAX_SIZE], webmFileNames[MAX_SIZE];
std::string gifFullPath[MAX_SIZE], gifFileNames[MAX_SIZE];

//Documents
std::string pdfFullPath[MAX_SIZE], pdfFileNames[MAX_SIZE];
std::string xlsFullPath[MAX_SIZE], xlsFileNames[MAX_SIZE];
std::string xlsxFullPath[MAX_SIZE], xlsxFileNames[MAX_SIZE];
std::string pptFullPath[MAX_SIZE], pptFileNames[MAX_SIZE];
std::string pptxFullPath[MAX_SIZE], pptxFileNames[MAX_SIZE];
std::string docFullPath[MAX_SIZE], docFileNames[MAX_SIZE];
std::string docxFullPath[MAX_SIZE], docxFileNames[MAX_SIZE];
std::string pstFullPath[MAX_SIZE], pstFileNames[MAX_SIZE];

//Audio
std::string flacFullPath[MAX_SIZE], flacFileNames[MAX_SIZE];
std::string m4aFullPath[MAX_SIZE], m4aFileNames[MAX_SIZE];
std::string mp3FullPath[MAX_SIZE], mp3FileNames[MAX_SIZE];
std::string wavFullPath[MAX_SIZE], wavFileNames[MAX_SIZE];

//Counts how many files are in sourcePath
int sourcePathCount = 0;

//Random boolean logic to prevent removing a freshly generated sourcedir
bool freshSource = false;

//Size_T for source folder size
size_t sourceSize;