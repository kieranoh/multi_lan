#include <iostream>
#include <string>
#include <cstdio>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Comandament per executar
    std::string command = "ls -l " + dir_path + " 2>&1"; // Redirigir stderr a stdout
    std::array<char, 128> buffer;
    std::string result;

    // Obertura d'un flux per executar el comandament
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Retorna cadena buida si no es pot obrir el flux
    }

    // Llegir la sortida del comandament
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Retorna la sortida o cadena buida en cas d'error
}