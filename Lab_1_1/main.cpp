#include "routecipher.h"
#include <iostream>
#include <string>
#include <limits>
#include <locale>

using namespace std;

// Функция для очистки буфера ввода
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Функция для получения ключа от пользователя
int getKeyFromUser()
{
    int key;
    while (true) {
        cout << "Enter encryption key (number of columns > 0): ";
        cin >> key;
        
        if (cin.fail() || key <= 0) {
            cout << "Error: Key must be a positive integer!" << endl;
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return key;
        }
    }
}

// Функция для получения текста от пользователя
string getTextFromUser(const string& prompt)
{
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}

// Функция для отображения меню
void showMenu()
{
    cout << "\n=== MENU ===" << endl;
    cout << "1 - Encrypt text" << endl;
    cout << "2 - Decrypt text" << endl;
    cout << "3 - Change key" << endl;
    cout << "0 - Exit" << endl;
    cout << "Select operation: ";
}

// Основная функция программы
int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    
    cout << "=== TABLE ROUTE TRANSPOSITION CIPHER ===" << endl;
    cout << "Write route: horizontally left to right, top to bottom" << endl;
    cout << "Read route: top to bottom, right to left" << endl;
    cout << "Only English letters are processed (A-Z, a-z)" << endl;
    
    // Установка ключа
    int key = getKeyFromUser();
    RouteCipher cipher(key);
    cout << "Key set: " << key << " columns" << endl;
    
    int choice;
    do {
        showMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                string text = getTextFromUser("Enter text to encrypt: ");
                if (text.empty()) {
                    cout << "Text cannot be empty!" << endl;
                    break;
                }
                
                try {
                    string encrypted = cipher.encrypt(text);
                    cout << "Original text: " << text << endl;
                    cout << "Encrypted text: " << encrypted << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                    cout << "Please use only English letters (A-Z, a-z)" << endl;
                }
                break;
            }
                
            case 2: {
                string text = getTextFromUser("Enter text to decrypt: ");
                if (text.empty()) {
                    cout << "Text cannot be empty!" << endl;
                    break;
                }
                
                try {
                    string decrypted = cipher.decrypt(text);
                    cout << "Encrypted text: " << text << endl;
                    cout << "Decrypted text: " << decrypted << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                    cout << "Please use only English letters (A-Z, a-z)" << endl;
                }
                break;
            }
                
            case 3: {
                key = getKeyFromUser();
                cipher = RouteCipher(key);
                cout << "Key changed: " << key << " columns" << endl;
                break;
            }
                
            case 0:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid operation! Please try again." << endl;
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}