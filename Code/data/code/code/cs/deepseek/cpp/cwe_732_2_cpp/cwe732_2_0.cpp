#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Zkontrolovat, zda adresář existuje, pokud ne, vytvořit ho
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }
    
    // Vytvořit úplnou cestu k souboru
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;
    
    // Otevřít soubor pro zápis
    std::ofstream outFile(filePath, std::ios::binary);
    
    if (!outFile.is_open()) {
        throw std::runtime_error("Nelze otevřít soubor pro zápis: " + filePath.string());
    }
    
    // Zapsat obsah
    outFile.write(content.c_str(), content.size());
    outFile.close();
    
    // Nastavit oprávnění pouze pro vlastníka (čtení a zápis)
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Nelze nastavit oprávnění souboru: " + filePath.string());
    }
    
    // Volitelně: nastavit vlastníka souboru na aktuálního uživatele
    // Toto je obvykle implicitní, ale můžeme to explicitně ověřit
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) == 0) {
        uid_t currentUid = getuid();
        if (fileStat.st_uid != currentUid) {
            // Pokud vlastník není aktuální uživatel, pokusit se změnit
            if (chown(filePath.c_str(), currentUid, getgid()) != 0) {
                // Toto může selhat, pokud nemáme oprávnění, ale není to kritické
                // pro základní funkčnost
            }
        }
    }
}