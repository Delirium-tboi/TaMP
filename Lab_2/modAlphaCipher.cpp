#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <cwctype>
#include <algorithm>

using namespace std;

modAlphaCipher::modAlphaCipher(const wstring& skey)
{
    // Инициализируем алфавит и маппинг
    for(unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size(); // Исправлено: alphaNum.size() на numAlpha.size()
    }
    return convert(work);
}

wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size(); // Исправлено: alphaNum.size() на numAlpha.size()
    }
    return convert(work);
}

vector<int> modAlphaCipher::convert(const wstring& s)
{
    vector<int> result;
    for(auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

wstring modAlphaCipher::convert(const vector<int>& v)
{
    wstring result;
    for(auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

// Валидация и нормализация ключа
wstring modAlphaCipher::getValidKey(const wstring& s)
{
    if (s.empty())
        throw cipher_error("Пустой ключ");
    
    wstring tmp(s);
    for (auto & c : tmp) {
        if (!iswalpha(c))
            throw cipher_error("Ключ содержит недопустимые символы");
        if (iswlower(c))
            c = towupper(c);
        // Проверка на русские буквы
        bool is_russian = false;
        for (wchar_t rus_char : numAlpha) {
            if (c == rus_char) {
                is_russian = true;
                break;
            }
        }
        if (!is_russian)
            throw cipher_error("Ключ содержит символы не из русского алфавита");
    }
    return tmp;
}

// Валидация и нормализация открытого текста
wstring modAlphaCipher::getValidOpenText(const wstring& s)
{
    wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Пустой открытый текст после удаления не-букв");
    
    // Проверка на русские буквы
    for (auto c : tmp) {
        bool is_russian = false;
        for (wchar_t rus_char : numAlpha) {
            if (c == rus_char) {
                is_russian = true;
                break;
            }
        }
        if (!is_russian)
            throw cipher_error("Текст содержит символы не из русского алфавита");
    }
    return tmp;
}

// Валидация зашифрованного текста
wstring modAlphaCipher::getValidCipherText(const wstring& s)
{
    if (s.empty())
        throw cipher_error("Пустой зашифрованный текст");
    
    for (auto c : s) {
        if (!iswupper(c))
            throw cipher_error("Зашифрованный текст содержит строчные буквы");
        // Проверка на русские буквы
        bool is_russian = false;
        for (wchar_t rus_char : numAlpha) {
            if (c == rus_char) {
                is_russian = true;
                break;
            }
        }
        if (!is_russian)
            throw cipher_error("Зашифрованный текст содержит недопустимые символы");
    }
    return s;
}