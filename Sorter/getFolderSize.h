#include <filesystem>

void getFolderSize(size_t &size, std::string path) {
    using namespace std::filesystem;
    for (recursive_directory_iterator it(path);
        it != recursive_directory_iterator();
        ++it)
    {
        if (!is_directory(*it))
            size += file_size(*it);
    }
}