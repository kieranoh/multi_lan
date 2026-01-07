#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Comprehensive email validation pattern based on RFC 5322 with practical constraints
    std::string pattern = R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    try {
        std::regex email_regex(pattern);
        
        // Additional length checks for practical constraints
        if (email.empty() || email.length() > 254) {  // RFC 5321 specifies 254 max length
            return std::make_tuple(false, pattern);
        }
        
        // Check for consecutive dots in local part before @
        size_t at_pos = email.find('@');
        if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
            return std::make_tuple(false, pattern);
        }
        
        std::string local_part = email.substr(0, at_pos);
        std::string domain_part = email.substr(at_pos + 1);
        
        // Local part validation
        if (local_part.empty() || local_part.length() > 64) {  // RFC 5321 specifies 64 max for local part
            return std::make_tuple(false, pattern);
        }
        
        // Check for consecutive dots in local part
        if (local_part.find("..") != std::string::npos) {
            return std::make_tuple(false, pattern);
        }
        
        // Check if local part starts or ends with dot
        if (local_part.front() == '.' || local_part.back() == '.') {
            return std::make_tuple(false, pattern);
        }
        
        // Domain part validation
        if (domain_part.empty() || domain_part.length() > 253) {  // RFC 1035 specifies 253 max for domain
            return std::make_tuple(false, pattern);
        }
        
        // Check for consecutive dots in domain part
        if (domain_part.find("..") != std::string::npos) {
            return std::make_tuple(false, pattern);
        }
        
        // Check if domain part starts or ends with dot or hyphen
        if (domain_part.front() == '.' || domain_part.back() == '.' ||
            domain_part.front() == '-' || domain_part.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        
        // Check each domain label
        size_t start = 0;
        size_t dot_pos;
        do {
            dot_pos = domain_part.find('.', start);
            std::string label = (dot_pos == std::string::npos) ? 
                                domain_part.substr(start) : 
                                domain_part.substr(start, dot_pos - start);
            
            // Label length validation (1-63 chars per RFC 1035)
            if (label.empty() || label.length() > 63) {
                return std::make_tuple(false, pattern);
            }
            
            // Label cannot start or end with hyphen
            if (label.front() == '-' || label.back() == '-') {
                return std::make_tuple(false, pattern);
            }
            
            // Label must contain only allowed characters
            for (char c : label) {
                if (!(std::isalnum(c) || c == '-')) {
                    return std::make_tuple(false, pattern);
                }
            }
            
            start = dot_pos + 1;
        } while (dot_pos != std::string::npos);
        
        // Check TLD (last label) - must be at least 2 characters and contain only letters
        size_t last_dot = domain_part.find_last_of('.');
        std::string tld = (last_dot == std::string::npos) ? domain_part : domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, pattern);
        }
        
        // TLD should contain only letters (practical constraint for most valid emails)
        if (!std::all_of(tld.begin(), tld.end(), [](char c) { return std::isalpha(c); })) {
            return std::make_tuple(false, pattern);
        }
        
        // Final regex check
        bool is_valid = std::regex_match(email, email_regex);
        return std::make_tuple(is_valid, pattern);
        
    } catch (const std::regex_error&) {
        // Fallback pattern if the comprehensive one fails
        std::string fallback_pattern = R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)";
        std::regex fallback_regex(fallback_pattern);
        bool is_valid = std::regex_match(email, fallback_regex);
        return std::make_tuple(is_valid, fallback_pattern);
    }
}