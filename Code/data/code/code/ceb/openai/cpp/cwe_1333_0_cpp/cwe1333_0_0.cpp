#include <regex>
#include <tuple>
#include <string>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regular expression pattern for validating an email address
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    // Validate the email using the regex pattern
    bool is_valid = std::regex_match(email, pattern);
    
    // Return a tuple containing the validation result and the pattern used
    return std::make_tuple(is_valid, pattern.str());
}