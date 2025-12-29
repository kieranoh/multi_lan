#include <tuple>
#include <string>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Expresión regular para validar el formato del correo electrónico
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})(\.[a-zA-Z]{2,})*$)";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}