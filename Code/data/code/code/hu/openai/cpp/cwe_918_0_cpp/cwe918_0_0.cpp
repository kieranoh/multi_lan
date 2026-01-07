#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Ellenőrizzük, hogy a subdomain_prefix érvényes-e
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // Ha üres vagy érvénytelen, a domain URL-t adjuk vissza
    }
    return "https://" + subdomain_prefix + "." + domain; // Érvényes aldomain esetén generáljunk URL-t
}