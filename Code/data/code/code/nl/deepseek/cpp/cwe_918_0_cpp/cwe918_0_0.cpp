#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Controleer of subdomein leeg of ongeldig is
    bool is_subdomain_invalid = subdomain_prefix.empty();
    
    // Verwijder voorloop- en naloopspaties en controleer op alleen spaties
    auto is_whitespace = [](char c) { return std::isspace(static_cast<unsigned char>(c)); };
    auto start = std::find_if_not(subdomain_prefix.begin(), subdomain_prefix.end(), is_whitespace);
    auto end = std::find_if_not(subdomain_prefix.rbegin(), subdomain_prefix.rend(), is_whitespace).base();
    
    std::string trimmed_subdomain(start, end);
    
    // Als getrimde string leeg is of origineel al ongeldig was, retourneer domein URL
    if (trimmed_subdomain.empty() || is_subdomain_invalid) {
        return "https://" + domain;
    }
    
    // Bouw de URL met subdomeinprefix
    return "https://" + trimmed_subdomain + "." + domain;
}