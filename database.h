#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database {
public:
    explicit Database(const std::string &dbPath);
    ~Database();

    bool initializeDatabase();
    bool storePassword(const std::string &account, const std::string &encryptedPassword);
    std::string retrievePassword(const std::string &account);

private:
    sqlite3 *db;
};

#endif // DATABASE_H
