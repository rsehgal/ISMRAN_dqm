/*
**	Filename : Test_List_Files_In_Directory.cpp
**	2021-11-10
**	username : rsehgal
*/

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

int main() {
    string path = "/home/rsehgal/DevShare";
    //string path = "/home/rsehgal/ISMRAN_dqm/build";

    for (const auto & file : directory_iterator(path))
        cout << file.path() << endl;

    return EXIT_SUCCESS;
}

