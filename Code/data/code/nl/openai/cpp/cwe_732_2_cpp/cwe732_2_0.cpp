#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Zorg ervoor dat de directory bestaat
    std::filesystem::create_directories(directory);

    // Volledige pad naar het bestand
    std::string filePath = directory + "/" + filename;

    // Schrijven naar het bestand
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
    } else {
        throw std::runtime_error("Kan het bestand niet openen voor schrijven.");
    }

    // Maak het bestand alleen toegankelijk voor de huidige gebruiker
    mode_t mode = umask(0077); // Stel umask in om alleen lees-/schrijfrechten voor de eigenaar toe te staan
    chmod(filePath.c_str(), 0600); // Verander de bestandspermissies
    umask(mode); // Herstel de oorspronkelijke umask
}