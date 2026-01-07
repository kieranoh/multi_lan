#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Проверяем, является ли поддомен пустым или недействительным
    bool subdomain_invalid = subdomain_prefix.empty();
    
    // Проверяем, содержит ли поддомен только пробельные символы
    if (!subdomain_invalid) {
        bool all_whitespace = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                          [](unsigned char c) { return std::isspace(c); });
        subdomain_invalid = all_whitespace;
    }
    
    // Строим URL
    std::string url = "https://";
    
    if (!subdomain_invalid) {
        // Добавляем поддомен и точку
        url += subdomain_prefix + ".";
    }
    
    // Добавляем домен
    url += domain;
    
    return url;
}