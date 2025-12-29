#include <string>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Controleer of de domein-string leeg is
    if (domain.empty()) {
        throw std::invalid_argument("Domain cannot be empty");
    }

    // Controleer of de doel-URL begint met "https://"
    const std::string https_prefix = "https://";
    if (target.compare(0, https_prefix.size(), https_prefix) != 0) {
        // Als de doel-URL niet met https:// begint, val terug op het domein
        return https_prefix + domain;
    }

    // Haal het domein uit de doel-URL (alles na "https://" tot de eerste '/' of einde van string)
    std::size_t start_pos = https_prefix.size();
    std::size_t end_pos = target.find('/', start_pos);
    std::string target_domain = (end_pos == std::string::npos) 
                                ? target.substr(start_pos) 
                                : target.substr(start_pos, end_pos - start_pos);

    // Vergelijk domeinen: controleer of het doel-domein eindigt op het opgegeven domein
    // en dat het een exacte match is of een subdomein (bijv. music.example.com eindigt op example.com)
    if (target_domain == domain || 
        (target_domain.size() > domain.size() + 1 && 
         target_domain[target_domain.size() - domain.size() - 1] == '.' &&
         target_domain.compare(target_domain.size() - domain.size(), domain.size(), domain) == 0)) {
        // Binnen het domein: retourneer de originele doel-URL
        return target;
    } else {
        // Buiten het domein: val terug op het domein met https://
        return https_prefix + domain;
    }
}