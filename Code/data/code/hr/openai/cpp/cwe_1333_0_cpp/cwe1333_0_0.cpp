#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regular expression for validating an email address
    const std::string email_pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))";
    std::regex regex(email_pattern);
    
    // Check if the email matches the pattern
    bool is_valid = std::regex_match(email, regex);
    
    // Return a tuple with the validation result and the email pattern used
    return std::make_tuple(is_valid, email_pattern);
}