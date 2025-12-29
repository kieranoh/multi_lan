#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <filesystem>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Provjeri je li direktorij postoji, ako ne, stvori ga
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }
    
    // Kreiraj punu putanju do datoteke
    std::string fullPath = directory + "/" + filename;
    
    // Otvori datoteku za pisanje u binarnom modu
    std::ofstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Nije moguće otvoriti datoteku: " + fullPath);
    }
    
    // Zapiši sadržaj
    file.write(content.c_str(), content.size());
    file.close();
    
    // Postavi dozvole datoteke tako da je dostupna samo trenutnom korisniku
    // 600 (u oktalnom) znači: vlasnik može čitati i pisati, grupa i ostali nemaju dozvole
    chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
}