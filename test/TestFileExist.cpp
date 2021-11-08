#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using std::cout; using std::cin;
using std::endl; using std::vector;
using std::filesystem::exists;
using std::string;

int main() {
    vector<string> files_to_check = {"/home/rsehgal/ISMRAN_Code/ISMRAN_dqm/sourceDir/test1.txt"};

    for (const auto &file : files_to_check) {
        exists(file) ? cout << "Exists\n" : cout << "Doesn't exist\n";
    }

    return EXIT_SUCCESS;
}

