#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <memory>
#include <stdexcept>
#include <fstream>

// Объявление предоставленной функции
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Длина ключа по умолчанию (можно изменить при необходимости)
    const int key_length = 2048;
    
    // Создание временного файла для параметров DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // Создание временного файла для закрытого ключа
    char key_filename[] = "/tmp/keyXXXXXX";
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        remove(param_filename);
        return "";
    }
    close(key_fd);
    
    std::string result;
    
    try {
        // 1. Генерация параметров DSA
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        std::string param_output = execute_command(param_command);
        
        // Проверка успешности выполнения команды (можно проверить наличие ошибок в выводе)
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA parameters");
        }
        
        // 2. Генерация закрытого ключа DSA
        std::string key_command = "openssl gendsa " + std::string(param_filename) + 
                                 " -out " + std::string(key_filename);
        std::string key_output = execute_command(key_command);
        
        // Проверка успешности выполнения команды
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA key");
        }
        
        // Чтение сгенерированного закрытого ключа из файла
        std::ifstream key_file(key_filename, std::ios::binary);
        if (!key_file.is_open()) {
            throw std::runtime_error("Failed to open generated key file");
        }
        
        std::string key_content((std::istreambuf_iterator<char>(key_file)),
                               std::istreambuf_iterator<char>());
        
        result = key_content;
        
        // Закрытие файлов
        key_file.close();
        
    } catch (const std::exception& e) {
        // В случае ошибки возвращаем пустую строку
        result = "";
    }
    
    // Удаление временных файлов
    remove(param_filename);
    remove(key_filename);
    
    return result;
}