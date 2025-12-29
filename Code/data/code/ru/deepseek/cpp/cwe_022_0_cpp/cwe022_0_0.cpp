#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Создаем полный путь к файлу
    std::filesystem::path full_path = std::filesystem::path(dir_path) / filename;
    
    // Проверяем, существует ли файл и является ли он обычным файлом
    std::error_code ec;
    if (!std::filesystem::exists(full_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(full_path, ec) || ec) {
        return "";
    }
    
    // Открываем файл для чтения
    std::ifstream file(full_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return "";
    }
    
    // Получаем размер файла
    std::streamsize size = file.tellg();
    if (size == -1) {
        return "";
    }
    
    file.seekg(0, std::ios::beg);
    
    // Читаем содержимое файла
    std::string content;
    content.resize(size);
    
    if (!file.read(&content[0], size)) {
        return "";
    }
    
    return content;
}