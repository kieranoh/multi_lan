#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Fitxategiaren bide osoa eraiki
    std::filesystem::path full_path = std::filesystem::path(dir_path) / filename;
    
    // Egiaztatu fitxategia existitzen dela eta fitxategi arrunta dela
    std::error_code ec;
    if (!std::filesystem::exists(full_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(full_path, ec) || ec) {
        return "";
    }
    
    // Ireki fitxategia irakurtzeko
    std::ifstream file(full_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return "";
    }
    
    // Fitxategiaren tamaina lortu
    std::ifstream::pos_type file_size = file.tellg();
    if (file_size == std::ifstream::pos_type(-1)) {
        return "";
    }
    
    // Hasierara itzuli
    file.seekg(0, std::ios::beg);
    
    // Edukia irakurri
    std::string content;
    content.resize(static_cast<size_t>(file_size));
    
    if (!file.read(&content[0], file_size)) {
        return "";
    }
    
    return content;
}