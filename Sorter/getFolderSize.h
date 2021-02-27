#include <boost/filesystem.hpp>

void getFolderSize(size_t &size, std::string path) {
    namespace bf = boost::filesystem;
    for (bf::recursive_directory_iterator it(path);
        it != bf::recursive_directory_iterator();
        ++it)
    {
        if (!bf::is_directory(*it))
            size += bf::file_size(*it);
    }
}