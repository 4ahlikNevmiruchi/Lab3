#include "database.h"
#include <iostream>

Database::Database(const std::string &dbPath) : db(nullptr) {
    sqlite3_open(dbPath.c_str(), &db);
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::initializeDatabase() {
    const char *createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS passwords (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account TEXT UNIQUE,
            encrypted_password TEXT
        )
    )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to create table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::storePassword(const std::string &account, const std::string &encryptedPassword) {
    const char *insertSQL = "INSERT INTO passwords (account, encrypted_password) VALUES (?, ?)";
    sqlite3_stmt *stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, encryptedPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to insert password: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

std::string Database::retrievePassword(const std::string &account) {
    const char *selectSQL = "SELECT encrypted_password FROM passwords WHERE account = ?";
    sqlite3_stmt *stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    std::string password;
    if (rc == SQLITE_ROW) {
        password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return password;
}
