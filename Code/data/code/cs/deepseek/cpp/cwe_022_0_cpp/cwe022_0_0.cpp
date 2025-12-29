#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Vytvoření cesty k souboru pomocí filesystem API
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Kontrola existence souboru
        if (!std::filesystem::exists(file_path)) {
            return "";
        }
        
        // Kontrola, zda se jedná o běžný soubor (ne adresář)
        if (!std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Otevření souboru v binárním režimu pro správné zpracování všech znaků
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        
        // Kontrola, zda se soubor podařilo otevřít
        if (!file.is_open()) {
            return "";
        }
        
        // Získání velikosti souboru
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Načtení obsahu souboru
        std::string content;
        content.resize(size);
        
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
    }
    catch (const std::filesystem::filesystem_error&) {
        // Zachycení chyb filesystem (např. problémy s oprávněními)
        return "";
    }
    catch (const std::bad_alloc&) {
        // Zachycení chyb alokace paměti pro velké soubory
        return "";
    }
    catch (...) {
        // Zachycení všech ostatních neočekávaných výjimek
        return "";
    }
}