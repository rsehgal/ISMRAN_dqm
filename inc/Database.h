/*
**	Filename : Database.h
**	2021-10-30
**	username : rsehgal
*/
#ifndef Database_h
#define Database_h

#include <iostream>
#include <mysql.h>
#include <string>

namespace ismran {

class Database {
  // MYSQL related data members
  MYSQL *conn, mysql;
  MYSQL_RES *res;
  MYSQL_ROW row;

  int fQueryState;

  // MySql database details
  std::string fDbName;
  std::string fUsername;
  std::string fPasswd;
  std::string fQuery;
  std::string fServerIp;

  bool fVerbose;

public:
  Database();
  virtual ~Database();
  Database(std::string serverIp, std::string dbName, std::string uName, std::string passWd);
  Database(std::string dbName, std::string uName, std::string passWd);
  int Connect();

  template <bool select = false> int Query(std::string query);

  int Insert(std::string query);
  int InsertFileNameAndPath(std::string filePath, std::string fileName);

  int Delete(std::string tablename);
  int Select(std::string query);
  int Count(std::string query);
  int Update(std::string query);
  int GetNumOfColumns(std::string tablename);
  int GetNumOfRows(std::string tablename);
  void PrintQueryOutput();

  // Function to set the fVERBOSE flag
  void SetVerbose(bool verbose);
};

template <bool select> int Database::Query(std::string query) {

  //	fQueryState = mysql_query(conn,fQuery.c_str());
  fQueryState = mysql_query(conn, query.c_str());
  if (fQueryState != 0) {
    std::cout << mysql_error(conn) << std::endl << std::endl;
    return 1;
  }
  if (select) {
    res = mysql_store_result(conn);

    if (fVerbose)
      PrintQueryOutput();
  }
}

} // namespace ismran
#endif
