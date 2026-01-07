#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 1. Basic length and structure checks
    if (email.empty()) {
        return std::make_tuple(false, "Email is empty");
    }
    
    // Check for @ symbol
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "Missing @ symbol");
    }
    
    // Split into local part and domain part
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 2. Check local part (before @)
    if (local_part.empty()) {
        return std::make_tuple(false, "Local part is empty");
    }
    
    if (local_part.length() > 64) {
        return std::make_tuple(false, "Local part exceeds 64 characters");
    }
    
    // Check if local part starts or ends with dot
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "Local part cannot start or end with dot");
    }
    
    // Check for consecutive dots
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Local part contains consecutive dots");
    }
    
    // Check local part characters
    for (char c : local_part) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || 
              c == '.' || c == '!' || c == '#' || c == '$' || 
              c == '%' || c == '&' || c == '\'' || c == '*' || 
              c == '+' || c == '-' || c == '/' || c == '=' || 
              c == '?' || c == '^' || c == '_' || c == '`' || 
              c == '{' || c == '|' || c == '}' || c == '~')) {
            return std::make_tuple(false, "Invalid character in local part");
        }
    }
    
    // 3. Check domain part (after @)
    if (domain_part.empty()) {
        return std::make_tuple(false, "Domain part is empty");
    }
    
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "Domain part exceeds 255 characters");
    }
    
    // Check if domain part starts or ends with dot or hyphen
    if (domain_part.front() == '.' || domain_part.back() == '.' ||
        domain_part.front() == '-' || domain_part.back() == '-') {
        return std::make_tuple(false, "Domain cannot start or end with dot or hyphen");
    }
    
    // Check for consecutive dots or hyphens
    if (domain_part.find("..") != std::string::npos ||
        domain_part.find("--") != std::string::npos) {
        return std::make_tuple(false, "Domain contains consecutive dots or hyphens");
    }
    
    // Split domain into labels
    std::vector<std::string> labels;
    size_t start = 0;
    size_t end = domain_part.find('.');
    
    while (end != std::string::npos) {
        labels.push_back(domain_part.substr(start, end - start));
        start = end + 1;
        end = domain_part.find('.', start);
    }
    labels.push_back(domain_part.substr(start));
    
    // Check each label
    for (const auto& label : labels) {
        if (label.empty()) {
            return std::make_tuple(false, "Empty domain label");
        }
        
        if (label.length() > 63) {
            return std::make_tuple(false, "Domain label exceeds 63 characters");
        }
        
        // Check label characters
        for (char c : label) {
            if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '-')) {
                return std::make_tuple(false, "Invalid character in domain label");
            }
        }
        
        // Check if label starts or ends with hyphen
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, "Domain label cannot start or end with hyphen");
        }
    }
    
    // Check top-level domain (last label)
    const std::string& tld = labels.back();
    if (tld.length() < 2) {
        return std::make_tuple(false, "Top-level domain must be at least 2 characters");
    }
    
    // Check if TLD contains only letters
    for (char c : tld) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "Top-level domain must contain only letters");
        }
    }
    
    // 4. Additional comprehensive regex check (as backup validation)
    // This regex is more permissive to avoid false negatives
    std::regex email_regex(
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$)",
        std::regex::ECMAScript | std::regex::icase
    );
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "Email does not match valid pattern");
    }
    
    // 5. All checks passed
    return std::make_tuple(true, "Valid email address");
}