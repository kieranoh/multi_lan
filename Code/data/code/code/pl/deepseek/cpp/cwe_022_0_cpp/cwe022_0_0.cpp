#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Utwórz pełną ścieżkę do pliku
        std::filesystem::path full_path = std::filesystem::path(dir_path) / filename;
        
        // Sprawdź, czy plik istnieje i jest zwykłym plikiem
        if (!std::filesystem::exists(full_path) || !std::filesystem::is_regular_file(full_path)) {
            return "";
        }
        
        // Otwórz plik w trybie binarnym, aby poprawnie obsłużyć wszystkie znaki
        std::ifstream file(full_path, std::ios::binary);
        
        // Sprawdź, czy plik został pomyślnie otwarty
        if (!file.is_open()) {
            return "";
        }
        
        // Określ rozmiar pliku
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Jeśli plik jest pusty, zwróć pusty ciąg
        if (file_size <= 0) {
            return "";
        }
        
        // Odczytaj całą zawartość pliku
        std::string content;
        content.resize(file_size);
        
        if (!file.read(&content[0], file_size)) {
            return "";
        }
        
        return content;
    }
    catch (const std::filesystem::filesystem_error&) {
        // Obsługa błędów systemu plików (np. brak uprawnień)
        return "";
    }
    catch (const std::bad_alloc&) {
        // Obsługa błędów alokacji pamięci dla dużych plików
        return "";
    }
    catch (...) {
        // Obsługa wszystkich innych nieoczekiwanych błędów
        return "";
    }
}