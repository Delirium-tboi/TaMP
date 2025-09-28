#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

// Класс исключения для ошибок шифрования
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

class RouteCipher
{
private:
    int columns;
    
    bool isValidChar(char c) const;
    std::string normalizeText(const std::string& text) const;
    int calculateRows(int textLength) const;
    void validateKeyForText(int textLength) const;
    std::vector<std::vector<char>> createEncryptionTable(const std::string& text) const;
    std::vector<std::vector<char>> createDecryptionTable(const std::string& text) const;
    std::string readHorizontal(const std::vector<std::vector<char>>& table) const;
    std::string readVerticalReverse(const std::vector<std::vector<char>>& table) const;

public:
    RouteCipher() = delete;
    RouteCipher(int key);
    std::string encrypt(const std::string& plainText);
    std::string decrypt(const std::string& cipherText);
    int getKey() const { return columns; }
};