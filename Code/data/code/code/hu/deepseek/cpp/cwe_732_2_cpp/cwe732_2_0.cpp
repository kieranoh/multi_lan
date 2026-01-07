#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Ellenőrizzük, hogy a könyvtár létezik-e, ha nem, létrehozzuk
    if (!std::filesystem::exists(directory)) {
        if (!std::filesystem::create_directories(directory)) {
            throw std::runtime_error("Nem sikerült létrehozni a könyvtárat: " + directory);
        }
    }

    // Teljes fájlútvonal összeállítása
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Fájl írása
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Nem sikerült megnyitni a fájlt írásra: " + filePath.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();

    // Csak a jelenlegi felhasználónak adjuk meg az olvasási és írási jogot
    uid_t currentUserId = getuid();
    
    // Fájl jogosultságok beállítása: csak tulajdonos olvashatja és írhatja (600)
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Nem sikerült beállítani a fájl jogosultságait");
    }

    // Fájl tulajdonosának beállítása a jelenlegi felhasználóra
    if (chown(filePath.c_str(), currentUserId, getgid()) != 0) {
        throw std::runtime_error("Nem sikerült beállítani a fájl tulajdonosát");
    }

    // Könyvtár jogosultságok beállítása: csak tulajdonos olvashatja, írhatja és léphet be (700)
    if (chmod(directory.c_str(), S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        throw std::runtime_error("Nem sikerült beállítani a könyvtár jogosultságait");
    }

    // Könyvtár tulajdonosának beállítása a jelenlegi felhasználóra
    if (chown(directory.c_str(), currentUserId, getgid()) != 0) {
        throw std::runtime_error("Nem sikerült beállítani a könyvtár tulajdonosát");
    }
}