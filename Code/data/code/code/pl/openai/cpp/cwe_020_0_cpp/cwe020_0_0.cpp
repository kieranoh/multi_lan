#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Tworzenie wyrażenia regularnego do dopasowania domeny
    std::regex domain_regex("^(https?://)?(www\\.)?(.*\\.)?" + domain + "(/.*)?$");
    
    // Sprawdzenie, czy URL docelowy znajduje się w podanej domenie
    if (std::regex_match(target, domain_regex)) {
        return target; // Zwróć URL, jeśli pasuje do domeny
    } else {
        // Zbudowanie URL przekierowania do podanej domeny
        return "https://" + domain; // Zwróć URL domeny z protokołem https
    }
}