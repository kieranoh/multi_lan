#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Construire la commande avec le chemin fourni
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Ouvrir un pipe pour lire la sortie de la commande
    std::array<char, 128> buffer;
    std::string result;
    
    // Utiliser unique_ptr pour garantir la fermeture du flux
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Échec de l'ouverture du pipe
        return "";
    }
    
    // Lire la sortie de la commande
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Vérifier si la commande a réussi (result non vide)
    // Note: popen ne retourne pas d'erreur si la commande échoue, 
    // mais redirige stderr vers /dev/null, donc result sera vide en cas d'erreur
    return result;
}