#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // Verificar si el directori existeix i és accessible abans d'executar la comanda
    try {
        if (!std::filesystem::exists(dir_path)) {
            return "";
        }
        if (!std::filesystem::is_directory(dir_path)) {
            return "";
        }
    } catch (const std::filesystem::filesystem_error&) {
        return "";
    }

    // Construir la comanda amb el camí proporcionat
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Buffer per capturar la sortida
    std::array<char, 128> buffer;
    std::string result;
    
    // Obrir un pipe per llegir la sortida de la comanda
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    
    // Llegir la sortida del pipe
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Si la comanda ha fallat o no hi ha sortida, retornar cadena buida
    if (result.empty()) {
        return "";
    }
    
    return result;
}