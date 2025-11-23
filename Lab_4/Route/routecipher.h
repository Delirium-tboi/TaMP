/**
 * @file routecipher.h
 * @author Семин Александр 24ПТв2
 * @version 1.0
 * @date 2025
 * @copyright -
 * @brief Заголовочный файл для модуля шифрования табличной маршрутной перестановкой
 * @warning Реализация для русского языка
 */

#pragma once
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

/**
 * @brief Класс исключения для ошибок шифрования
 * @details Наследуется от std::exception
 */
class CipherException : public exception
{
private:
    string message; ///< сообщение об ошибке
public:
    /**
     * @brief Конструктор с параметром
     * @param msg сообщение об ошибке
     */
    explicit CipherException(const string& msg) : message(msg) {}
    
    /**
     * @brief Получение сообщения об ошибке
     * @return указатель на строку с сообщением
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @brief Шифр табличной маршрутной перестановки
 * @details Маршрут записи: по горизонтали слева направо, сверху вниз.
 * Маршрут считывания: сверху вниз, справа налево.
 * Ключ - количество столбцов таблицы.
 */
class Table
{
private:
    int cols; ///< количество столбцов (ключ)
    
public:
    /**
     * @brief Конструктор с установкой ключа
     * @param key количество столбцов таблицы
     * @throw CipherException если ключ <= 0
     */
    explicit Table(int key);
    
    /**
     * @brief Зашифровывание текста
     * @param plain открытый текст
     * @return зашифрованный текст
     * @throw CipherException если текст пустой или слишком короткий для ключа
     */
    wstring encrypt(const wstring& plain);
    
    /**
     * @brief Расшифровывание текста
     * @param cipher зашифрованный текст
     * @return расшифрованный текст
     * @throw CipherException если текст пустой или слишком короткий для ключа
     */
    wstring decrypt(const wstring& cipher);
};