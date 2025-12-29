#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Vérification des paramètres d'entrée
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Fonction pour normaliser en minuscules
    auto to_lower = [](std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return str;
    };
    
    // Normaliser le domaine en minuscules
    std::string normalized_domain = to_lower(domain);
    
    // Extraire le protocole de l'URL cible
    std::string target_lower = to_lower(target);
    
    // Vérifier si l'URL cible commence par "https://"
    std::string https_prefix = "https://";
    std::string http_prefix = "http://";
    
    std::string target_without_protocol;
    std::string target_protocol;
    
    if (target_lower.find(https_prefix) == 0) {
        target_protocol = "https://";
        target_without_protocol = target.substr(https_prefix.length());
    } else if (target_lower.find(http_prefix) == 0) {
        target_protocol = "https://"; // On utilisera toujours https
        target_without_protocol = target.substr(http_prefix.length());
    } else {
        // Pas de protocole spécifié, on considère que c'est un chemin relatif
        // Dans ce cas, on retourne le domaine avec https
        return "https://" + domain;
    }
    
    // Extraire le domaine de l'URL cible (tout jusqu'au premier '/' ou fin de chaîne)
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_domain = target_without_protocol.substr(0, slash_pos);
    
    // Normaliser le domaine cible en minuscules pour la comparaison
    std::string normalized_target_domain = to_lower(target_domain);
    
    // Vérifier si le domaine cible se termine par le domaine fourni
    // On vérifie d'abord l'égalité exacte
    if (normalized_target_domain == normalized_domain) {
        return "https://" + target_without_protocol;
    }
    
    // Vérifier si le domaine cible est un sous-domaine du domaine fourni
    // Le domaine cible doit se terminer par "." + domaine
    if (normalized_target_domain.length() > normalized_domain.length() + 1 &&
        normalized_target_domain[normalized_target_domain.length() - normalized_domain.length() - 1] == '.' &&
        normalized_target_domain.substr(normalized_target_domain.length() - normalized_domain.length()) == normalized_domain) {
        return "https://" + target_without_protocol;
    }
    
    // Si aucun des cas ci-dessus ne correspond, retourner le domaine avec https
    return "https://" + domain;
}