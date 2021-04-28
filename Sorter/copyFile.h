#pragma once
#include <string>
#include <fstream>

void copyFile(std::string source, std::string destination) {
	//The input file
	std::ifstream src(source);

	//The output file
	std::ofstream dst(destination, std::ios::binary);

	//Copies input to output
	dst << src.rdbuf();

	//Precaution to avoid mem overflow
	dst.close();
	src.close();
}