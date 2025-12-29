#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Kontrollera om subdomänprefixet är tomt eller ogiltigt
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        // Om ogiltigt, returnera bara domänen med HTTPS-protokollet
        return "https://" + domain;
    }
    
    // Om subdomänprefixet är giltigt, returnera den kompletta URL:en
    return "https://" + subdomain_prefix + "." + domain;
}