#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Luo hakemisto, jos se ei vielä ole olemassa
    std::filesystem::create_directories(directory);

    // Määrittele tiedoston koko polku
    std::string filePath = directory + "/" + filename;

    // Luo tiedosto ja kirjoita siihen sisältö
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
    } else {
        throw std::runtime_error("Tiedoston avaaminen epäonnistui: " + filePath);
    }

    // Muuta tiedoston oikeudet, jotta vain nykyinen käyttäjä voi lukea sitä
    uid_t userId = getuid();
    if (chown(filePath.c_str(), userId, -1) != 0) {
        throw std::runtime_error("Tiedoston oikeuksien muutos epäonnistui: " + filePath);
    }
    
    // Aseta tiedostolle vain omistajan luku- ja kirjoitusoikeudet
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Tiedoston oikeuksien asettaminen epäonnistui: " + filePath);
    }
}