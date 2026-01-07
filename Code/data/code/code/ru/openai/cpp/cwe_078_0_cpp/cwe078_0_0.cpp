#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path + " 2>&1"; // Перенаправление stderr в stdout
    std::array<char, 128> buffer;
    std::string result;

    // Используем popen для выполнения команды и получения результата
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Если не удалось открыть поток, возвращаем пустую строку
    }

    // Читаем результат выполнения команды
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Возвращаем результат выполнения команды
}