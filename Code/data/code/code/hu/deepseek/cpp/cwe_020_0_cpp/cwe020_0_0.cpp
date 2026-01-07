#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Ellenőrizzük, hogy a domain nem üres
    if (domain.empty()) {
        throw std::invalid_argument("Domain cannot be empty");
    }

    // Regex a URL kinyeréséhez
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)(\?[^#]*)?(#.*)?$)", std::regex::icase);
    std::smatch url_match;
    
    // Ha a target nem valid URL, akkor visszatérünk a domain alapú URL-lel
    if (!std::regex_match(target, url_match, url_regex)) {
        return "https://" + domain;
    }
    
    // Kinyerjük a protokollt, hostot és utat
    std::string protocol = url_match[1].str();
    std::string host = url_match[2].str();
    std::string path = url_match[3].str();
    
    // Átalakítjuk a hostot és domain-t kisbetűssé az összehasonlításhoz
    std::string host_lower = host;
    std::string domain_lower = domain;
    std::transform(host_lower.begin(), host_lower.end(), host_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(domain_lower.begin(), domain_lower.end(), domain_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // Ellenőrizzük, hogy a host a megadott domain-en belül van-e
    // Ez lehet pontosan egyezik, vagy aldomain (pl. music.example.com ends with .example.com)
    bool is_within_domain = false;
    
    if (host_lower == domain_lower) {
        is_within_domain = true;
    } else if (host_lower.length() > domain_lower.length() + 1) {
        // Ellenőrizzük, hogy a host végződik-e ".domain"-nel
        if (host_lower[host_lower.length() - domain_lower.length() - 1] == '.' &&
            host_lower.substr(host_lower.length() - domain_lower.length()) == domain_lower) {
            is_within_domain = true;
        }
    }
    
    // Ha a cél URL a domain-en belül van, használjuk a teljes URL-t (de https-re cseréljük)
    if (is_within_domain) {
        // Mindig https-t használunk
        return "https://" + host + path;
    } else {
        // Különben térjünk vissza a domain alapú URL-lel
        return "https://" + domain;
    }
}