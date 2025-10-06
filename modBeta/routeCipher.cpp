#include "routeCipher.h"
#include <stdexcept>
#include <algorithm>

// Конструктор: инициализация ключа
RouteCipher::RouteCipher(int key)
{
    columns = getValidKey(key);  // Валидируем и сохраняем ключ
}

// Метод шифрования
std::string RouteCipher::encrypt(const std::string& text)
{
    std::string validText = getValidText(text);
    size_t rows = (validText.size() + columns - 1) / columns;
    size_t total_cells = rows * columns;

    validText.resize(total_cells, 'X');
    
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns));
    
    size_t index = 0;
    for (size_t i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            table[i][j] = validText[index++];
        }
    }

    std::string result;
    for (int j = columns - 1; j >= 0; j--) {
        for (size_t i = 0; i < rows; i++) {
            result += table[i][j];
        }
    }
    return result;
}

// Метод дешифрования
std::string RouteCipher::decrypt(const std::string& text)
{
    // Валидируем текст
    std::string validText = getValidText(text);
    
    // Вычисляем количество строк
    int rows = (validText.size() + columns - 1) / columns;
    
    // Создаем таблицу
    std::vector<std::vector<char>> table(rows, std::vector<char>(columns, ' '));

    // Заполняем таблицу по столбцам сверху вниз, справа налево
    int index = 0;
    for (int j = columns - 1; j >= 0; j--) {        // Столбцы справа налево
        for (int i = 0; i < rows; i++) {            // Строки сверху вниз
            if (index < validText.size()) {
                table[i][j] = validText[index++];
            }
        }
    }

    // Читаем таблицу по строкам слева направо, сверху вниз
    std::string result;
    for (int i = 0; i < rows; i++) {                // Строки сверху вниз
        for (int j = 0; j < columns; j++) {         // Столбцы слева направо
            if (table[i][j] != ' ') {               // Пропускаем пустые ячейки
                result += table[i][j];
            }
        }
    }
    
    return result;
}

// Валидация ключа
int RouteCipher::getValidKey(int key)
{
    // Ключ должен быть положительным числом
    if (key <= 0) {
        throw std::invalid_argument("Ключ должен быть положительным");
    }
    return key;
}

// Валидация текста
std::string RouteCipher::getValidText(const std::string& text)
{
    // Проверка на пустой текст
    if (text.empty()) {
        throw std::invalid_argument("Текст пуст");
    }
    
    std::string result;
    
    // Обрабатываем каждый символ текста
    for (char c : text) {
        // Оставляем только буквы, преобразуем в верхний регистр
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    
    // Проверка, что остались буквы после обработки
    if (result.empty()) {
        throw std::invalid_argument("Текст не содержит букв");
    }
    
    return result;
}