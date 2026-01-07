#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Tarkista, että hakemisto on olemassa, luo se tarvittaessa
    if (!std::filesystem::exists(directory)) {
        try {
            std::filesystem::create_directories(directory);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Virhe hakemiston luomisessa: " << e.what() << std::endl;
            return;
        }
    }
    
    // Tarkista, että hakemisto on todellakin hakemisto
    if (!std::filesystem::is_directory(directory)) {
        std::cerr << "Annettu polku ei ole hakemisto: " << directory << std::endl;
        return;
    }
    
    // Muodosta koko tiedostopolku
    std::filesystem::path filepath = std::filesystem::path(directory) / filename;
    
    // Avaa tiedosto kirjoitusta varten
    std::ofstream outfile(filepath, std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "Virhe tiedoston avaamisessa: " << filepath << std::endl;
        return;
    }
    
    // Kirjoita sisältö tiedostoon
    outfile.write(content.c_str(), content.size());
    outfile.close();
    
    // Aseta tiedoston käyttöoikeudet vain nykyiselle käyttäjälle (600)
    try {
        std::filesystem::permissions(filepath,
            std::filesystem::perms::owner_read | std::filesystem::perms::owner_write,
            std::filesystem::perm_options::replace);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Virhe käyttöoikeuksien asettamisessa: " << e.what() << std::endl;
        return;
    }
    
    // Varmista, että hakemiston käyttöoikeudet ovat turvalliset (700)
    try {
        std::filesystem::permissions(directory,
            std::filesystem::perms::owner_all,
            std::filesystem::perm_options::replace);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Virhe hakemiston käyttöoikeuksien asettamisessa: " << e.what() << std::endl;
    }
}