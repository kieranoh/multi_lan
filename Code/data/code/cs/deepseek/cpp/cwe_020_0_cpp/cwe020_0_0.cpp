#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Kontrola prázdných vstupů
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Pomocná funkce pro normalizaci řetězce na malá písmena
    auto to_lower = [](const std::string& str) -> std::string {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        return result;
    };
    
    // Normalizace cíle a domény na malá písmena pro porovnání bez ohledu na velikost
    std::string target_lower = to_lower(target);
    std::string domain_lower = to_lower(domain);
    
    // Odstranění protokolu z cíle pro analýzu
    std::string target_without_protocol;
    
    // Kontrola, zda cíl začíná "https://"
    if (target_lower.find("https://") == 0) {
        target_without_protocol = target_lower.substr(8); // 8 = délka "https://"
    }
    // Kontrola, zda cíl začíná "http://"
    else if (target_lower.find("http://") == 0) {
        target_without_protocol = target_lower.substr(7); // 7 = délka "http://"
    }
    else {
        // Pokud cíl nezačíná protokolem, považujeme celý řetězec za cestu bez protokolu
        target_without_protocol = target_lower;
    }
    
    // Najdeme první '/' pro oddělení hostitele od cesty
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_host = target_without_protocol;
    std::string target_path = "";
    
    if (slash_pos != std::string::npos) {
        target_host = target_without_protocol.substr(0, slash_pos);
        target_path = target_without_protocol.substr(slash_pos);
    }
    
    // Kontrola, zda hostitel cíle končí zadanou doménou
    bool is_within_domain = false;
    
    // Přesná shoda domény
    if (target_host == domain_lower) {
        is_within_domain = true;
    }
    // Subdoména domény (např. music.example.com končí na .example.com)
    else if (target_host.length() > domain_lower.length() + 1) {
        if (target_host[target_host.length() - domain_lower.length() - 1] == '.' &&
            target_host.substr(target_host.length() - domain_lower.length()) == domain_lower) {
            is_within_domain = true;
        }
    }
    
    // Vrácení výsledku
    if (is_within_domain) {
        // Pokud původní cíl již začínal na https://, vrátíme ho beze změny
        if (target.find("https://") == 0) {
            return target;
        }
        // Pokud původní cíl začínal na http://, změníme na https://
        else if (target.find("http://") == 0) {
            return "https://" + target.substr(7);
        }
        // Pokud cíl nezačínal protokolem, přidáme https://
        else {
            return "https://" + target;
        }
    } else {
        // Cíl není v doméně, vrátíme doménu s https://
        return "https://" + domain;
    }
}