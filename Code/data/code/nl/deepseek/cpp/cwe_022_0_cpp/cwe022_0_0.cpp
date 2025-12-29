#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Controleer of de directory bestaat en toegankelijk is
    std::error_code ec;
    if (!std::filesystem::exists(dir_path, ec) || ec) {
        return "";
    }
    
    // Construeer het volledige pad naar het bestand
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // Controleer of het bestand bestaat en een regulier bestand is
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // Open het bestand voor lezen
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // Lees de volledige inhoud van het bestand
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    
    // Controleer op leesfouten
    if (!file) {
        return "";
    }
    
    return content;
}