#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    const std::regex email_regex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})(\.[a-zA-Z]{2,})?$)");
    if (std::regex_match(email, email_regex)) {
        return std::make_tuple(true, "Valid email address.");
    } else {
        return std::make_tuple(false, "Invalid email address.");
    }
}