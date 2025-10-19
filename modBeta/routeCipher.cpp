#include "routeCipher.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>

// Конструктор: инициализация ключа
RouteCipher::RouteCipher(int key)
{
    columns = getValidKey(key);
}

// Метод шифрования
std::string RouteCipher::encrypt(const std::string& text)
{
    std::string validText = getValidText(text);
    int original_length = validText.size();
    int rows = (original_length + columns - 1) / columns;
    int total_cells = rows * columns;

    // Создаем таблицу и заполняем ее по строкам
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    int index = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (index < original_length) {
                table[i][j] = validText[index++];
            }
            // Оставляем пустые ячейки пустыми
        }
    }

    // Читаем по столбцам справа налево, сверху вниз
    std::string result;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (table[i][j] != ' ') { // Читаем только заполненные ячейки
                result += table[i][j];
            }
        }
    }
    
    return result;
}

// Метод дешифрования
std::string RouteCipher::decrypt(const std::string& text)
{
    std::string validText = getValidText(text);
    int encrypted_length = validText.size();
    int rows = (encrypted_length + columns - 1) / columns;
    
    // Восстанавливаем оригинальную длину текста
    int original_length = encrypted_length; // Начинаем с предположения
    
    // Создаем таблицу для дешифрования
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));
    
    // Сначала определяем, какие ячейки были заполнены в оригинальной таблице
    std::vector<std::vector<bool>> filled(rows, std::vector<bool>(columns, false));
    int original_index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (original_index < original_length) {
                filled[i][j] = true;
                original_index++;
            }
        }
    }
    
    // Заполняем таблицу по столбцам справа налево, сверху вниз
    // ТОЛЬКО в те ячейки, которые были заполнены в оригинале
    int encrypted_index = 0;
    for (int j = columns - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (filled[i][j] && encrypted_index < encrypted_length) {
                table[i][j] = validText[encrypted_index++];
            }
        }
    }

    // Читаем таблицу по строкам слева направо, сверху вниз
    std::string result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (filled[i][j]) {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

// Валидация ключа
int RouteCipher::getValidKey(int key)
{
    if (key <= 0) {
        throw std::invalid_argument("Ключ должен быть положительным");
    }
    return key;
}

// Валидация текста
std::string RouteCipher::getValidText(const std::string& text)
{
    if (text.empty()) {
        throw std::invalid_argument("Текст пуст");
    }
    
    std::string result;
    
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    
    if (result.empty()) {
        throw std::invalid_argument("Текст не содержит букв");
    }
    
    return result;
}
