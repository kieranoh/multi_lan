#include <regex>
#include <tuple>

/**
 * @brief Checks if the provided email address is valid.
 *
 * This function uses a regular expression to validate the format of the email address.
 * It covers a wide range of valid email formats to avoid false negatives.
 *
 * @param email The email address to be checked.
 * @return A tuple containing a boolean indicating validity and a message.
 */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regular expression for validating an email address
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    if (std::regex_match(email, email_pattern)) {
        return std::make_tuple(true, "Valid email address.");
    } else {
        return std::make_tuple(false, "Invalid email address.");
    }
}