#include <string>
#include <tuple>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Patroon 1: RFC 5322 compliant (vereenvoudigd maar robuust)
    const std::string pattern1 = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Patroon 2: Praktisch patroon voor algemeen gebruik (minder restrictief)
    const std::string pattern2 = 
        R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)";
    
    // Patroon 3: Eenvoudig patroon voor basisvalidatie
    const std::string pattern3 = 
        R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)";
    
    // Controleer op lege string
    if (email.empty()) {
        return std::make_tuple(false, "empty");
    }
    
    // Controleer op voorloop- of volgspaties
    if (email.front() == ' ' || email.back() == ' ') {
        return std::make_tuple(false, "leading/trailing spaces");
    }
    
    // Controleer op meerdere @ tekens
    if (std::count(email.begin(), email.end(), '@') != 1) {
        return std::make_tuple(false, "multiple @ symbols");
    }
    
    // Probeer patronen in volgorde van strengheid
    std::regex regex1(pattern1);
    if (std::regex_match(email, regex1)) {
        return std::make_tuple(true, "RFC 5322 compliant");
    }
    
    std::regex regex2(pattern2, std::regex::icase);
    if (std::regex_match(email, regex2)) {
        return std::make_tuple(true, "common email pattern");
    }
    
    std::regex regex3(pattern3);
    if (std::regex_match(email, regex3)) {
        // Extra controle op domeinnaam
        size_t at_pos = email.find('@');
        std::string domain = email.substr(at_pos + 1);
        
        // Controleer of domein minstens één punt heeft
        if (domain.find('.') == std::string::npos) {
            return std::make_tuple(false, "invalid domain");
        }
        
        // Controleer of TLD minstens 2 tekens heeft
        size_t last_dot = domain.rfind('.');
        std::string tld = domain.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "TLD too short");
        }
        
        // Controleer of TLD alleen letters bevat
        if (!std::all_of(tld.begin(), tld.end(), [](char c) { 
            return std::isalpha(static_cast<unsigned char>(c)); 
        })) {
            return std::make_tuple(false, "invalid TLD");
        }
        
        return std::make_tuple(true, "basic pattern with domain validation");
    }
    
    return std::make_tuple(false, "no pattern matched");
}