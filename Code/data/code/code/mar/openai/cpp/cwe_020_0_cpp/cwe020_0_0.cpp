#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Check if the target URL starts with "https://" and contains the domain
    if (target.find("https://") == 0 && target.find(domain) != std::string::npos) {
        return target; // Return the target URL if it matches the domain
    } else {
        return "https://" + domain; // Otherwise, return the domain URL
    }
}