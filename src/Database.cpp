/*
**	Filename : Database.cpp
**	2021-10-30
**	username : rsehgal
*/

#include "Database.h"
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

int Database::Delete(std::string tablename) {
  std::string query = "DELETE FROM " + tablename;
  return Query(query);
}

int Database::Update(std::string query) { return Query(query); }

int Database::Insert(std::string query) { return Query(query); }

int Database::InsertFileNameAndPath(std::string filePath, std::string fileName){
  std::string query = "INSERT into ismran_files (filePath,fileName) values('" + filePath+"','"+fileName+"')";
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

void Database::SetVerbose(bool verbose) { fVerbose = verbose; }

} // namespace ismran
