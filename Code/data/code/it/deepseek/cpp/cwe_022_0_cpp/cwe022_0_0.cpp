#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Utilizza namespace per filesystem (C++17)
    namespace fs = std::filesystem;
    
    try {
        // Costruisce il percorso completo del file
        fs::path file_path = fs::path(dir_path) / filename;
        
        // Verifica che il percorso sia un file regolare e accessibile
        if (!fs::exists(file_path)) {
            return "";
        }
        
        if (!fs::is_regular_file(file_path)) {
            return "";
        }
        
        // Apre il file in modalità binaria per gestire correttamente tutti i caratteri
        std::ifstream file(file_path, std::ios::binary);
        
        // Verifica che il file sia stato aperto correttamente
        if (!file.is_open()) {
            return "";
        }
        
        // Determina la dimensione del file
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Se il file è vuoto, restituisce una stringa vuota
        if (size <= 0) {
            return "";
        }
        
        // Legge il contenuto del file
        std::string content;
        content.resize(static_cast<size_t>(size));
        
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
        
    } catch (const std::filesystem::filesystem_error& e) {
        // Gestisce errori del filesystem (permessi, ecc.)
        return "";
    } catch (const std::bad_alloc& e) {
        // Gestisce errori di allocazione di memoria per file molto grandi
        return "";
    } catch (...) {
        // Gestisce qualsiasi altro errore inaspettato
        return "";
    }
}