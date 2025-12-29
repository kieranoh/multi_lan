#include <map>
#include <string>
#include <algorithm>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Create a copy of the original header in case we need to restore it
    std::map<std::string, std::string> original_header = header;
    
    try {
        // Convert info_type to lowercase for case-insensitive comparison
        std::string lower_type = info_type;
        std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        // Check the info_type and store in appropriate header key
        if (lower_type == "lang") {
            header["Accept-Language"] = info_content;
        } else if (lower_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (lower_type == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            // Invalid info_type - restore original header
            header = std::move(original_header);
        }
    } catch (...) {
        // If anything goes wrong, restore the original header
        header = std::move(original_header);
    }
}