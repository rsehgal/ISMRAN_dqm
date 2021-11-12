#include <iostream>
#include <vector>
#include <string>

using std::cout; using std::cin;
using std::endl; using std::vector;
#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace FS=std::experimental::filesystem;
#else
#include <filesystem>
namespace FS=std::filesystem;
#endif
using std::string;

int main() {
    vector<string> files_to_check = {"/home/rsehgal/ISMRAN_Code/ISMRAN_dqm/sourceDir/test1.txt"};

    for (const auto &file : files_to_check) {
        FS::exists(file) ? cout << "Exists\n" : cout << "Doesn't exist\n";
    }

    return EXIT_SUCCESS;
}

