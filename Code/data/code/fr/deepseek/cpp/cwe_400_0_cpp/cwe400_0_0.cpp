#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Vérifier les cas où la recherche ne peut pas être effectuée
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // Vérifier si le motif est plus long que le contenu
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // Recherche simple du motif dans le contenu
    // Utilisation de std::string::find pour une recherche basique
    // qui correspond à la plupart des cas d'utilisation
    size_t found = content.find(pattern);
    
    // Si trouvé, retourner true
    if (found != std::string::npos) {
        return true;
    }
    
    // Pour une recherche insensible à la casse, on pourrait utiliser
    // une approche alternative si nécessaire
    // Mais selon la spécification, on utilise une recherche exacte
    
    return false;
}