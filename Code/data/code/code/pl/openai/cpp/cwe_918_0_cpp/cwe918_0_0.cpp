#include <string>
#include <iostream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Sprawdź, czy subdomena jest pusta lub nieprawidłowa
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // Zwróć tylko domenę, jeśli subdomena jest nieprawidłowa
    }
    
    // Zwróć poprawny adres URL z subdomeną
    return "https://" + subdomain_prefix + "." + domain;
}