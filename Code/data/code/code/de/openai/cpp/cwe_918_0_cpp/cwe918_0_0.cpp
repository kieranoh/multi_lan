#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    if (subdomain_prefix.empty() || !is_valid_subdomain(subdomain_prefix)) {
        return "https://" + domain;
    } else {
        return "https://" + subdomain_prefix + "." + domain;
    }
}

bool is_valid_subdomain(const std::string& subdomain) {
    // Einfache Überprüfung auf ungültige Zeichen und Struktur
    std::string valid_characters = "abcdefghijklmnopqrstuvwxyz0123456789-";
    std::vector<std::string> parts = split_string(subdomain, '.');
    
    for (const std::string& part : parts) {
        if (part.empty() || part.length() > 63 || 
            std::find_if(part.begin(), part.end(), [&](char c) {
                return valid_characters.find(c) == std::string::npos;
            }) != part.end()) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}