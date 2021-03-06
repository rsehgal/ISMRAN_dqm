/*
**	Filename : Helpers.cpp
**	2021-11-16
**	username : rsehgal
*/
#include "Helpers.h"
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ismran {

std::vector<std::string> GetStringTokens(std::string pathString, char delim) {
  std::vector<std::string> tokensVector;
  std::stringstream ss(pathString);
  std::string token;
  while (getline(ss, token, delim)) {
    tokensVector.push_back(token);
  }
  return tokensVector;
}

std::string GetPath_StartingFromMountPoint(std::string pathString) {
  std::vector<std::string> tokensVector = GetStringTokens(pathString);
  std::string reqPath = "";
  for (unsigned int i = 3; i < tokensVector.size(); i++) {
    reqPath += "/"+tokensVector[i];
  }
  return reqPath;
}

std::string GetAmbarMountPoint_ParentDir() { return "/var/www/html/web"; }

} // namespace ismran
