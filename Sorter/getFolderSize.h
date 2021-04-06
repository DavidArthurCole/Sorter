#include <filesystem>
#include "globalVars.h"

void getFolderSize() {
    using namespace std::filesystem;

    //Size_T for source folder size
    size_t size = 0;

    //Timer
    auto folderSizeStart = std::chrono::steady_clock::now();

    //Iterates over every file - adds its size. If an error occurs, it is printed (this will happen with null byte files, non-ascii chars, etc.)
    try { for (recursive_directory_iterator it(sourcePath); it != recursive_directory_iterator(); ++it) if (!is_directory(*it)) size += file_size(*it); }
    catch (std::exception e) { std::cout << e.what() << "\n"; }

    //Casts the size to a double
    double sourceSizeDouble = static_cast<double>(size);
    //This is some ridiculously disgusting code, but it just prints 2 decimal places in terms of GB - this will equal the RAW BYTE SIZE
    std::cout << "Source folder contains " << ((double)(int)((sourceSizeDouble / 1024000000) * 100) / 100) << " GB of data\n";

    auto folderSizeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - folderSizeStart);
    std::cout << "Calculated source folder size in " << float(folderSizeDuration.count() / 1000.00) << " seconds.\n";
}