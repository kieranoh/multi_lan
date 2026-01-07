#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;

    // Utilisation de popen pour exécuter la commande et récupérer la sortie
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Retourner une chaîne vide en cas d'erreur
    }
    
    // Lire la sortie de la commande ligne par ligne
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Retourner la sortie de la commande
}