#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regex voor het controleren van een geldig e-mailadres
    std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    // Controleer of het e-mailadres overeenkomt met het patroon
    bool is_valid = std::regex_match(email, email_pattern);
    
    // Retourneer een tuple met de geldigheid en het gebruikte patroon
    return std::make_tuple(is_valid, email_pattern.str());
}