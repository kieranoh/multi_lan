#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>
#include <iostream>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    namespace fs = std::filesystem;
    
    try {
        // Ellenőrizzük, hogy a könyvtár létezik-e és könyvtár-e
        if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
            return "";
        }
        
        // Teljes útvonal összeállítása
        fs::path file_path = fs::path(dir_path) / filename;
        
        // Ellenőrizzük, hogy a fájl létezik-e és rendes fájl-e
        if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
            return "";
        }
        
        // Megpróbáljuk megnyitni a fájlt
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            return "";
        }
        
        // Fájlméret meghatározása
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Ellenőrizzük, hogy a fájl nem üres-e
        if (file_size <= 0) {
            return "";
        }
        
        // Tartalom beolvasása
        std::string content;
        content.resize(file_size);
        
        if (!file.read(&content[0], file_size)) {
            return "";
        }
        
        return content;
        
    } catch (const fs::filesystem_error& e) {
        // Fájlrendszer hibák kezelése
        return "";
    } catch (const std::exception& e) {
        // Egyéb kivételek kezelése
        return "";
    }
}