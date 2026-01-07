#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Skapa fullständig sökväg till filen
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // Kontrollera att filen finns och är en vanlig fil
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // Försök öppna filen
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return "";
    }
    
    // Hämta filstorlek
    std::streamsize size = file.tellg();
    if (size == -1) {
        return "";
    }
    
    file.seekg(0, std::ios::beg);
    
    // Läs filinnehåll
    std::string content;
    content.resize(size);
    
    if (!file.read(&content[0], size)) {
        return "";
    }
    
    return content;
}