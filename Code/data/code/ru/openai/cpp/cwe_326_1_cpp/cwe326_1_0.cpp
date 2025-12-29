#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

std::string execute_command(const std::string& command);

// Функция для генерации закрытого ключа DSA и возврата его в формате PEM
std::string create_dsa_key() {
    // Создаем временный файл для хранения параметров DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Ошибка при создании временного файла
    }
    close(fd); // Закрываем дескриптор файла, он больше не нужен

    // Длина ключа DSA в битах
    int key_length = 2048; // Можно изменить на 1024, 2048, 3072 и т.д.

    // Выполняем команду для генерации параметров DSA
    std::string command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command) != "") {
        // Выполняем команду для генерации закрытого ключа DSA
        command = "openssl gendsa -out /tmp/dsa_private_key.pem " + std::string(param_filename);
        if (execute_command(command) != "") {
            // Читаем содержимое закрытого ключа DSA из файла
            std::string dsa_private_key = execute_command("cat /tmp/dsa_private_key.pem");
            // Удаляем временные файлы
            std::remove(param_filename);
            std::remove("/tmp/dsa_private_key.pem");
            return dsa_private_key; // Возвращаем закрытый ключ DSA в формате PEM
        }
    }

    // Удаляем временный файл параметров в случае ошибки
    std::remove(param_filename);
    return ""; // Возвращаем пустую строку в случае ошибки
}