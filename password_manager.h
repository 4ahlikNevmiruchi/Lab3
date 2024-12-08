#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>

class PasswordManager {
public:
    PasswordManager(const std::string& dbPath, const std::string& encryptionKey);
    void addPassword(const std::string& account, const std::string& password);
    std::string getPassword(const std::string& account);

private:
    std::string key;
};

#endif // PASSWORD_MANAGER_H
