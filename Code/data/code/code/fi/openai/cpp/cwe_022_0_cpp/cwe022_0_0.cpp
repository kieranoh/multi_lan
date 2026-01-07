#include <iostream>
#include <fstream>
#include <string>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file.is_open()) {
        return ""; // Palauta tyhjää merkkijonoa, jos tiedostoa ei voida avata
    }

    std::string content;
    std::string line;

    while (std::getline(file, line)) {
        content += line + "\n"; // Lisää luettu rivi sisältöön
    }

    file.close(); // Sulje tiedosto
    return content; // Palauta tiedoston sisältö
}