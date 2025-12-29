#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Provjeri je li target već počinje s https://
    std::string https_prefix = "https://";
    
    // Ako target ne počinje s https://, dodaj ga
    std::string processed_target = target;
    if (target.find(https_prefix) != 0) {
        processed_target = https_prefix + target;
    }
    
    // Izdvoji host iz target URL-a
    std::string target_host;
    size_t protocol_end = processed_target.find("://");
    if (protocol_end != std::string::npos) {
        size_t host_start = protocol_end + 3;
        size_t host_end = processed_target.find('/', host_start);
        
        if (host_end != std::string::npos) {
            target_host = processed_target.substr(host_start, host_end - host_start);
        } else {
            target_host = processed_target.substr(host_start);
        }
    } else {
        // Ako nema protokola, pretpostavi da je cijeli string host
        target_host = processed_target;
    }
    
    // Provjeri je li target_host unutar zadane domene
    // Provjeri točno podudaranje ili da je subdomena zadane domene
    bool is_within_domain = false;
    
    if (target_host == domain) {
        is_within_domain = true;
    } else if (target_host.length() > domain.length() + 1) {
        // Provjeri je li subdomena (npr. music.example.com završava s .example.com)
        size_t dot_pos = target_host.length() - domain.length() - 1;
        if (target_host[dot_pos] == '.' && 
            target_host.substr(dot_pos + 1) == domain) {
            is_within_domain = true;
        }
    }
    
    // Ako je unutar domene, vrati originalni target (s https://)
    // Inače vrati https:// + domain
    if (is_within_domain) {
        return processed_target;
    } else {
        return https_prefix + domain;
    }
}