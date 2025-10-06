#include "modAlphaCipher.h"
#include <stdexcept>
#include <iostream>

// Конструктор: инициализация алфавита и ключа
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Заполняем ассоциативный массив: символ -> его позиция в алфавите
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    // Преобразуем ключ в числовой вектор
    key = convert(getValidKey(skey));
}

// Метод шифрования
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    // Преобразуем текст в числовой вектор
    std::vector<int> work = convert(getValidText(open_text));
    
    // Применяем шифр Гронсфельда
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    // Преобразуем результат обратно в строку
    return convert(work);
}

// Метод дешифрования
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    // Преобразуем шифротекст в числовой вектор
    std::vector<int> work = convert(getValidText(cipher_text));
    
    // Обратная операция
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

// Преобразование строки в вектор чисел
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    // Для каждого символа в строке
    for (auto c : s) {
        // Добавляем его числовое представление в вектор
        result.push_back(alphaNum[c]);
    }
    return result;
}

// Преобразование вектора чисел в строку
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    // Для каждого числа в векторе
    for (auto i : v) {
        // Добавляем соответствующий символ из алфавита
        result.push_back(numAlpha[i]);
    }
    return result;
}

// Валидация ключа
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    // Проверка на пустой ключ
    if (s.empty()) {
        throw std::invalid_argument("Пустой ключ");
    }
    
    std::wstring tmp(s);  // Создаем копию для обработки
    
    // Обрабатываем каждый символ ключа
    for (auto& c : tmp) {
        // ПРОВЕРКА: символ должен присутствовать в нашем алфавите
        if (alphaNum.find(c) == alphaNum.end()) {
            // Если символа нет в алфавите, пробуем преобразовать в верхний регистр
            wchar_t upper_c = towupper(c);
            if (alphaNum.find(upper_c) != alphaNum.end()) {
                c = upper_c;  // Используем верхний регистр
            } else {
                throw std::invalid_argument("Ключ содержит недопустимые символы");
            }
        }
    }
    return tmp;
}

// Валидация текста
std::wstring modAlphaCipher::getValidText(const std::wstring& s)
{
    std::wstring tmp;
    
    // Обрабатываем каждый символ текста
    for (auto c : s) {
        // ПРОВЕРКА: символ должен присутствовать в нашем алфавите
        if (alphaNum.find(c) != alphaNum.end()) {
            tmp.push_back(c);  // Символ уже в правильном формате
        } else {
            // Пробуем преобразовать в верхний регистр
            wchar_t upper_c = towupper(c);
            if (alphaNum.find(upper_c) != alphaNum.end()) {
                tmp.push_back(upper_c);  // Используем верхний регистр
            }
            // Если символ не буква алфавита - просто пропускаем его
        }
    }
    
    // Проверка, что после обработки остались буквы
    if (tmp.empty()) {
        throw std::invalid_argument("Текст пуст после обработки");
    }
    
    return tmp;
}