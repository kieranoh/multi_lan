#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Crée le chemin complet du fichier
    std::string fullPath = directory + "/" + filename;

    // Ouvre un fichier en écriture
    std::ofstream outFile(fullPath);
    
    // Vérifie si le fichier est ouvert avec succès
    if (!outFile) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier pour l'écriture." << std::endl;
        return;
    }

    // Écrit le contenu dans le fichier
    outFile << content;
    outFile.close();

    // Change les permissions du fichier pour qu'il ne soit accessible que par l'utilisateur actuel
    chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
}