#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Koristimo std::filesystem za bezbedno konstruisanje putanje
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // Proveravamo da li datoteka postoji i da li je regularna datoteka
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // Otvaramo datoteku za čitanje u binarnom modu da bismo pravilno obradili sve karaktere
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // Određujemo veličinu datoteke
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // Ako je datoteka prazna, vratimo prazan string
    if (size <= 0) {
        return "";
    }
    
    // Čitamo ceo sadržaj datoteke
    std::string content;
    content.resize(size);
    
    if (!file.read(&content[0], size)) {
        return "";
    }
    
    return content;
}