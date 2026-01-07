#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // Kreiramo punu putanju do datoteke
    std::ifstream file(full_path); // Otvaramo datoteku

    if (!file) { // Provjeravamo da li je datoteka uspješno otvorena
        return ""; // Ako nije, vraćamo prazan string
    }

    std::string content;
    std::string line;

    while (std::getline(file, line)) { // Čitamo datoteku liniju po liniju
        content += line + "\n"; // Dodajemo liniju u sadržaj
    }

    file.close(); // Zatvaramo datoteku
    return content; // Vraćamo sadržaj datoteke
}