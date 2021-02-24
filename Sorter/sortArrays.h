#pragma once
#include <string>
#include "programWideVars.h"
#include "getFileExtension.h"
#include <iostream>

//String to hold filetype before the file is sorted into its array
std::string fileExt;

void sortArrays()
{
	// For every file that was added to the sourceArray
	// (every file that existed in ../Source/
	for (int i = 0; i < sourcePathCount; i++)
	{
		//Get the file extension of the file
		fileExt = getFileExtension(sourcePathFilesFullPath[i]);

		// Given the filetype, find which array it should be put in
		// (if any), add it, then +1 to the count of that filetype

		// fileExt is uppered and lowered to account for certain
		// programs writing the files as such (mostly seen in JPG,
		// PNG), included for all to be safe
		if (fileExt == "gif" | fileExt == "GIF")
		{			
			gifFullPath[gifCount] = sourcePathFilesFullPath[i];
			gifFileNames[gifCount] = sourcePathFileNames[i];
			gifCount++;
		}
		else if (fileExt == "bmp" | fileExt == "BMP")
		{
			bmpFullPath[bmpCount] = sourcePathFilesFullPath[i];
			bmpFileNames[bmpCount] = sourcePathFileNames[i];
			bmpCount++;
		}
		else if (fileExt == "jfif" | fileExt == "JFIF")
		{
			jfifFullPath[jfifCount] = sourcePathFilesFullPath[i];
			jfifFileNames[jfifCount] = sourcePathFileNames[i];
			jfifCount++;
		}
		else if (fileExt == "jpeg" | fileExt == "JPEG")
		{
			jpegFullPath[jpegCount] = sourcePathFilesFullPath[i];
			jpegFileNames[jpegCount] = sourcePathFileNames[i];
			jpegCount++;
		}
		else if (fileExt == "jpg" | fileExt == "JPG")
		{
			jpgFullPath[jpgCount] = sourcePathFilesFullPath[i];
			jpgFileNames[jpgCount] = sourcePathFileNames[i];
			jpgCount++;
		}
		else if (fileExt == "png" | fileExt == "PNG")
		{
			pngFullPath[pngCount] = sourcePathFilesFullPath[i];
			pngFileNames[pngCount] = sourcePathFileNames[i];
			pngCount++;
		}
		else if (fileExt == "avi" | fileExt == "AVI")
		{
			aviFullPath[aviCount] = sourcePathFilesFullPath[i];
			aviFileNames[aviCount] = sourcePathFileNames[i];
			aviCount++;
		}
		else if (fileExt == "flv" | fileExt == "FLV")
		{
			flvFullPath[flvCount] = sourcePathFilesFullPath[i];
			flvFileNames[flvCount] = sourcePathFileNames[i];
			flvCount++;
		}
		else if (fileExt == "mkv" | fileExt == "MKV")
		{
			mkvFullPath[mkvCount] = sourcePathFilesFullPath[i];
			mkvFileNames[mkvCount] = sourcePathFileNames[i];
			mkvCount++;
		}
		else if (fileExt == "mov" | fileExt == "MOV")
		{
			movFullPath[movCount] = sourcePathFilesFullPath[i];
			movFileNames[movCount] = sourcePathFileNames[i];
			movCount++;
		}
		else if (fileExt == "mp4" | fileExt == "MP4")
		{
			mp4FullPath[mp4Count] = sourcePathFilesFullPath[i];
			mp4FileNames[mp4Count] = sourcePathFileNames[i];
			mp4Count++;
		}
		else if (fileExt == "mpg" | fileExt == "MPG")
		{
			mpgFullPath[mpgCount] = sourcePathFilesFullPath[i];
			mpgFileNames[mpgCount] = sourcePathFileNames[i];
			mpgCount++;
		}
		else if (fileExt == "webm" | fileExt == "WEBM")
		{
			webmFullPath[webmCount] = sourcePathFilesFullPath[i];
			webmFileNames[webmCount] = sourcePathFileNames[i];
			webmCount++;
		}
		else if (fileExt == "doc" | fileExt == "DOC")
		{
			docFullPath[docCount] = sourcePathFilesFullPath[i];
			docFileNames[docCount] = sourcePathFileNames[i];
			docCount++;
		}
		else if (fileExt == "docx" | fileExt == "DOCX")
		{
			docxFullPath[docxCount] = sourcePathFilesFullPath[i];
			docxFileNames[docxCount] = sourcePathFileNames[i];
			docxCount++;
		}
		else if (fileExt == "pdf" | fileExt == "PDF")
		{
			pdfFullPath[pdfCount] = sourcePathFilesFullPath[i];
			pdfFileNames[pdfCount] = sourcePathFileNames[i];
			pdfCount++;
		}
		else if (fileExt == "ppt" | fileExt == "PPT")
		{
			pptFullPath[pptCount] = sourcePathFilesFullPath[i];
			pptFileNames[pptCount] = sourcePathFileNames[i];
			pptCount++;
		}
		else if (fileExt == "pptx" | fileExt == "PPTX")
		{
		pptxFullPath[pptxCount] = sourcePathFilesFullPath[i];
		pptxFileNames[pptxCount] = sourcePathFileNames[i];
		pptxCount++;
		}
		else if (fileExt == "pst" | fileExt == "PST")
		{
		pstFullPath[pstCount] = sourcePathFilesFullPath[i];
		pstFileNames[pstCount] = sourcePathFileNames[i];
		pstCount++;
		}
		else if (fileExt == "xls" | fileExt == "XLS")
		{
		xlsFullPath[xlsCount] = sourcePathFilesFullPath[i];
		xlsFileNames[xlsCount] = sourcePathFileNames[i];
		xlsCount++;
		}
		else if (fileExt == "xlsx" | fileExt == "XLSX")
		{
		xlsxFullPath[xlsxCount] = sourcePathFilesFullPath[i];
		xlsxFileNames[xlsxCount] = sourcePathFileNames[i];
		xlsxCount++;
		}
		else if (fileExt == "flac" | fileExt == "FLAC")
		{
		flacFullPath[flacCount] = sourcePathFilesFullPath[i];
		flacFileNames[flacCount] = sourcePathFileNames[i];
		flacCount++;
		}
		else if (fileExt == "m4a" | fileExt == "M4A")
		{
		m4aFullPath[m4aCount] = sourcePathFilesFullPath[i];
		m4aFileNames[m4aCount] = sourcePathFileNames[i];
		m4aCount++;
		}
		else if (fileExt == "mp3" | fileExt == "MP3")
		{
		mp3FullPath[mp3Count] = sourcePathFilesFullPath[i];
		mp3FileNames[mp3Count] = sourcePathFileNames[i];
		mp3Count++;
		}
		else if (fileExt == "wav" | fileExt == "WAV")
		{
		wavFullPath[wavCount] = sourcePathFilesFullPath[i];
		wavFileNames[wavCount] = sourcePathFileNames[i];
		wavCount++;
		}
		else
		{
			//Deals with nested folders or otherwise broken files,
			//will dump them into SourceUnhandled

			//Creates two directories to be used in copying
			std::string sourceDir = sourcePathFilesFullPath[i];
			std::string destDir = basePath + "SourceUnhandled/"+ sourcePathFileNames[i];
			//The input file
			std::ifstream src(sourceDir, std::ios::binary);
			//The output file
			std::ofstream dst(destDir, std::ios::binary);

			//Copies input to output
			dst << src.rdbuf();
			src.close();
			dst.close();
		}
	}
}
