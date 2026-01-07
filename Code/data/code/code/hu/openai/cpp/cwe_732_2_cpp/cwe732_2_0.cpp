#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Ellenőrizzük, hogy a könyvtár létezik-e
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    // Fájl elérési út létrehozása
    std::string filePath = directory + "/" + filename;

    // Fájl megnyitása írásra
    std::ofstream outFile(filePath);
    
    // Ellenőrizzük, hogy a fájl sikeresen megnyílt-e
    if (!outFile) {
        throw std::runtime_error("Nem sikerült megnyitni a fájlt: " + filePath);
    }

    // A tartalom kiírása a fájlba
    outFile << content;
    
    // Fájl bezárása
    outFile.close();

    // A fájl jogosultságainak módosítása, hogy csak a jelenlegi felhasználó számára legyen elérhető
    int result = chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    if (result != 0) {
        throw std::runtime_error("Nem sikerült módosítani a fájl jogosultságait: " + filePath);
    }
}