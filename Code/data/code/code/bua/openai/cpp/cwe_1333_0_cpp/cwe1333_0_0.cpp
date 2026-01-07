#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Define a regular expression for validating email addresses
    const std::regex email_pattern(
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"
    );

    // Check if the email matches the pattern
    if (std::regex_match(email, email_pattern)) {
        return std::make_tuple(true, "Valid email address.");
    } else {
        return std::make_tuple(false, "Invalid email address.");
    }
}