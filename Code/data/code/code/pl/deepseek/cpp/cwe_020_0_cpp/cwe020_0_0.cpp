#include <string>
#include <algorithm>
#include <cctype>
#include <regex>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Walidacja wejścia
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Normalizacja domeny - usunięcie białych znaków
    std::string normalized_domain = domain;
    normalized_domain.erase(std::remove_if(normalized_domain.begin(), normalized_domain.end(), 
                                          [](unsigned char c) { return std::isspace(c); }), 
                          normalized_domain.end());
    
    // Sprawdzenie, czy target zaczyna się od "https://"
    std::string target_lower = target;
    std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    
    // Jeśli target nie zaczyna się od https://, dodajemy go
    std::string processed_target = target;
    if (target_lower.find("https://") != 0 && target_lower.find("http://") != 0) {
        processed_target = "https://" + target;
    }
    
    // Wyodrębnienie hosta z target URL
    std::regex url_regex(R"(^(?:https?://)?([^/?#:]+)(?:[/?#:]|$))", std::regex::icase);
    std::smatch url_match;
    
    if (!std::regex_search(processed_target, url_match, url_regex) || url_match.size() < 2) {
        return "https://" + normalized_domain;
    }
    
    std::string target_host = url_match[1].str();
    std::string target_host_lower = target_host;
    std::transform(target_host_lower.begin(), target_host_lower.end(), target_host_lower.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    
    // Sprawdzenie, czy host targetu znajduje się w podanej domenie
    // Sprawdzamy dokładne dopasowanie lub czy host kończy się na "." + domena
    if (target_host_lower == normalized_domain || 
        (target_host_lower.length() > normalized_domain.length() + 1 &&
         target_host_lower.substr(target_host_lower.length() - normalized_domain.length() - 1) == 
         "." + normalized_domain)) {
        
        // Upewnij się, że zwracany URL używa https://
        std::string result = processed_target;
        if (result.find("https://") != 0 && result.find("http://") != 0) {
            result = "https://" + result;
        }
        
        // Zamień http:// na https:// jeśli istnieje
        if (result.find("http://") == 0) {
            result = "https://" + result.substr(7);
        }
        
        return result;
    }
    
    // Jeśli target nie znajduje się w domenie, zwróć domenę z https://
    return "https://" + normalized_domain;
}