#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Motif principal conforme à la RFC 5322 (version simplifiée mais robuste)
    const std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+)"
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?$)";
    
    std::regex email_regex(pattern);
    
    // Vérification de base de la longueur
    if (email.empty() || email.length() > 254) { // RFC 5321 limite à 254 caractères
        return std::make_tuple(false, "Length check failed");
    }
    
    // Vérifier qu'il y a exactement un '@'
    size_t at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, "Must contain exactly one @");
    }
    
    // Séparer la partie locale et le domaine
    size_t at_pos = email.find('@');
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Vérifications supplémentaires pour éviter les faux négatifs
    
    // 1. La partie locale ne doit pas commencer ou finir par un point
    if (!local_part.empty() && (local_part.front() == '.' || local_part.back() == '.')) {
        return std::make_tuple(false, "Local part cannot start or end with dot");
    }
    
    // 2. Pas de points consécutifs dans la partie locale
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Local part cannot have consecutive dots");
    }
    
    // 3. Le domaine ne doit pas commencer ou finir par un trait d'union
    if (!domain_part.empty() && (domain_part.front() == '-' || domain_part.back() == '-')) {
        return std::make_tuple(false, "Domain cannot start or end with hyphen");
    }
    
    // 4. Le domaine ne doit pas avoir de points consécutifs
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Domain cannot have consecutive dots");
    }
    
    // 5. Vérifier que le domaine a au moins un point (sauf pour les domaines locaux)
    // Pour une validation générale, on exige au moins un point dans le domaine
    if (domain_part.find('.') == std::string::npos) {
        // Certains environnements permettent les domaines sans point (localhost)
        // Mais pour une validation générale, on le rejette
        return std::make_tuple(false, "Domain must contain at least one dot");
    }
    
    // 6. Vérifier que le TLD (dernière partie) a au moins 2 caractères
    // (avec exceptions pour certains ccTLD comme .ai, .io, etc.)
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            // Certains TLD comme .ai ont 2 caractères, .a est invalide
            return std::make_tuple(false, "TLD must be at least 2 characters");
        }
        
        // Vérifier que le TLD ne contient que des lettres
        if (!std::all_of(tld.begin(), tld.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        })) {
            return std::make_tuple(false, "TLD must contain only letters");
        }
    }
    
    // 7. Vérification par expression régulière
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "Regex pattern mismatch");
    }
    
    // 8. Vérification supplémentaire pour les domaines avec traits d'union
    // Les traits d'union ne doivent pas être au début ou à la fin d'un label de domaine
    std::string domain_copy = domain_part;
    size_t start = 0;
    while (start < domain_copy.length()) {
        size_t dot_pos = domain_copy.find('.', start);
        std::string label = (dot_pos == std::string::npos) 
            ? domain_copy.substr(start) 
            : domain_copy.substr(start, dot_pos - start);
        
        if (!label.empty()) {
            if (label.front() == '-' || label.back() == '-') {
                return std::make_tuple(false, "Domain labels cannot start or end with hyphen");
            }
            
            // Vérifier la longueur du label (max 63 caractères selon RFC)
            if (label.length() > 63) {
                return std::make_tuple(false, "Domain label too long (max 63 chars)");
            }
        }
        
        if (dot_pos == std::string::npos) break;
        start = dot_pos + 1;
    }
    
    // 9. Vérifier la longueur de la partie locale (max 64 caractères selon RFC)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "Local part too long (max 64 chars)");
    }
    
    // Si toutes les vérifications passent
    return std::make_tuple(true, pattern);
}