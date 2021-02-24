#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "programWideVars.h"
#include "fillSourceArray.h"

//Void for sorting files
void sortFiles(std::string fileFullPath[MAX_SIZE], std::string fileFileNames[MAX_SIZE], std::string fileType, int currentMaxPic, int picCount, int type);

void sortAll()
{

	// Will only run each sort if files of that type exist(ed) in source
	if (gifCount > 0)
	{
		sortFiles(gifFullPath, gifFileNames, "gif", currentMaxGif, gifCount, 1);
	}
	if (jfifCount > 0)
	{
		sortFiles(jfifFullPath, jfifFileNames, "jfif", currentMaxJfif, jfifCount, 0);
	}
	if (bmpCount > 0)
	{
		sortFiles(bmpFullPath, bmpFileNames, "bmp", currentMaxBmp, bmpCount, 0);
	}
	if (jpegCount > 0)
	{
		sortFiles(jpegFullPath, jpegFileNames, "jpeg", currentMaxJpeg, jpegCount, 0);
	}
	if (jpgCount > 0)
	{
		sortFiles(jpgFullPath, jpgFileNames, "jpg", currentMaxJpg, jpgCount, 0);
	}
	if (pngCount > 0)
	{
		sortFiles(pngFullPath, pngFileNames, "png", currentMaxPng, pngCount, 0);
	}
	if (aviCount > 0)
	{
		sortFiles(aviFullPath, aviFileNames, "avi", currentMaxAvi, aviCount, 1);
	}
	if (flvCount > 0)
	{
		sortFiles(flvFullPath, flvFileNames, "flv", currentMaxFlv, flvCount, 1);
	}
	if (mkvCount > 0)
	{
		sortFiles(mkvFullPath, mkvFileNames, "mkv", currentMaxMkv, mkvCount, 1);
	}
	if (movCount > 0)
	{
		sortFiles(movFullPath, movFileNames, "mov", currentMaxMov, movCount, 1);
	}
	if (mp4Count > 0)
	{
		sortFiles(mp4FullPath, mp4FileNames, "mp4", currentMaxMp4, mp4Count, 1);
	}
	if (mpgCount > 0)
	{
		sortFiles(mpgFullPath, mpgFileNames, "mpg", currentMaxMpg, mpgCount, 1);
	}
	if (webmCount > 0)
	{
		sortFiles(webmFullPath, webmFileNames, "webm", currentMaxWebm, webmCount, 1);
	}
	if (docCount > 0)
	{
		sortFiles(docFullPath, docFileNames, "doc", currentMaxDoc, docCount, 2);
	}
	if (docxCount > 0)
	{
		sortFiles(docxFullPath, docxFileNames, "docx", currentMaxDocx, docxCount, 2);
	}
	if (pdfCount > 0)
	{
		sortFiles(pdfFullPath, pdfFileNames, "pdf", currentMaxPdf, pdfCount, 2);
	}
	if (pptCount > 0)
	{
		sortFiles(pptFullPath, pptFileNames, "ppt", currentMaxPpt, pptCount, 2);
	}
	if (pptxCount > 0)
	{
		sortFiles(pptxFullPath, pptxFileNames, "pptx", currentMaxPptx, pptxCount, 2);
	}
	if (pstCount > 0)
	{
		sortFiles(pstFullPath, pstFileNames, "pst", currentMaxPst, pstCount, 2);
	}
	if (xlsCount > 0)
	{
		sortFiles(xlsFullPath, xlsFileNames, "xls", currentMaxXls, xlsCount, 2);
	}
	if (xlsxCount > 0)
	{
		sortFiles(xlsxFullPath, xlsxFileNames, "xlsx", currentMaxXlsx, xlsxCount, 2);
	}
	if (flacCount > 0)
	{
		sortFiles(flacFullPath, flacFileNames, "flac", currentMaxFlac, flacCount, 3);
	}
	if (m4aCount > 0)
	{
		sortFiles(m4aFullPath, m4aFileNames, "m4a", currentMaxM4a, m4aCount, 3);
	}
	if (mp3Count > 0)
	{
		sortFiles(mp3FullPath, mp3FileNames, "mp3", currentMaxMp3, mp3Count, 3);
	}
	if (wavCount > 0)
	{
		sortFiles(wavFullPath, wavFileNames, "wav", currentMaxWav, wavCount, 3);
	}
}

void sortFiles(std::string fileFullPath[MAX_SIZE], std::string fileFileNames[MAX_SIZE], std::string fileType, int currentMaxPic, int picCount, int type)
{
	//Type usage;
	// 0 - pictures
	// 1 - videos
	// 2 - documents
	// 3 - music/audio

	//Stores the current <type> log in a string so it can be
	//appended instead of overwritten
	std::ifstream inLogFile(logsPath + fileType + "_log.txt");
	std::string logFileStore((std::istreambuf_iterator<char>(inLogFile)), (std::istreambuf_iterator<char>()));
	inLogFile.close();

	//Differentiation between array index and current max number
	//Use h for referencing the array(s).
	int h = 0;
	std::cout << "Sorted 0 " << fileType << "s.";
	for (int i = currentMaxPic; i < (currentMaxPic + picCount); i++, h++)
	{
		//Creates two directories to be used in copying
		std::string sourceDir = fileFullPath[h];
		std::string fileTypeUpper = boost::to_upper_copy<std::string>(fileType);

		std::string destDir;
		switch (type)
		{
		case 0:
			destDir = basePath + "Pictures/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		case 1:
			destDir = basePath + "Videos/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		case 2:
			destDir = basePath + "Documents/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		case 3:
			destDir = basePath + "Audio/" + fileTypeUpper + "/" + fileTypeUpper + std::to_string(i) + "." + fileType;
			break;
		}

		//The input file
		std::ifstream src(sourceDir, std::ios::binary);
		//The output file
		std::ofstream dst(destDir, std::ios::binary);

		//Copies input to output
		dst << src.rdbuf();

		//Precaution to avoid mem overflow
		dst.close();
		src.close();

		logFileStore += fileFileNames[h] + " was renamed to " + fileTypeUpper + std::to_string(i) + "\n";
		std::cout << "\rSorted " << h + 1 << " " << fileType << "s.";
	}

	//Rewrites log file
	std::ofstream outLogFile(logsPath + fileType + "_log.txt");
	outLogFile << logFileStore;
	outLogFile.close();
	std::cout << "\n";
}