#include <tuple>
#include <string>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RegEx pattern for validating email addresses
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    
    // Validate the email against the pattern
    bool is_valid = std::regex_match(email, pattern);
    
    // Return the result as a tuple (validity, pattern used)
    return std::make_tuple(is_valid, pattern.str());
}