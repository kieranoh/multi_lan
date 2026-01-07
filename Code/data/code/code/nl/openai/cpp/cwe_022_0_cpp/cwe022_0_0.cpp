#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string file_path = std::filesystem::path(dir_path) / filename;
    std::ifstream file(file_path);
    
    if (!file.is_open()) {
        return ""; // Retourneer een lege string bij een fout
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n'; // Voeg elke regel toe aan de inhoud
    }

    file.close();
    return content; // Retourneer de inhoud van het bestand
}