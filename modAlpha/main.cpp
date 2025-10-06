#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include "modAlphaCipher.h"
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    try {
        std::wcout << L"Создаем шифратор с ключом: КЛЮЧ" << std::endl;
        modAlphaCipher cipher(L"КЛЮЧ");
        
        std::wstring text = L"ПРИВЕТМИР";
        std::wcout << L"Исходный текст: " << text << std::endl;
        
        std::wstring encrypted = cipher.encrypt(text);
        std::wcout << L"Зашифрованный: " << encrypted << std::endl;
        
        std::wstring decrypted = cipher.decrypt(encrypted);
        std::wcout << L"Расшифрованный: " << decrypted << std::endl;
        
        // Проверка корректности
        if (text == decrypted) {
            std::wcout << L"✓ Тест пройден успешно!" << std::endl;
        } else {
            std::wcout << L"✗ Ошибка: текст не совпадает после расшифровки!" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}