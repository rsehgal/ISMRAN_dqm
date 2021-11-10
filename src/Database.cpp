/*
**	Filename : Database.cpp
**	2021-10-30
**	username : rsehgal
*/

#include "Database.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
namespace ismran {

Database::Database() {
  // TODO Auto-generated constructor stub
  fUsername = "barcq";
  fPasswd = "barcq";
  fDbName = "barcq";
  fQueryState = 0;

  fVerbose = true; // false;
  fServerIp = "127.0.0.1";
  mysql_init(&mysql);
}

Database::Database(std::string dbName, std::string uName, std::string passWd)
    : fUsername(uName), fPasswd(passWd), fDbName(dbName), fQueryState(0), fVerbose(false), fServerIp("127.0.0.1") {
  mysql_init(&mysql);
}
Database::Database(std::string serverIp, std::string dbName, std::string uName, std::string passWd)
    : fUsername(uName), fPasswd(passWd), fDbName(dbName), fQueryState(0), fVerbose(false), fServerIp(serverIp) {
  mysql_init(&mysql);
}

Database::~Database() {
  // TODO Auto-generated destructor stub
  // mysql_free_result(res);
  // mysql_close(conn);
}

int Database::Connect() {
  conn = mysql_real_connect(&mysql, fServerIp.c_str(), fUsername.c_str(), fPasswd.c_str(), fDbName.c_str(), 0, 0, 0);
  if (conn == NULL) {
    std::cout << mysql_error(&mysql) << std::endl << std::endl;
    return 1;
  } else {
    return 0;
  }
}

void Database::Set(char *serverIp, char *dbName, char *uName, char *passWd) {
  fDbName = std::string(dbName);
  fServerIp = std::string(serverIp);
  fUsername = std::string(uName);
  fPasswd = std::string(passWd);
}

void Database::SetServerIp(char *serverIp) { fServerIp = std::string(serverIp); }
void Database::SetDbName(char *dbName) { fDbName = std::string(dbName); }
void Database::SetUname(char *uName) { fUsername = std::string(uName); }
void Database::SetPasswd(char *passWd) { fPasswd = std::string(passWd); }

int Database::Delete(std::string tablename) {
  std::string query = "DELETE FROM " + tablename;
  return Query(query);
}

int Database::Update(std::string query) { return Query(query); }

int Database::Insert(std::string query) { return Query(query); }

int Database::InsertFileNameAndPath(std::string filePath, std::string fileName) {
  std::string query = "INSERT into ismran_files (filePath,fileName) values('" + filePath + "','" + fileName + "')";
  std::cout << "QUERY : " << query << std::endl;
  return Query(query);
}

int Database::Select(std::string query) { return Query<true>(query); }

int Database::GetNumOfRows(std::string tablename) {
  std::string query = "SELECT count(*) FROM " + tablename;
  return Count(query);
}

int Database::GetNumOfColumns(std::string tablename) {
  std::string query = "SELECT count(*) FROM INFORMATION_SCHEMA.Columns where TABLE_NAME = '" + tablename + "'";
  return Count(query);
}

int Database::Count(std::string query) {
  int queryReturnCode = Query<true>(query);
  row = mysql_fetch_row(res);
  return atoi(row[0]);
}

void Database::PrintQueryOutput() {
  std::cout << "MySQL Tables in mysql database." << std::endl << std::endl;
  while ((row = mysql_fetch_row(res)) != NULL) {
    // std::cout << left;
    std::cout << std::setw(18) << row[0] << std::setw(18)
              << row[1]
              //<< std::setw(18) << row[2]
              //<< std::setw(18) << row[3]
              << std::endl;
  }
}
std::vector<std::vector<std::string>> Database::GetVectorOfDeletedFiles() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select * from ismran_files");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;
  while ((row = mysql_fetch_row(res)) != NULL) {
    std::string fullFileName = std::string(row[0]) + "/" + std::string(row[1]);
    if (!std::filesystem::exists(fullFileName.c_str())) {
      vecOfFilePaths.push_back(std::string(row[0]));
      vecOfFileNames.push_back(std::string(row[1]));
    }
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

void Database::UpdateDbForDeletedFile(){
  std::vector<std::vector<std::string>> vecOfVecOfDeletedFileNames = GetVectorOfDeletedFiles();

  std::string concatenatedFileName="";
  for(unsigned int i = 0 ; i < vecOfVecOfDeletedFileNames[1].size() ; i++){
	if(i==vecOfVecOfDeletedFileNames[1].size()-1)
	concatenatedFileName+="'"+vecOfVecOfDeletedFileNames[1][i]+"'";
	else
	concatenatedFileName+="'"+vecOfVecOfDeletedFileNames[1][i]+"',";
  }
  std::cout << concatenatedFileName << std::endl;
  std::string query = "update ismran_files set fileExistInSourceDir=0 where fileName IN (" + concatenatedFileName + ")";
  Update(query);
}

std::vector<std::vector<std::string>> Database::GetVectorOfUnCopiedFiles() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select * from ismran_files where copied=0");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;

  while ((row = mysql_fetch_row(res)) != NULL) {
    vecOfFilePaths.push_back(std::string(row[0]));
    vecOfFileNames.push_back(std::string(row[1]));

    // vecOfFileNames.push_back(std::string(row[0]) + "/" + std::string(row[1]));
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

void Database::CalculateHashAndCopyFile(std::string sourcePath, std::string fileToCopy) {
  std::string fullFilePath = sourcePath + "/" + fileToCopy;
  std::ifstream infile("../files/copyPath.txt");
  std::string copyPath;
  infile >> copyPath;
  infile.close();
  system(("sha256sum " + fullFilePath + " > sha.txt").c_str());
  std::ifstream inHashFile("sha.txt");
  std::string hashCode;
  inHashFile >> hashCode;
  inHashFile.close();
  system(("cp " + fullFilePath + " " + copyPath).c_str());
  std::string query = "update ismran_files set copied=1 where fileName='" + fileToCopy + "'";
  Update(query);
  query = "update ismran_files set hashCode='" + hashCode + "' where fileName='" + fileToCopy + "'";
  Update(query);

  query = "update ismran_files set remoteFilePath='" + copyPath + "' where fileName='" + fileToCopy + "'";
  Update(query);
}

std::vector<std::vector<std::string>> Database::GetVectorOfFiles_ForIntegrityCheck() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select * from ismran_files where integrityCheck=0");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;

  while ((row = mysql_fetch_row(res)) != NULL) {
    vecOfFilePaths.push_back(std::string(row[6]));
    vecOfFileNames.push_back(std::string(row[1]));

    // vecOfFileNames.push_back(std::string(row[0]) + "/" + std::string(row[1]));
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

void Database::DoIntegrityCheck(std::string targetPath, std::string fileToCheck) {
  std::string fullFilePath = targetPath + "/" + fileToCheck;
  // std::cout << "File for Integrity check : " << fullFilePath << std::endl;
  system(("sha256sum " + fullFilePath + " > sha.txt").c_str());
  std::ifstream inHashFile("sha.txt");
  std::string hashCode;
  inHashFile >> hashCode;
  inHashFile.close();
  std::string query = "select hashCode from ismran_files where fileName='" + fileToCheck + "'";
  Select(query);
  while ((row = mysql_fetch_row(res)) != NULL) {
    if (hashCode == std::string(row[0])) {
      query = "update ismran_files set integrityCheck=1 where fileName='" + fileToCheck + "'";
      Update(query);
    }
  }
}

void Database::UpdateDbForFileNames_Offline(std::string sourceDir){
for (const auto & file : std::filesystem::directory_iterator(sourceDir)){
	//To get the filename with full path
	//std::cout << file.path() << std::endl;

	//To get just the filename
	//std::cout << std::filesystem::path(file.path()).filename() << std::endl;
	InsertFileNameAndPath(sourceDir,std::filesystem::path(file.path()).filename());
}
}

void Database::SetVerbose(bool verbose) { fVerbose = verbose; }

} // namespace ismran
