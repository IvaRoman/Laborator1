#pragma once  // Защита от повторного включения
#include <string>
#include <vector>

class RouteCipher
{
private:
    int columns;  // Количество столбцов (ключ)
    
    // Валидация ключа
    int getValidKey(int key);
    
    // Валидация текста
    std::string getValidText(const std::string& text);
    
public:
    RouteCipher() = delete;  // Запрет конструктора по умолчанию
    
    // Конструктор с ключом
    RouteCipher(int key);
    
    // Методы шифрования/дешифрования
    std::string encrypt(const std::string& text);   // Шифрование
    std::string decrypt(const std::string& text);   // Дешифрование
};