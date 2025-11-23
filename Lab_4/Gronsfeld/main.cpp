/**
 * @file main.cpp
 * @author Семин Александр 24ПТв2
 * @version 1.0
 * @date 2025
 * @brief Главный модуль для тестирования шифра Гронсфельда
 * @details Содержит тестовые функции и пользовательский интерфейс
 */

#include "modAlphaCipher.h"
#include <iostream>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <cwctype>

using namespace std;

/**
 * @brief Преобразование string в wstring
 * @param narrow_str строка в узком формате
 * @return строка в широком формате
 */
wstring to_wide(const string& narrow_str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(narrow_str);
}

/**
 * @brief Преобразование wstring в string
 * @param wide_str строка в широком формате
 * @return строка в узком формате
 */
string to_narrow(const wstring& wide_str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wide_str);
}

/**
 * @brief Тестовая функция с обработкой исключений
 * @param text исходный текст
 * @param key ключ шифрования
 * @param destructCipherText флаг для тестирования обработки ошибок
 */
void check(const string& text, const string& key, bool destructCipherText = false)
{
    try {
        wstring wtext = to_wide(text);
        wstring wkey = to_wide(key);
        
        modAlphaCipher cipher(wkey);
        wstring cipherText = cipher.encrypt(wtext);
        
        if (destructCipherText) {
            // "Портим" зашифрованный текст для тестирования обработки ошибок
            cipherText[0] = towlower(cipherText[0]);
        }
        
        wstring decryptedText = cipher.decrypt(cipherText);
        
        cout << "Ключ: " << key << endl;
        cout << "Исходный текст: " << text << endl;
        cout << "Зашифрованный текст: " << to_narrow(cipherText) << endl;
        cout << "Расшифрованный текст: " << to_narrow(decryptedText) << endl;
        
        if (wtext == decryptedText)
            cout << "OK\n";
        else
            cout << "Ошибка\n";
            
    } catch (const cipher_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    cout << "------------------------" << endl;
}

/**
 * @brief Главная функция программы
 * @return код завершения программы
 */
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
        
    // Тестирование с обработкой исключений
    cout << "=== Тестирование обработки исключений ===" << endl;
    check("ПРИВЕТ", "ЭХО");                    // Корректные данные
    check("ПРИВЕТ", "эхо");                    // Строчные буквы в ключе
    check("ПРИВЕТ", "");                       // Пустой ключ
    check("ПРИВЕТ", "ЭХО123");                 // Цифры в ключе
    check("Привет мир!", "КЛЮЧ");              // Строчные и пробелы в тексте
    check("123", "КЛЮЧ");                      // Только цифры
    check("ПРИВЕТ", "ЭХО", true);              // "Испорченный" зашифрованный текст
    
    // Пользовательский интерфейс
    cout << "\n=== Пользовательский интерфейс ===" << endl;
    string key_input;
    string text_input;
    unsigned op;
    
    cout << "Шифр готов. Введите ключ: ";
    getline(cin, key_input);
    
    try {
        wstring key = to_wide(key_input);
        modAlphaCipher cipher(key);
        
        cout << "Ключ загружен\n";
        
        do {
            cout << "Шифр готов. Выберите операцию (0-выход, 1-шифрование, 2-расшифрование): ";
            cin >> op;
            
            if (op > 2) {
                cout << "Неверная операция\n";
            } else if (op > 0) {
                cout << "Введите текст: ";
                cin.ignore();
                getline(cin, text_input);
                
                try {
                    wstring text = to_wide(text_input);
                    
                    if (op == 1) {
                        wstring encrypted = cipher.encrypt(text);
                        cout << "Зашифрованный текст: " << to_narrow(encrypted) << endl;
                    } else {
                        wstring decrypted = cipher.decrypt(text);
                        cout << "Расшифрованный текст: " << to_narrow(decrypted) << endl;
                    }
                } catch (const cipher_error& e) {
                    cout << "Ошибка при обработке текста: " << e.what() << endl;
                }
            }
        } while (op != 0);
        
    } catch (const cipher_error& e) {
        cerr << "Ошибка при загрузке ключа: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}