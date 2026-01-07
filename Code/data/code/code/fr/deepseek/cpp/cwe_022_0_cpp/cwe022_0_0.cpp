#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Construire le chemin complet du fichier
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Vérifier que le chemin est dans le répertoire spécifié (sécurité)
        std::filesystem::path canonical_dir;
        std::filesystem::path canonical_file;
        
        try {
            canonical_dir = std::filesystem::canonical(dir_path);
            canonical_file = std::filesystem::canonical(file_path);
        } catch (const std::filesystem::filesystem_error&) {
            // Si le chemin ne peut pas être rendu canonique, retourner chaîne vide
            return "";
        }
        
        // Vérifier que le fichier est bien dans le répertoire spécifié
        // compare les chemins pour s'assurer qu'il n'y a pas de traversal de répertoire
        std::string dir_str = canonical_dir.string();
        std::string file_str = canonical_file.string();
        
        if (file_str.compare(0, dir_str.length(), dir_str) != 0) {
            // Le fichier n'est pas dans le répertoire spécifié
            return "";
        }
        
        // Vérifier que c'est un fichier régulier (pas un répertoire)
        if (!std::filesystem::is_regular_file(canonical_file)) {
            return "";
        }
        
        // Ouvrir le fichier en mode binaire pour lire tout type de fichier
        std::ifstream file(canonical_file, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return "";
        }
        
        // Obtenir la taille du fichier
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Lire le contenu du fichier
        std::string content;
        content.resize(size);
        
        if (file.read(&content[0], size)) {
            return content;
        } else {
            return "";
        }
        
    } catch (const std::exception&) {
        // Intercepter toutes les exceptions et retourner une chaîne vide
        return "";
    }
}