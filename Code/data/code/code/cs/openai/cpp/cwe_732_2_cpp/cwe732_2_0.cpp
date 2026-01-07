#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Vytvoření cesty k souboru
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Otevření souboru pro zápis
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Nelze otevřít soubor pro zápis: " + filePath.string());
    }

    // Zápis obsahu do souboru
    outFile << content;
    outFile.close();

    // Získání ID aktuálního uživatele
    uid_t userId = getuid();

    // Změna oprávnění souboru tak, aby byl přístupný pouze aktuálnímu uživateli
    if (chown(filePath.c_str(), userId, userId) != 0) {
        throw std::runtime_error("Nelze změnit vlastníka souboru: " + filePath.string());
    }

    // Změna oprávnění souboru na 600 (pouze pro čtení a zápis pro vlastníka)
    if (chmod(filePath.c_str(), 0600) != 0) {
        throw std::runtime_error("Nelze změnit oprávnění souboru: " + filePath.string());
    }
}