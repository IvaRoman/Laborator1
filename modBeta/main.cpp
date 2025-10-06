#include <iostream>
#include "routeCipher.h"

int main()
{
    try {
        int key;
        std::string text;
        
        // Ввод ключа
        std::cout << "Введите ключ (число столбцов): ";
        std::cin >> key;
        
        // Создание шифратора
        RouteCipher cipher(key);

        int op;
        // Главный цикл программы
        do {
            std::cout << "Операция (0-выход, 1-шифровать, 2-расшифровать): ";
            std::cin >> op;
            
            if (op == 1 || op == 2) {
                // Ввод текста
                std::cout << "Введите текст: ";
                std::cin.ignore();  // Очистка буфера после ввода числа
                std::getline(std::cin, text);  // Чтение всей строки
                
                if (op == 1) {
                    // Шифрование и вывод результата
                    std::cout << "Зашифрованный текст: " << cipher.encrypt(text) << std::endl;
                } else {
                    // Дешифрование и вывод результата
                    std::cout << "Расшифрованный текст: " << cipher.decrypt(text) << std::endl;
                }
            }
        } while (op != 0);  // Выход при вводе 0
        
    } catch (const std::exception& e) {
        // Обработка всех исключений
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    return 0;
}