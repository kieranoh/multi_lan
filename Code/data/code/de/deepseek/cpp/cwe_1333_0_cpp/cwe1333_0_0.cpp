#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Pattern 1: RFC 5322 compliant pattern (most comprehensive)
    std::string pattern1 = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Pattern 2: More restrictive but common pattern
    std::string pattern2 = 
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)";
    
    // Pattern 3: Allows multiple subdomains and country codes
    std::string pattern3 = 
        R"(^[a-zA-Z0-9._%+-]+@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})?$)";
    
    // Pattern 4: Allows internationalized domain names (IDN)
    std::string pattern4 = 
        R"(^[a-zA-Z0-9._%+-]+@(?:[a-zA-Z0-9-]+\.)*[a-zA-Z0-9-]+\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$)";
    
    // Pattern 5: Strict pattern with length limits
    std::string pattern5 = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$)";
    
    // Additional basic checks
    if (email.empty() || email.length() > 254) {  // RFC 5321 specifies 254 max length
        return std::make_tuple(false, "Length check failed");
    }
    
    // Check for @ symbol
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "Missing or misplaced @ symbol");
    }
    
    // Check local part (before @) and domain part (after @)
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Local part cannot start or end with dot
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "Local part cannot start or end with dot");
    }
    
    // Domain part cannot start or end with dot or hyphen
    if (domain_part.front() == '.' || domain_part.back() == '.' ||
        domain_part.front() == '-' || domain_part.back() == '-') {
        return std::make_tuple(false, "Domain part cannot start or end with dot or hyphen");
    }
    
    // Check for consecutive dots
    if (email.find("..") != std::string::npos) {
        return std::make_tuple(false, "Consecutive dots are not allowed");
    }
    
    // Check domain part has at least one dot
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "Domain must contain at least one dot");
    }
    
    // Try patterns in order of strictness
    std::vector<std::pair<std::string, std::string>> patterns = {
        {"RFC 5322 compliant", pattern1},
        {"Common email pattern", pattern2},
        {"Multiple subdomains", pattern3},
        {"International domains", pattern4},
        {"Strict with length limits", pattern5}
    };
    
    for (const auto& [pattern_name, pattern_str] : patterns) {
        try {
            std::regex email_regex(pattern_str);
            if (std::regex_match(email, email_regex)) {
                return std::make_tuple(true, pattern_name);
            }
        } catch (const std::regex_error& e) {
            // If regex fails, continue to next pattern
            continue;
        }
    }
    
    // Additional heuristic checks for edge cases
    // Check if domain part ends with valid TLD pattern
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2 || tld.length() > 63) {
            return std::make_tuple(false, "Invalid TLD length");
        }
        
        // Check TLD contains only letters
        if (!std::all_of(tld.begin(), tld.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        })) {
            return std::make_tuple(false, "TLD must contain only letters");
        }
    }
    
    // Final fallback: simple check for common structure
    if (email.find('@') != std::string::npos && 
        email.find('.', email.find('@')) != std::string::npos &&
        email.find(' ') == std::string::npos) {
        return std::make_tuple(true, "Simple heuristic check");
    }
    
    return std::make_tuple(false, "No pattern matched");
}