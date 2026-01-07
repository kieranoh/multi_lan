#include <iostream>
#include <regex>
#include <string>
#include <tuple>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Patró per validar l'adreça de correu electrònic
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex regex_pattern(pattern);
    bool is_valid = std::regex_match(email, regex_pattern);
    
    return std::make_tuple(is_valid, pattern);
}