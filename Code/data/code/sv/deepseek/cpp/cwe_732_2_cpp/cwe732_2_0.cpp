#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <filesystem>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Skapa katalogen om den inte finns med rätt behörigheter
    std::filesystem::path dir_path(directory);
    
    if (!std::filesystem::exists(dir_path)) {
        // Skapa katalogen med endast behörighet för aktuell användare (700)
        std::filesystem::create_directories(dir_path);
        std::filesystem::permissions(dir_path, 
            std::filesystem::perms::owner_all |
            std::filesystem::perms::group_none |
            std::filesystem::perms::others_none);
    } else {
        // Säkerställ att katalogen har rätt behörigheter (700)
        std::filesystem::permissions(dir_path, 
            std::filesystem::perms::owner_all |
            std::filesystem::perms::group_none |
            std::filesystem::perms::others_none);
    }
    
    // Skapa fullständig sökväg till filen
    std::filesystem::path file_path = dir_path / filename;
    
    // Öppna filen för skrivning
    std::ofstream out_file(file_path, std::ios::binary);
    
    if (!out_file.is_open()) {
        throw std::runtime_error("Kunde inte öppna filen för skrivning: " + file_path.string());
    }
    
    // Skriv innehållet till filen
    out_file.write(content.c_str(), content.size());
    out_file.close();
    
    // Ställ in filbehörigheter till endast aktuell användare (600)
    std::filesystem::permissions(file_path, 
        std::filesystem::perms::owner_read | std::filesystem::perms::owner_write |
        std::filesystem::perms::group_none |
        std::filesystem::perms::others_none);
}