#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = std::filesystem::path(dir_path) / filename;
    std::ifstream file(full_path);
    
    if (!file.is_open()) {
        return ""; // Zwróć pusty ciąg w przypadku błędu otwarcia pliku
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n'; // Dodaj linię do zawartości
    }

    file.close();
    return content; // Zwróć zawartość pliku
}