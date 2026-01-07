#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Vérifier si le répertoire existe, sinon le créer
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }
    
    // Construire le chemin complet du fichier
    std::string fullPath = directory + "/" + filename;
    
    // Ouvrir le fichier en mode écriture
    std::ofstream file(fullPath, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        // Si l'ouverture échoue, on retourne gracieusement
        return;
    }
    
    // Écrire le contenu dans le fichier
    file.write(content.c_str(), content.size());
    file.close();
    
    // Définir les permissions du fichier pour qu'il soit accessible uniquement par l'utilisateur actuel
    // 0600 = rw------- (lecture/écriture pour le propriétaire uniquement)
    chmod(fullPath.c_str(), S_IRUSR | S_IWUSR);
}