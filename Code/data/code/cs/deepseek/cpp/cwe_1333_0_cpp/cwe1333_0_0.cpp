#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 compliant regex pattern (simplified for practical use)
    // This pattern covers most real-world email addresses while avoiding false negatives
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Additional length constraints as per RFC standards
    if (email.empty() || email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // Check for consecutive dots in local part or domain
    if (email.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Check if @ exists and is not at the beginning or end
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // Split into local and domain parts
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Check local part length (max 64 chars per RFC)
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // Check domain part length and structure
    if (domain_part.length() > 253 || domain_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Check for valid domain labels
    size_t dot_pos = 0;
    size_t prev_pos = 0;
    while ((dot_pos = domain_part.find('.', prev_pos)) != std::string::npos) {
        std::string label = domain_part.substr(prev_pos, dot_pos - prev_pos);
        if (label.empty() || label.length() > 63 || 
            label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        prev_pos = dot_pos + 1;
    }
    
    // Check last label
    std::string last_label = domain_part.substr(prev_pos);
    if (last_label.empty() || last_label.length() > 63 || 
        last_label.front() == '-' || last_label.back() == '-') {
        return std::make_tuple(false, pattern);
    }
    
    // Check TLD (Top-Level Domain) - should contain at least one letter
    bool has_letter = std::any_of(last_label.begin(), last_label.end(), 
                                  [](char c) { return std::isalpha(c); });
    if (!has_letter) {
        return std::make_tuple(false, pattern);
    }
    
    // Apply the main regex pattern
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}