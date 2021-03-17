#pragma once
#include <chrono>
#include <iostream>
#include "globalVars.h"
#include <string>
#include <stdlib.h>
#include <filesystem>

void cleanSource()
{
	using namespace std::filesystem;

	if (postClean && !freshSource)
	{
		//Starts the removal of the source directory
		auto start5 = std::chrono::steady_clock::now();
		std::cout << "\nStarting clean-up process, please do not close the program or press any buttons.\n";
		remove_all(sourcePath);

		//Loop ensures that the program does not continue until source is deleted
		bool sourceDeleted = false;
		while (sourceDeleted == false) if (!exists(sourcePath)) sourceDeleted = true;

		//Creates the source directory again
		create_directory(sourcePath);

		//Last clock ends
		auto end5 = std::chrono::steady_clock::now();
		auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
		std::cout << "Clean-up and rebuild finished in " << float(duration5.count() / 1000.00) << " seconds.\n";
	}
	else if (postClean && freshSource) std::cout << "\nSkipping post-clean as the source was freshly built\n";

	//Total timer ended
	auto endExec = std::chrono::steady_clock::now();
	auto durationExec = std::chrono::duration_cast<std::chrono::milliseconds>(endExec - startExec);
	std::cout << "Sorting program completed in " << float(durationExec.count() / 1000.00) << " seconds.\n";
}