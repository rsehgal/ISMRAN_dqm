/*
**	Filename : Helpers.h
**	2021-11-16
**	username : rsehgal
*/
#ifndef Helpers_h
#define Helpers_h

#include <string>
#include <vector>
namespace ismran {
extern std::vector<std::string> GetStringTokens(std::string pathString,char delim='/');
extern std::string GetPath_StartingFromMountPoint(std::string pathString);
extern std::string GetAmbarMountPoint_ParentDir();
extern std::string GetRemoteDataDirectory_OnDAQMachine();
} // namespace ismran
#endif
