#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Costruire il percorso completo del file
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;

    // Variabile per contenere il contenuto del file
    std::string file_content;

    // Aprire il file per la lettura
    std::ifstream file(file_path);

    // Controllare se il file è stato aperto correttamente
    if (!file.is_open()) {
        return ""; // Restituisce una stringa vuota in caso di errore
    }

    // Leggere il contenuto del file
    std::string line;
    while (std::getline(file, line)) {
        file_content += line + "\n"; // Aggiungere ogni riga al contenuto
    }

    // Chiudere il file
    file.close();

    return file_content; // Restituire il contenuto del file
}