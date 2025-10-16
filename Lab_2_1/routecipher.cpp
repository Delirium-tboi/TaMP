#include "routecipher.h"
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

const char FILL_CHAR = '=';

RouteCipher::RouteCipher(int key) : columns(key) 
{
    if (key <= 0) {
        throw cipher_error("Key must be a positive integer!");
    }
}

bool RouteCipher::isValidChar(char c) const
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

string RouteCipher::normalizeText(const string& text) const
{
    string result;
    for (char c : text) {
        if (isValidChar(c)) {
            result += toupper(c);
        }
    }
    return result;
}

string RouteCipher::prepareCipherText(const string& text) const
{
    string result;
    for (char c : text) {
        // Сохраняем все буквы и символ заполнителя
        if (isValidChar(c) || c == FILL_CHAR) {
            result += (c == FILL_CHAR) ? FILL_CHAR : toupper(c);
        }
    }
    return result;
}

int RouteCipher::calculateRows(int textLength) const
{
    return (textLength + columns - 1) / columns;
}

void RouteCipher::validateKeyForText(int textLength) const
{
    if (columns > textLength) {
        throw cipher_error("The key (" + to_string(columns) + 
                          ") must not to be longer than the text(" + 
                          to_string(textLength) + ")!");
    }
}

vector<vector<char>> RouteCipher::createEncryptionTable(const string& text) const
{
    int rows = calculateRows(text.length());
    vector<vector<char>> table(rows, vector<char>(columns, FILL_CHAR));
    int index = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (index < text.length()) {
                table[i][j] = text[index++];
            }
        }
    }
    
    return table;
}

vector<vector<char>> RouteCipher::createDecryptionTable(const string& text) const
{
    int rows = calculateRows(text.length());
    int totalCells = rows * columns;
    
    // Дополняем текст до полной таблицы символами FILL_CHAR
    string paddedText = text;
    if (paddedText.length() < totalCells) {
        paddedText += string(totalCells - paddedText.length(), FILL_CHAR);
    }
    
    vector<vector<char>> table(rows, vector<char>(columns, ' '));
    int index = 0;
    
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (index < paddedText.length()) {
                table[i][j] = paddedText[index++];
            }
        }
    }
    
    return table;
}

string RouteCipher::readHorizontal(const vector<vector<char>>& table) const
{
    string result;
    int rows = table.size();
    
    // Читаем построчно все символы (и буквы и заполнители)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result += table[i][j];
        }
    }
    
    return result;
}

string RouteCipher::readVerticalReverse(const vector<vector<char>>& table) const
{
    string result;
    int rows = table.size();
    
    // Читаем по столбцам справа налево все символы
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            result += table[i][j];
        }
    }
    
    return result;
}
string RouteCipher::encrypt(const string& plainText)
{
    if (plainText.empty()) {
        throw cipher_error("Text cannot be empty!");
    }
    
    string normalized = normalizeText(plainText);
    if (normalized.empty()) {
        throw cipher_error("The text should contain only English letters!");
    }
    
    validateKeyForText(normalized.length());
    
    auto table = createEncryptionTable(normalized);
    // Зашифрованный текст содержит заполнители = (они нужны для расшифровки)
    return readVerticalReverse(table);
}

string RouteCipher::decrypt(const string& cipherText)
{
    if (cipherText.empty()) {
        throw cipher_error("Text cannot be empty!");
    }
    
    // Для дешифровки используем prepareCipherText, которая сохраняет '='
    string prepared = prepareCipherText(cipherText);
    if (prepared.empty()) {
        throw cipher_error("The text should contain only English letters!");
    }
    
    validateKeyForText(prepared.length());
    
    // Создаем таблицу с символами '='
    auto table = createDecryptionTable(prepared);
    
    // Читаем таблицу (включая '=')
    string decryptedWithFillers = readHorizontal(table);
    
    // Удаляем заполнители из конечного расшифрованного текста
    string finalResult;
    for (char c : decryptedWithFillers) {
        if (c != FILL_CHAR) {
            finalResult += c;
        }
    }
    
    return finalResult;
}