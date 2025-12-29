#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Définir la longueur de la clé RSA (2048 bits est une valeur sécurisée standard)
    const int key_length = 2048;
    
    // Construire la commande openssl
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Buffer pour stocker le résultat
    std::array<char, 128> buffer;
    std::string result;
    
    // Ouvrir un pipe pour lire la sortie de la commande
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Échec de l'ouverture du pipe
        return "";
    }
    
    // Lire la sortie de la commande
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Vérifier si le résultat est vide (erreur lors de la génération)
    if (result.empty()) {
        return "";
    }
    
    return result;
}