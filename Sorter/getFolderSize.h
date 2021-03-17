#include <filesystem>

void getFolderSize(size_t size, std::string path) {
    using namespace std::filesystem;

    //Timer
    auto folderSizeStart = std::chrono::steady_clock::now();

    for (recursive_directory_iterator it(path);
        it != recursive_directory_iterator();
        ++it)
    {
        if (!is_directory(*it))
            size += file_size(*it);
    }

    //Casts the size to a double
    double sourceSizeDouble = static_cast<double>(size);
    //This is some ridiculously disgusting code, but it just prints 2 decimal places in terms of GB - this will equal the RAW BYTE SIZE
    std::cout << "Source folder contains " << ((double)(int)((sourceSizeDouble / 1024000000) * 100) / 100) << " GB of data\n";

    auto folderSizeEnd = std::chrono::steady_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(folderSizeEnd - folderSizeStart);
    std::cout << "Calculated source folder size in " << float(duration5.count() / 1000.00) << " seconds.\n";
}