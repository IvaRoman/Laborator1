#pragma once  // Защита от повторного включения файла
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>  // Для работы с широкими символами и кодировками

class modAlphaCipher
{
private:
    // Русский алфавит в верхнем регистре
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    // Ассоциативный массив: символ -> его номер в алфавите
    std::map<wchar_t, int> alphaNum;
    
    // Ключ в числовом представлении
    std::vector<int> key;
    
    // Закрытые методы преобразования
    std::vector<int> convert(const std::wstring& s);  // Строка -> вектор чисел
    std::wstring convert(const std::vector<int>& v);  // Вектор чисел -> строка
    
    // Методы валидации
    std::wstring getValidKey(const std::wstring& s);   // Проверка ключа
    std::wstring getValidText(const std::wstring& s);  // Проверка текста

public:
    modAlphaCipher() = delete;  // Запрет конструктора без параметров
    
    // Конструктор с ключом
    modAlphaCipher(const std::wstring& skey);
    
    // Методы шифрования/дешифрования
    std::wstring encrypt(const std::wstring& open_text);   // Шифрование
    std::wstring decrypt(const std::wstring& cipher_text); // Дешифрование
};