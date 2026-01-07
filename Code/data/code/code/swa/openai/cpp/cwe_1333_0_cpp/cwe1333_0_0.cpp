#include <regex>
#include <tuple>
#include <string>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regex pattern for validating an email address
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    // Check if the email matches the regex pattern
    if (std::regex_match(email, pattern)) {
        return std::make_tuple(true, "Valid email address");
    } else {
        return std::make_tuple(false, "Invalid email address");
    }
}