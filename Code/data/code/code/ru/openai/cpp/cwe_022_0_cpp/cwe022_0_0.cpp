#include <iostream>
#include <fstream>
#include <string>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Создаем полный путь к файлу
    std::string file_path = dir_path + "/" + filename;
    std::ifstream file(file_path);
    
    // Проверяем, был ли файл успешно открыт
    if (!file.is_open()) {
        return ""; // Возвращаем пустую строку в случае ошибки
    }
    
    std::string content;
    std::string line;
    
    // Читаем содержимое файла построчно
    while (std::getline(file, line)) {
        content += line + "\n"; // Добавляем строку к содержимому
    }
    
    file.close(); // Закрываем файл
    return content; // Возвращаем содержимое файла
}