#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Trim leading and trailing whitespace from both inputs
    auto trim = [](const std::string& str) -> std::string {
        size_t start = str.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string::npos) {
            return "";
        }
        size_t end = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(start, end - start + 1);
    };
    
    std::string trimmed_domain = trim(domain);
    std::string trimmed_subdomain = trim(subdomain_prefix);
    
    // Check if subdomain is empty or invalid (only whitespace)
    if (trimmed_subdomain.empty()) {
        return "https://" + trimmed_domain;
    }
    
    // Remove any trailing dot from subdomain if present
    if (!trimmed_subdomain.empty() && trimmed_subdomain.back() == '.') {
        trimmed_subdomain.pop_back();
    }
    
    // Remove any leading dot from domain if present
    if (!trimmed_domain.empty() && trimmed_domain.front() == '.') {
        trimmed_domain.erase(0, 1);
    }
    
    // Remove any trailing dot from domain if present
    if (!trimmed_domain.empty() && trimmed_domain.back() == '.') {
        trimmed_domain.pop_back();
    }
    
    // Construct the URL
    std::string url = "https://";
    url += trimmed_subdomain;
    url += ".";
    url += trimmed_domain;
    
    return url;
}