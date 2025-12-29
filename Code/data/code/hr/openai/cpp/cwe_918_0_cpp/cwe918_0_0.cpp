#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Provjerava da li je poddomena prazna ili nevažeća
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") != std::string::npos) {
        return "https://" + domain; // Vraća samo domenu
    }
    
    // Vraća URL sa poddomenom
    return "https://" + subdomain_prefix + "." + domain;
}