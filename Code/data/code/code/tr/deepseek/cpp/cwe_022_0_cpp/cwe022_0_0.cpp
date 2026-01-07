#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Dizin yolunu ve dosya adını birleştir
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Dosyanın var olup olmadığını ve normal bir dosya olduğunu kontrol et
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Dosyayı aç ve oku
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return "";
        }
        
        // Dosya boyutunu al
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // İçeriği oku
        std::string content(size, '\0');
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
    }
    catch (const std::filesystem::filesystem_error&) {
        // Dosya sistemi hataları (izin, yol vb.)
        return "";
    }
    catch (const std::bad_alloc&) {
        // Bellek tahsis hatası
        return "";
    }
    catch (...) {
        // Diğer tüm hatalar
        return "";
    }
}