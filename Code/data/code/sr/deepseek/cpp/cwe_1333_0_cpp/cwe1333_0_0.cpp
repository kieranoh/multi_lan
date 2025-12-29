#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Obrazac koji pokriva većinu validnih email adresa prema RFC 5322
    // Ovaj obrazac je prilagođen da bude manje restriktivan i pokrije više slučajeva
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"  // lokalni deo
        R"(@)"                                                                       // @ simbol
        R"((?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+)"                         // domen (jedan ili više subdomena)
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";                             // TLD
    
    std::regex email_regex(pattern);
    
    // Provera osnovnih uslova pre regex-a za bolju performansu
    if (email.empty()) {
        return std::make_tuple(false, "empty");
    }
    
    // Provera da li postoji tačno jedan @ simbol
    size_t at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, "invalid_at_count");
    }
    
    // Pronalaženje pozicije @ simbola
    size_t at_pos = email.find('@');
    
    // Provera da lokalni deo i domen nisu prazni
    if (at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "empty_local_or_domain");
    }
    
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Provera da lokalni deo ne počinje ili ne završava tačkom
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "invalid_local_dot");
    }
    
    // Provera da domen ne počinje ili ne završava crticom ili tačkom
    if (domain_part.front() == '-' || domain_part.front() == '.' || 
        domain_part.back() == '-' || domain_part.back() == '.') {
        return std::make_tuple(false, "invalid_domain_edge");
    }
    
    // Provera da nema uzastopnih tačaka u lokalnom delu
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_local");
    }
    
    // Provera da nema uzastopnih tačaka u domenu
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive_dots_domain");
    }
    
    // Provera da TLD ima najmanje 2 karaktera
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "tld_too_short");
        }
    }
    
    // Konačna provera sa regex-om
    if (std::regex_match(email, email_regex)) {
        return std::make_tuple(true, "valid");
    } else {
        return std::make_tuple(false, "regex_failed");
    }
}