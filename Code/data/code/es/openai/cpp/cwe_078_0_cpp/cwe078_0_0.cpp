#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Comando a ejecutar
    std::string command = "ls -l " + dir_path;

    // Usamos un array de caracteres para establecer la tubería
    std::array<char, 128> buffer;
    std::string result;

    // Abrimos un proceso para ejecutar el comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error
    }

    // Leemos la salida del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Retornamos el resultado o cadena vacía en caso de error
}