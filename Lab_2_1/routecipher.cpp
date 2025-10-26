#include "routecipher.h"
#include <algorithm>
#include <vector>
using namespace std;

Table::Table(int key)
{
    if (key <= 0) throw CipherException("Ключ должен быть > 0");
    cols = key;
}

wstring Table::encrypt(const wstring& plain)
{
    if (plain.empty()) throw CipherException("Текст для шифрования не может быть пустым");
    
    // Проверка на минимальную длину текста
    if (plain.length() < static_cast<size_t>(cols)) {
        throw CipherException("Текст слишком короткий для выбранного ключа. Длина текста должна быть не меньше числа столбцов.");
    }

    int n = static_cast<int>(plain.length());
    int rows = (n + cols - 1) / cols;

    vector<vector<wchar_t>> grid(rows, vector<wchar_t>(cols, L' '));
    int pos = 0;

    // Заполнение таблицы по строкам
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (pos < n) {
                grid[r][c] = plain[pos++];
            }
        }
    }

    wstring out;
    out.reserve(n);
    
    // Чтение по столбцам справа налево
    for (int c = cols - 1; c >= 0; --c) {
        for (int r = 0; r < rows; ++r) {
            if (grid[r][c] != L' ') {
                out += grid[r][c];
            }
        }
    }
    return out;
}

wstring Table::decrypt(const wstring& cipher)
{
    if (cipher.empty()) throw CipherException("Текст для расшифровки не может быть пустым");

    int n = static_cast<int>(cipher.length());
    
    // Проверка совместимости длины текста с ключом
    if (n < static_cast<size_t>(cols)) {
        throw CipherException("Текст слишком короткий для выбранного ключа. Невозможно выполнить расшифровку.");
    }

    int rows = (n + cols - 1) / cols;
    
    // Вычисление количества полных столбцов
    int fullCols = n % cols;
    if (fullCols == 0) fullCols = cols;

    vector<vector<wchar_t>> grid(rows, vector<wchar_t>(cols, L' '));
    int pos = 0;

    // Заполнение таблицы по столбцам справа налево
    for (int c = cols - 1; c >= 0; --c) {
        int h = rows;
        // Для неполных столбцов уменьшаем высоту
        if (c >= fullCols) {
            h = rows - 1;
        }
        for (int r = 0; r < h; ++r) {
            if (pos < n) {
                grid[r][c] = cipher[pos++];
            }
        }
    }

    wstring out;
    out.reserve(n);
    
    // Чтение по строкам слева направо
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != L' ') {
                out += grid[r][c];
            }
        }
    }
    return out;
}