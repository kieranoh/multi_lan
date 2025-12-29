#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Adierazi HTTPS protokoloa
    const std::string protocol = "https://";
    
    // Azpidomeina balidatzeko regexa definitu
    std::regex valid_subdomain_regex("^[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*$");
    
    // Azpidomeina hutsik edo baliogabea bada, domeinu nagusia itzuli
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, valid_subdomain_regex)) {
        return protocol + domain;
    }
    
    // Hutsik ez den azpidomeina osatu
    return protocol + subdomain_prefix + "." + domain;
}