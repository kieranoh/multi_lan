#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Tarkistetaan, onko aliverkkotunnus tyhjä tai sisältää vain whitespace-merkkejä
    bool subdomain_empty = true;
    for (char c : subdomain_prefix) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            subdomain_empty = false;
            break;
        }
    }
    
    // Jos aliverkkotunnus on tyhjä, palautetaan vain verkkotunnus HTTPS-protokollalla
    if (subdomain_empty) {
        return "https://" + domain;
    }
    
    // Poistetaan ylimääräiset välilyönnit alusta ja lopusta
    size_t start = 0;
    size_t end = subdomain_prefix.length();
    
    while (start < end && std::isspace(static_cast<unsigned char>(subdomain_prefix[start]))) {
        start++;
    }
    
    while (end > start && std::isspace(static_cast<unsigned char>(subdomain_prefix[end - 1]))) {
        end--;
    }
    
    std::string cleaned_subdomain = subdomain_prefix.substr(start, end - start);
    
    // Jos puhdistettu aliverkkotunnus on tyhjä, palautetaan vain verkkotunnus
    if (cleaned_subdomain.empty()) {
        return "https://" + domain;
    }
    
    // Muodostetaan URL
    return "https://" + cleaned_subdomain + "." + domain;
}