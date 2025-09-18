#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

class RouteCipher
{
private:
    int columns; // Количество столбцов (ключ)
    
    // Проверяет, является ли символ допустимым (только английские буквы)
    bool isValidChar(char c) const;
    
    // Преобразует текст: оставляет только английские буквы и приводит к верхнему регистру
    std::string normalizeText(const std::string& text) const;
    
    // Вычисляет количество строк для таблицы
    int calculateRows(int textLength) const;
    
    // Создает таблицу для шифрования
    std::vector<std::vector<char>> createEncryptionTable(const std::string& text) const;
    
    // Создает таблицу для расшифрования
    std::vector<std::vector<char>> createDecryptionTable(const std::string& text) const;
    
    // Читает текст из таблицы по горизонтали
    std::string readHorizontal(const std::vector<std::vector<char>>& table) const;
    
    // Читает текст из таблицы вертикально справа налево
    std::string readVerticalReverse(const std::vector<std::vector<char>>& table) const;

public:
    // Запрещаем конструктор без параметров
    RouteCipher() = delete;
    
    // Конструктор с установкой ключа
    RouteCipher(int key);
    
    // Шифрует текст (только английские буквы)
    std::string encrypt(const std::string& plainText);
    
    // Расшифровывает текст
    std::string decrypt(const std::string& cipherText);
};