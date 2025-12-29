#include <string>
#include <map>
#include <algorithm>
#include <cctype>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Make a copy of the original header in case we need to revert
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Convert info_type to lowercase for case-insensitive comparison
        std::string type_lower = info_type;
        std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        // Check if the info_type is valid and store in appropriate header key
        if (type_lower == "lang") {
            header["Accept-Language"] = info_content;
        } else if (type_lower == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (type_lower == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Invalid info_type - revert to original header
            header = std::move(original_header);
        }
        
        // If info_content is empty, we might want to remove the header
        // But the problem doesn't specify this, so we'll just store empty string
        // which is valid for headers
        
    } catch (...) {
        // If anything goes wrong, revert to original header
        header = std::move(original_header);
    }
}