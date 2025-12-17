#include <iostream>
#include <sqlite3.h>

int main() {
  sqlite3* db = nullptr;
  // here sqlite3 is a struct which is like the connection struct for sqlite3
  int rc = sqlite3_open("test.db", &db);
  // here rc stands for return code

  if (rc != SQLITE_OK) {
    std::cerr << "Cannot open DB: " << sqlite3_errmsg(db) << "\n";
  }

  std::cout << "Database opened succesfully" << std::endl;

  const char* create_sql = 
    "CREATE TABLE IF NOT EXISTS problems("
    "id INTEGER PRIMARY KEY,"
    "title TEXT"
    ");";

  rc = sqlite3_exec(db, create_sql, nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cerr << "CREATE TABLE FAILED\n";
    sqlite3_close(db);
    return 1;
  }

  const char* insert_sql = "INSERT INTO problems (title) VALUES ('first problem');";
  rc = sqlite3_exec(db, insert_sql, nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cerr << "INSERT FAILED\n";
    sqlite3_close(db);
    return 1; 
  }

  const char* select_sql = "SELECT * FROM problems;";
  auto callback = [] (void*, int argc, char** argv, char**) -> int {
    for (int i = 0; i < argc; i++) {
      std::cout << argv[i] << " ";
    }
    std::cout << "\n";
    return 0;
  };

  rc = sqlite3_exec(db, select_sql, callback, nullptr, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SELECT QUERY FAILED\n";
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}
