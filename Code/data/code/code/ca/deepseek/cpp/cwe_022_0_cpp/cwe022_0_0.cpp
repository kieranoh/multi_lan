#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Utilitzem std::filesystem per manipular camins de manera segura
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // Verifiquem si el fitxer existeix i és un fitxer regular
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // Obrim el fitxer en mode binari per llegir tots els caràcters correctament
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // Llegim tot el contingut del fitxer
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    
    // Verifiquem si hi ha hagut errors durant la lectura
    if (!file) {
        return "";
    }
    
    return content;
}