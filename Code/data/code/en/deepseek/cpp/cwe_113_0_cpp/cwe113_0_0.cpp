#include <string>
#include <map>
#include <cctype>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Create a copy of the original header to restore if needed
    std::map<std::string, std::string> original_header = header;
    
    // Convert info_type to lowercase for case-insensitive comparison
    std::string type_lower = info_type;
    std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // Check if info_type is valid and map to appropriate header key
    std::string header_key;
    if (type_lower == "lang") {
        header_key = "Accept-Language";
    } else if (type_lower == "encoding") {
        header_key = "Accept-Encoding";
    } else if (type_lower == "cache") {
        header_key = "Cache-Control";
    } else {
        // Invalid info_type - restore original header and return
        header = original_header;
        return;
    }
    
    // Validate info_content (should not be empty)
    if (info_content.empty()) {
        header = original_header;
        return;
    }
    
    try {
        // Store the information in the header
        header[header_key] = info_content;
    } catch (...) {
        // If any exception occurs, restore original header
        header = original_header;
    }
}