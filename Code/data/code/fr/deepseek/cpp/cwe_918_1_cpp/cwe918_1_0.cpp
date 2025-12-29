#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Vérifier si l'identifiant utilisateur est vide ou invalide
    if (user_id.empty()) {
        return "";
    }
    
    // Vérifier si l'identifiant utilisateur contient uniquement des caractères valides
    // Pour un identifiant utilisateur, nous acceptons généralement des lettres, chiffres et certains caractères spéciaux
    // Ici, nous vérifions qu'il n'est pas entièrement composé d'espaces ou de caractères de contrôle
    bool is_invalid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c)) || std::iscntrl(static_cast<unsigned char>(c));
    });
    
    if (is_invalid) {
        return "";
    }
    
    // Construire l'URL complète
    // S'assurer qu'il n'y a pas de double slash
    std::string result = api_url;
    
    // Ajouter un slash séparateur si nécessaire
    if (!result.empty() && result.back() != '/') {
        result += '/';
    }
    
    // Ajouter l'identifiant utilisateur
    result += user_id;
    
    return result;
}