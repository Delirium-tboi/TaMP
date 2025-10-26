#pragma once
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// Класс для обработки исключений
class CipherException : public exception
{
private:
    string message;
public:
    explicit CipherException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Table
{
private:
    int cols;
public:
    explicit Table(int key);
    wstring encrypt(const wstring& plain);
    wstring decrypt(const wstring& cipher);
};