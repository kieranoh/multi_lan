#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Das reguläre Ausdrucksmuster für die Validierung von E-Mail-Adressen
    const std::string pattern = R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
    std::regex email_regex(pattern);
    
    // Überprüfen, ob die E-Mail-Adresse dem Muster entspricht
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}