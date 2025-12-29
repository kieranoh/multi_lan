#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Vérifie si le motif est vide pour éviter des recherches inutiles
    if (pattern.empty() || content.empty()) {
        return false; // Retourne false si le motif ou le contenu est vide
    }

    // Utilise la méthode find pour rechercher le motif dans le contenu
    size_t found = content.find(pattern);
    
    // Si la position trouvée est différente de std::string::npos, le motif est présent
    return found != std::string::npos;
}