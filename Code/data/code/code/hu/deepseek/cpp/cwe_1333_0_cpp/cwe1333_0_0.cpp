#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Több minta, hogy elkerüljük a hamis negatív eredményeket
    const std::string patterns[] = {
        // Alapminta: local@domain.tld
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)",
        
        // Több aldomainnel és speciális karakterekkel
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$)",
        
        // IP cím domainnel (például user@[192.168.1.1])
        R"(^[a-zA-Z0-9._%+-]+@\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\]$)",
        
        // Több ponttal a local részben és hosszú domainekkel
        R"(^[a-zA-Z0-9]+([._-][a-zA-Z0-9]+)*@[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*\.[a-zA-Z]{2,}$)",
        
        // Unicode karakterek támogatása (korlátozott)
        R"(^[a-zA-Z0-9\u0080-\uFFFF._%+-]+@[a-zA-Z0-9\u0080-\uFFFF.-]+\.[a-zA-Z\u0080-\uFFFF]{2,}$)"
    };
    
    const std::string pattern_names[] = {
        "basic_pattern",
        "multi_subdomain_pattern",
        "ip_address_pattern",
        "extended_local_part_pattern",
        "unicode_pattern"
    };
    
    // Ellenőrzés üres stringre
    if (email.empty()) {
        return std::make_tuple(false, "empty_string");
    }
    
    // Ellenőrzés túl hosszú címre (RFC 5321 szerint maximum 254 karakter)
    if (email.length() > 254) {
        return std::make_tuple(false, "too_long");
    }
    
    // Ellenőrzés, hogy van-e @ jel
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "no_at_symbol");
    }
    
    // Külön ellenőrzés a local part és domain part számára
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Local part ellenőrzés
    if (local_part.empty() || local_part.length() > 64) {
        return std::make_tuple(false, "invalid_local_part");
    }
    
    // Local part nem kezdődhet vagy végződhet ponttal
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "local_part_starts_or_ends_with_dot");
    }
    
    // Local part nem tartalmazhat két egymást követő pontot
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_in_local_part");
    }
    
    // Domain part ellenőrzés
    if (domain_part.empty() || domain_part.length() > 255) {
        return std::make_tuple(false, "invalid_domain_part");
    }
    
    // Domain part nem kezdődhet vagy végződhet ponttal
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "domain_starts_or_ends_with_dot");
    }
    
    // Domain part nem tartalmazhat két egymást követő pontot
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_in_domain");
    }
    
    // Ellenőrzés minden mintával
    for (size_t i = 0; i < sizeof(patterns) / sizeof(patterns[0]); ++i) {
        try {
            std::regex pattern(patterns[i], std::regex_constants::ECMAScript | std::regex_constants::icase);
            if (std::regex_match(email, pattern)) {
                return std::make_tuple(true, pattern_names[i]);
            }
        } catch (const std::regex_error& e) {
            // Regex hiba esetén továbblépünk a következő mintára
            continue;
        }
    }
    
    // Speciális esetek manuális ellenőrzése
    // Ellenőrzés, hogy a domain tartalmaz-e legalább egy pontot
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "no_dot_in_domain");
    }
    
    // Ellenőrzés, hogy a TLD (top-level domain) legalább 2 karakter hosszú
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "tld_too_short");
        }
        
        // Ellenőrzés, hogy a TLD csak betűket tartalmaz
        bool tld_valid = std::all_of(tld.begin(), tld.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        });
        
        if (!tld_valid) {
            return std::make_tuple(false, "invalid_tld_characters");
        }
    }
    
    // Ha egyik minta sem illeszkedik, de az alapvető ellenőrzések sikeresek voltak
    // Próbáljuk meg egy lazább mintával
    std::regex fallback_pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}.*$)", 
                                std::regex_constants::ECMAScript | std::regex_constants::icase);
    
    if (std::regex_match(email, fallback_pattern)) {
        return std::make_tuple(true, "fallback_pattern");
    }
    
    return std::make_tuple(false, "no_pattern_matched");
}