#pragma once
#include "globalVars.h"

void handleFlags(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		if (argv[i] == "-postclean") postClean = true;
		else if (argv[i] == "-nomaxes") noMaxes = true;
	}
}