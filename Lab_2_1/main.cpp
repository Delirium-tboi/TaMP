#include "routecipher.h"
#include <iostream>
#include <string>
#include <limits>
#include <locale>

using namespace std;

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

string getTextFromUser(const string& prompt)
{
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}

void showMenu(int currentKey)
{
    cout << "\n=== MENU (Current key: " << currentKey << ") ===" << endl;
    cout << "1 - Encrypt text" << endl;
    cout << "2 - Decrypt text" << endl;
    cout << "3 - Change key" << endl;
    cout << "0 - Exit" << endl;
    cout << "Select operation: ";
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    
    cout << "=== TABLE ROUTE TRANSPOSITION CIPHER ===" << endl;
    cout << "Write route: horizontally left to right, top to bottom" << endl;
    cout << "Read route: top to bottom, right to left" << endl;
    cout << "Only English letters are processed (A-Z, a-z)" << endl;
    cout << "Key must be >= text length" << endl;
    
    int key;
    RouteCipher* cipher = nullptr;
    
    // Инициализация шифра с обработкой исключений
    while (true) {
        try {
            key = getKeyFromUser();
            cipher = new RouteCipher(key);
            break;
        } catch (const cipher_error& e) {
            cout << "Key error: " << e.what() << endl;
        }
    }
    
    int choice;
    do {
        showMenu(cipher->getKey());
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
                    cout << "Original text: " << text << endl;
                    string encrypted = cipher->encrypt(text);
                    cout << "Encrypted text: " << encrypted << endl;
                } catch (const cipher_error& e) {
                    cout << "Encryption error: " << e.what() << endl;
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
                    cout << "Encrypted text: " << text << endl;
                    string decrypted = cipher->decrypt(text);
                    cout << "Decrypted text: " << decrypted << endl;
                } catch (const cipher_error& e) {
                    cout << "Decryption error: " << e.what() << endl;
                }
                break;
            }
                
            case 3: {
                while (true) {
                    try {
                        key = getKeyFromUser();
                        delete cipher;
                        cipher = new RouteCipher(key);
                        cout << "Key changed to: " << key << " columns" << endl;
                        break;
                    } catch (const cipher_error& e) {
                        cout << "Key error: " << e.what() << endl;
                    }
                }
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
    
    delete cipher;
    return 0;
}