/*
**	Filename : Test_Tokenizing.cpp
**	2021-11-16
**	username : rsehgal
*/
/*
** 	Demo to tokenize a string (filePath)
*/
#include "Helpers_Dqm.h"
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char *argv[]) {

  std::string filePath = "/home/rsehgal/test/abct.txt";
  std::vector<std::string> tokensVector = ismran::GetStringTokens(filePath);

  for (unsigned int i = 0; i < tokensVector.size(); i++) {
    std::cout << tokensVector[i] << std::endl;
  }

  return 0;
}
