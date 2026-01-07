#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Tarkista, että parametrit eivät ole tyhjiä
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }
    
    // Normalisoi domain poistamalla mahdolliset etuliitteet ja jälkiliitteet
    std::string normalized_domain = domain;
    
    // Poista mahdolliset välilyönnit alusta ja lopusta
    normalized_domain.erase(0, normalized_domain.find_first_not_of(" \t\n\r\f\v"));
    normalized_domain.erase(normalized_domain.find_last_not_of(" \t\n\r\f\v") + 1);
    
    // Poista mahdollinen "https://" tai "http://" etuliite
    if (normalized_domain.find("https://") == 0) {
        normalized_domain = normalized_domain.substr(8);
    } else if (normalized_domain.find("http://") == 0) {
        normalized_domain = normalized_domain.substr(7);
    }
    
    // Poista mahdollinen "/" lopusta
    if (!normalized_domain.empty() && normalized_domain.back() == '/') {
        normalized_domain.pop_back();
    }
    
    // Tarkista, onko targetissa jo https://
    std::string normalized_target = target;
    
    // Poista mahdolliset välilyönnit alusta ja lopusta
    normalized_target.erase(0, normalized_target.find_first_not_of(" \t\n\r\f\v"));
    normalized_target.erase(normalized_target.find_last_not_of(" \t\n\r\f\v") + 1);
    
    // Jos target alkaa https://, käytä sitä sellaisenaan
    if (normalized_target.find("https://") == 0) {
        // Poimitaan domain osa targetista vertailua varten
        std::string target_domain = normalized_target.substr(8); // Poista "https://"
        
        // Etsi ensimmäinen "/" (jos on)
        size_t slash_pos = target_domain.find('/');
        if (slash_pos != std::string::npos) {
            target_domain = target_domain.substr(0, slash_pos);
        }
        
        // Vertaa domainia (case-insensitive)
        std::string target_domain_lower = target_domain;
        std::string normalized_domain_lower = normalized_domain;
        
        std::transform(target_domain_lower.begin(), target_domain_lower.end(), 
                      target_domain_lower.begin(), ::tolower);
        std::transform(normalized_domain_lower.begin(), normalized_domain_lower.end(), 
                      normalized_domain_lower.begin(), ::tolower);
        
        // Tarkista, päättyykö target_domain annettuun domainiin
        if (target_domain_lower == normalized_domain_lower || 
            (target_domain_lower.length() > normalized_domain_lower.length() + 1 &&
             target_domain_lower.substr(target_domain_lower.length() - normalized_domain_lower.length() - 1) == 
             "." + normalized_domain_lower)) {
            // Target on annetussa verkkotunnuksessa
            return normalized_target;
        } else {
            // Target ei ole annetussa verkkotunnuksessa, käytetään domainia
            return "https://" + normalized_domain;
        }
    }
    // Jos target alkaa http://, muunnetaan se https://:ksi
    else if (normalized_target.find("http://") == 0) {
        // Poimitaan domain osa targetista vertailua varten
        std::string target_domain = normalized_target.substr(7); // Poista "http://"
        
        // Etsi ensimmäinen "/" (jos on)
        size_t slash_pos = target_domain.find('/');
        if (slash_pos != std::string::npos) {
            target_domain = target_domain.substr(0, slash_pos);
        }
        
        // Vertaa domainia (case-insensitive)
        std::string target_domain_lower = target_domain;
        std::string normalized_domain_lower = normalized_domain;
        
        std::transform(target_domain_lower.begin(), target_domain_lower.end(), 
                      target_domain_lower.begin(), ::tolower);
        std::transform(normalized_domain_lower.begin(), normalized_domain_lower.end(), 
                      normalized_domain_lower.begin(), ::tolower);
        
        // Tarkista, päättyykö target_domain annettuun domainiin
        if (target_domain_lower == normalized_domain_lower || 
            (target_domain_lower.length() > normalized_domain_lower.length() + 1 &&
             target_domain_lower.substr(target_domain_lower.length() - normalized_domain_lower.length() - 1) == 
             "." + normalized_domain_lower)) {
            // Target on annetussa verkkotunnuksessa, muunnetaan https://:ksi
            return "https://" + normalized_target.substr(7);
        } else {
            // Target ei ole annetussa verkkotunnuksessa, käytetään domainia
            return "https://" + normalized_domain;
        }
    }
    // Jos target ei ala protokollalla, oletetaan että se on suhteellinen polku
    else {
        // Tässä tapauksessa target on jo domainissa, joten palautetaan https:// + domain + target
        // Tarkistetaan ensin, alkaako target "/":lla
        if (!normalized_target.empty() && normalized_target[0] == '/') {
            return "https://" + normalized_domain + normalized_target;
        } else {
            return "https://" + normalized_domain + "/" + normalized_target;
        }
    }
}