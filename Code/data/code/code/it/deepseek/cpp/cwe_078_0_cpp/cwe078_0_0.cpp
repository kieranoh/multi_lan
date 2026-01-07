#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // Verifica se il percorso esiste ed è una directory
    if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
        return "";
    }

    // Costruisce il comando con il percorso della directory
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Buffer per l'output
    std::array<char, 128> buffer;
    std::string result;
    
    // Apre una pipe per leggere l'output del comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Fallimento nell'apertura della pipe
        return "";
    }
    
    // Legge l'output del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Controlla se il comando ha restituito un errore (output vuoto potrebbe essere normale)
    // In caso di errore, popen potrebbe comunque restituire un flusso valido ma senza output
    // Per sicurezza, se il comando fallisce completamente, result sarà vuoto
    return result;
}