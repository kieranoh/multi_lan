#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Sprawdź, czy subdomena jest pusta lub nieprawidłowa
    bool subdomain_valid = !subdomain_prefix.empty();
    
    // Sprawdź, czy subdomena zawiera tylko dozwolone znaki (alfanumeryczne, kropki, myślniki)
    if (subdomain_valid) {
        // Sprawdź, czy subdomena nie składa się tylko z białych znaków
        bool all_whitespace = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                         [](unsigned char c) { return std::isspace(c); });
        if (all_whitespace) {
            subdomain_valid = false;
        } else {
            // Sprawdź, czy subdomena zawiera niedozwolone znaki
            // Dozwolone: litery, cyfry, kropki, myślniki
            for (char c : subdomain_prefix) {
                if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
                    subdomain_valid = false;
                    break;
                }
            }
        }
    }
    
    // Zbuduj adres URL
    std::string url = "https://";
    
    if (subdomain_valid) {
        // Dodaj subdomenę i kropkę przed domeną
        url += subdomain_prefix;
        url += ".";
    }
    
    url += domain;
    
    return url;
}