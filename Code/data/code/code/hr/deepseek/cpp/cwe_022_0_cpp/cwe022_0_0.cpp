#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Koristimo std::filesystem za manipulaciju putanjama i provjere
    namespace fs = std::filesystem;
    
    try {
        // Sastavi punu putanju do datoteke
        fs::path file_path = fs::path(dir_path) / filename;
        
        // Provjeri postoji li datoteka i je li regularna datoteka
        if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
            return "";
        }
        
        // Otvori datoteku za čitanje u binarnom modu kako bi se pravilno čitali svi znakovi
        std::ifstream file(file_path, std::ios::binary);
        
        // Provjeri je li datoteka uspješno otvorena
        if (!file.is_open()) {
            return "";
        }
        
        // Odredi veličinu datoteke
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Ako je datoteka prazna, vrati prazan string
        if (size <= 0) {
            return "";
        }
        
        // Pročitaj cijeli sadržaj datoteke
        std::string content;
        content.resize(static_cast<size_t>(size));
        
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
        
    } catch (const std::exception&) {
        // Uhvati sve iznimke (filesystem_error, bad_alloc, itd.) i vrati prazan string
        return "";
    }
}