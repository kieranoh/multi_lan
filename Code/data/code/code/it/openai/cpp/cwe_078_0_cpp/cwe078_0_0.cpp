#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Comando da eseguire
    std::string command = "ls -l " + dir_path;

    // Creazione del buffer per memorizzare l'output
    std::array<char, 128> buffer;
    std::string result;

    // Apertura del processo per eseguire il comando
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // Restituisce stringa vuota in caso di errore
        return "";
    }

    // Lettura dell'output dal pipe
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}