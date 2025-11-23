/**
 * @file modAlphaCipher.h
 * @author Семин Александр 24Птв2
 * @version 1.0
 * @date 2025
 * @copyright -
 * @brief Заголовочный файл для модуля шифрования методом Гронсфельда
 * @warning Реализация для русского языка
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <stdexcept>
#include <iostream>

/**
 * @brief Класс исключения для ошибок шифрования
 * @details Наследуется от std::invalid_argument
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с параметром string
     * @param what_arg сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с параметром char*
     * @param what_arg сообщение об ошибке
     */
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

/**
 * @brief Шифрование методом Гронсфельда
 * @details Ключ устанавливается в конструкторе.
 * Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для русского языка
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< русский алфавит по порядку
    std::map<wchar_t, int> alphaNum; ///< ассоциативный массив "номер по символу"
    std::vector<int> key;            ///< ключ в числовом виде
    
    /**
     * @brief Преобразование строки в числовой вектор
     * @param s строка для преобразования
     * @return вектор чисел, соответствующих символам строки
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразование числового вектора в строку
     * @param v вектор чисел для преобразования
     * @return строка, соответствующая числовому вектору
     */
    std::wstring convert(const std::vector<int>& v);
    
    /**
     * @brief Проверка и нормализация ключа
     * @param s исходный ключ
     * @return валидированный ключ в верхнем регистре
     * @throw cipher_error если ключ пустой или содержит недопустимые символы
     */
    std::wstring getValidKey(const std::wstring& s);
    
    /**
     * @brief Проверка открытого текста
     * @param s исходный открытый текст
     * @return валидированный текст в верхнем регистре без не-букв
     * @throw cipher_error если текст пустой после удаления не-букв
     */
    std::wstring getValidOpenText(const std::wstring& s);
    
    /**
     * @brief Проверка зашифрованного текста
     * @param s зашифрованный текст
     * @return валидированный зашифрованный текст
     * @throw cipher_error если текст пустой или содержит недопустимые символы
     */
    std::wstring getValidCipherText(const std::wstring& s);
    
public:
    modAlphaCipher() = delete; ///< запрет конструктора без параметров
    
    /**
     * @brief Конструктор для установки ключа
     * @param skey строковый ключ
     * @throw cipher_error если ключ невалидный
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Зашифровывание
     * @param open_text Открытый текст. Не должен быть пустой строкой.
     * Строчные символы автоматически преобразуются к прописным.
     * Все не-буквы удаляются
     * @return Зашифрованная строка
     * @throw cipher_error если текст пустой
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Расшифровывание
     * @param cipher_text Зашифрованный текст. Должен содержать только прописные русские буквы
     * @return Расшифрованная строка
     * @throw cipher_error если текст пустой или содержит недопустимые символы
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};